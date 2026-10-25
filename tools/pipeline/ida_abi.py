"""Record the calling convention Hex-Rays deduces for every function (no PDB prototypes applied).

Final builds used link-time code generation, so many functions take arguments in registers
(e.g. Symbol_Register gets zName in ebx); PDB prototypes say plain __cdecl. This decompiles each
function of an IDB copy that has function boundaries but no applied types and stores where each
argument actually lives.

usage: python tools/pipeline/ida_abi.py   -> symbols/abi.json {ea: {cc, ret, args: [[kind, where, size]], ...}}
"""
import json
import time
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parents[2]
SRC = REPO / "work" / "retail" / "igi2_1.0.exe.functions.i64"
COPY = REPO / "work" / "retail" / "abi_probe.i64"
COPY.write_bytes(SRC.read_bytes())
if idapro.open_database(str(COPY), run_auto_analysis=False):
    raise SystemExit("could not open the probe IDB")

import ida_funcs  # noqa: E402
import ida_hexrays  # noqa: E402
import ida_typeinf  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

ida_hexrays.init_hexrays_plugin()
CC = {getattr(ida_typeinf, k): v for k, v in (
    ("CM_CC_CDECL", "cdecl"), ("CM_CC_STDCALL", "stdcall"), ("CM_CC_FASTCALL", "fastcall"),
    ("CM_CC_THISCALL", "thiscall"), ("CM_CC_SPECIALP", "userpurge"), ("CM_CC_SPECIAL", "usercall"),
    ("CM_CC_SPECIALE", "usercall..."), ("CM_CC_ELLIPSIS", "cdecl...")) if hasattr(ida_typeinf, k)}


def kind_of(t):
    """What the decompiler saw the argument used as: pointer, float or integer."""
    if t.is_ptr() or t.is_array():
        return "ptr"
    if t.is_floating():
        return "float"
    return "int"


def argloc(loc, size, t=None):
    k = kind_of(t) if t is not None else None
    if loc.is_reg1():
        return ["reg", ida_hexrays.get_mreg_name(ida_hexrays.reg2mreg(loc.reg1()), size) or str(loc.reg1()), size, k]
    if loc.is_reg2():
        return ["reg2", f"{loc.reg1()}:{loc.reg2()}", size, k]
    if loc.is_stkoff():
        return ["stack", loc.stkoff(), size, k]
    return ["other", str(loc.atype()), size, k]


t0 = time.time()
out, failed = {}, 0
funcs = list(idautils.Functions())
# Auto-analysis stores guessed prototypes (a stack argument named Str1 after the strncmp it
# reaches), and the decompiler obeys a stored type: an argument in ecx is then just an
# uninitialized register. Measure every non-library function from its code alone.
for ea in funcs:
    if not ida_funcs.get_func(ea).flags & ida_funcs.FUNC_LIB:
        idc.SetType(ea, "")
for n, ea in enumerate(funcs):
    try:
        cf = ida_hexrays.decompile(ea, flags=ida_hexrays.DECOMP_NO_WAIT | ida_hexrays.DECOMP_NO_CACHE)
    except ida_hexrays.DecompilationFailure:
        failed += 1
        continue
    if not cf:
        failed += 1
        continue
    fi = ida_typeinf.func_type_data_t()
    if not cf.type.get_func_details(fi):
        continue
    out[ea] = {"cc": CC.get(fi.get_cc(), hex(fi.get_cc())), "ret": str(fi.rettype),
               "retloc": argloc(fi.retloc, fi.rettype.get_size()) if not fi.rettype.is_void() else None,
               "args": [argloc(a.argloc, a.type.get_size(), a.type) for a in fi],
               "purge": fi.stkargs if hasattr(fi, "stkargs") else None}
    if n % 1000 == 0:
        print(f"{n}/{len(funcs)} {time.time() - t0:.0f}s", flush=True)
(REPO / "symbols" / "abi.json").write_text(json.dumps({str(k): v for k, v in out.items()}))
print(f"decompiled {len(out)}, failed {failed}, {time.time() - t0:.0f}s", flush=True)
idapro.close_database(save=False)
