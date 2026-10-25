"""Open an exe headless in IDA (idalib) and dump per-function fingerprints for matching.

usage: python tools/pipeline/ida_fingerprints.py <exe> <out.json>
Runs with the system Python that has the `idapro` package (not the uv venv). The IDB is kept
next to the exe (work/ is gitignored) so later steps reuse the analysis.
"""
import hashlib
import json
import re
import sys
import time
from pathlib import Path

import idapro

exe, out_path = sys.argv[1], sys.argv[2]
t0 = time.time()
# reuse an existing database (it may carry functions added by later steps)
db = exe + ".i64" if Path(exe + ".i64").exists() else exe
if idapro.open_database(db, run_auto_analysis=True):
    raise SystemExit(f"could not open {exe}")

import ida_auto  # noqa: E402  (IDA modules exist only after idapro is initialised)
import ida_bytes  # noqa: E402
import ida_funcs  # noqa: E402
import ida_ida  # noqa: E402
import ida_idp  # noqa: E402
import ida_lines  # noqa: E402
import ida_nalt  # noqa: E402
import ida_name  # noqa: E402
import ida_ua  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

ida_auto.auto_wait()
print(f"analysis {time.time() - t0:.0f}s, {ida_funcs.get_func_qty()} functions", flush=True)

lo, hi = ida_ida.inf_get_min_ea(), ida_ida.inf_get_max_ea()
imports = {}


def _imp(ea, name, ordinal):
    imports[ea] = name or f"ord{ordinal}"
    return True


for i in range(ida_nalt.get_import_module_qty()):
    ida_nalt.enum_import_names(i, _imp)

strings = {}
for s in idautils.Strings():
    try:
        strings[s.ea] = str(s)[:160]
    except Exception:
        pass

TOKEN = re.compile(r"[A-Za-z_?@$][\w?@$]*")
HEX = re.compile(r"\b([0-9A-F]+)h\b")
REGS = {"eax", "ebx", "ecx", "edx", "esi", "edi", "esp", "ebp", "ax", "bx", "cx", "dx", "si",
        "di", "sp", "bp", "al", "ah", "bl", "bh", "cl", "ch", "dl", "dh", "st", "ptr", "byte",
        "word", "dword", "qword", "tbyte", "large", "short", "near", "far", "offset", "ds", "es",
        "fs", "gs", "ss", "cs"}
_name_cache = {}


def _is_name(tok):
    if tok in REGS or tok.startswith("st"):
        return False
    if tok not in _name_cache:
        _name_cache[tok] = ida_name.get_name_ea(idc.BADADDR, tok) != idc.BADADDR
    return _name_cache[tok]


def _hexmask(m):
    v = int(m.group(1), 16)
    return "ADDR" if lo <= v < hi else m.group(0)


def norm_operand(ea, n):
    t = idc.get_operand_type(ea, n)
    if t in (idc.o_mem, idc.o_near, idc.o_far):
        return "ADDR"
    text = ida_lines.tag_remove(idc.print_operand(ea, n) or "")
    if t == idc.o_imm:
        v = idc.get_operand_value(ea, n) & 0xFFFFFFFF
        return "ADDR" if lo <= v < hi else f"#{v:x}"
    text = TOKEN.sub(lambda m: "ADDR" if _is_name(m.group(0)) else m.group(0), text)
    return HEX.sub(_hexmask, text)


funcs = []
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    flags = f.flags
    lines, mnems, calls, callee_imports, strs, data_refs, consts = [], [], [], [], [], 0, []
    drefs = []  # ordered (instruction index, operand, address) of every global data reference
    ninsn = 0
    for head in idautils.FuncItems(fea):
        if not ida_bytes.is_code(ida_bytes.get_flags(head)):
            continue
        ninsn += 1
        mn = idc.print_insn_mnem(head)
        mnems.append(mn)
        ops = []
        for n in range(3):
            if idc.get_operand_type(head, n) == idc.o_void:
                break
            ops.append(norm_operand(head, n))
            ot = idc.get_operand_type(head, n)
            if ot in (idc.o_mem, idc.o_imm, idc.o_displ):
                v = idc.get_operand_value(head, n) & 0xFFFFFFFF  # displacement for o_displ
                if lo <= v < hi and not ida_bytes.is_code(ida_bytes.get_flags(v)) and v not in imports:
                    drefs.append((ninsn - 1, n, v))
            if idc.get_operand_type(head, n) == idc.o_imm:
                v = idc.get_operand_value(head, n) & 0xFFFFFFFF
                if not (lo <= v < hi) and v > 0xFF:
                    consts.append(v)
        lines.append(mn + " " + ",".join(ops))
        is_call = ida_idp.is_call_insn(head)
        for ref in idautils.CodeRefsFrom(head, False):
            if ref in imports:
                callee_imports.append(imports[ref])
            elif is_call:
                cf = ida_funcs.get_func(ref)
                if cf and cf.start_ea == ref:
                    calls.append(ref)
        for ref in idautils.DataRefsFrom(head):
            if ref in strings:
                strs.append(strings[ref])
            elif ref in imports:
                callee_imports.append(imports[ref])
            else:
                data_refs += 1
                # call ds:[import] goes through a data ref
    funcs.append({
        "ea": fea, "end": f.end_ea, "size": f.end_ea - fea, "name": ida_name.get_name(fea),
        "lib": bool(flags & ida_funcs.FUNC_LIB), "thunk": bool(flags & ida_funcs.FUNC_THUNK),
        "ninsn": ninsn,
        "hash": hashlib.md5("\n".join(lines).encode()).hexdigest(),
        "mhash": hashlib.md5(" ".join(mnems).encode()).hexdigest(),
        "calls": calls, "imports": sorted(set(callee_imports)), "strings": strs,
        "consts": sorted(set(consts))[:64], "data_refs": data_refs, "drefs": drefs,
    })

callers = {}
for f in funcs:
    for c in f["calls"]:
        callers.setdefault(c, set()).add(f["ea"])
for f in funcs:
    f["callers"] = sorted(callers.get(f["ea"], ()))

segs = [{"name": idc.get_segm_name(s), "start": s, "end": idc.get_segm_end(s)}
        for s in idautils.Segments()]
json.dump({"exe": exe, "imagebase": ida_nalt.get_imagebase(), "segments": segs,
           "functions": funcs, "imports": {str(k): v for k, v in imports.items()}},
          open(out_path, "w"))
print(f"{len(funcs)} functions, {len(strings)} strings, {len(imports)} imports, "
      f"{time.time() - t0:.0f}s total", flush=True)
idapro.close_database(save=True)
