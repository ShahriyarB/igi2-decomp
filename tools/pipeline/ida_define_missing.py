"""Create retail functions IDA missed, at addresses the Final client PDB predicts exactly.

For an unmatched Final function lying between two matched functions whose distance is the same
in both builds, the bytes in between have the same layout, so its retail start is
prev_retail + (rva - prev_rva). A function that swallowed it is cut short there.

usage: python tools/pipeline/ida_define_missing.py   (system Python with idapro)
"""
import bisect
import json
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parents[2]
IDB = REPO / "work" / "retail" / "igi2_1.0.exe.i64"
if idapro.open_database(str(IDB), run_auto_analysis=False):
    raise SystemExit(f"could not open {IDB}")

import ida_auto  # noqa: E402
import ida_bytes  # noqa: E402
import ida_funcs  # noqa: E402
import ida_ua  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

m = json.loads((REPO / "symbols" / "match.json").read_text())
items = sorted((int(k), v) for k, v in m.items())
matched = [(rva, v["ea"]) for rva, v in items if v["ea"] is not None]
mr = [r for r, _ in matched]
created = cut = skipped = 0
# matched functions this database does not have yet (rebuilding from the analysis-only copy)
for rva, v in items:
    ea = v["ea"]
    if ea is None or (ida_funcs.get_func(ea) and ida_funcs.get_func(ea).start_ea == ea):
        continue
    f = ida_funcs.get_func(ea)
    if f and f.start_ea > ea:
        ida_funcs.del_func(f.start_ea)  # owned as a chunk by a function IDA began inside this one
        f = ida_funcs.get_func(ea)
    if f and f.start_ea < ea:
        ida_funcs.set_func_end(f.start_ea, ea)
        cut += 1
    misstarted = False
    for s in range(ea + 1, ea + 16):  # IDA began this function a few bytes in, after a misdecode
        g = ida_funcs.get_func(s)
        if g and g.start_ea == s:
            misstarted = ida_funcs.del_func(s) or misstarted
    ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, v["retail_size"] or v["length"])
    ida_ua.create_insn(ea)
    if misstarted:  # its size was measured from the wrong start: let IDA follow the flow
        created += bool(ida_funcs.add_func(ea) or ida_funcs.add_func(ea, ea + (v["retail_size"] or v["length"])))
    else:
        created += bool(ida_funcs.add_func(ea, ea + (v["retail_size"] or v["length"])))
for rva, v in items:
    if v["ea"] is not None:
        continue
    k = bisect.bisect_left(mr, rva) - 1
    if k < 0 or k + 1 >= len(matched):
        continue
    (prva, pea), (nrva, nea) = matched[k], matched[k + 1]
    if nea - pea != nrva - prva:
        skipped += 1
        continue
    ea, end = pea + (rva - prva), pea + (rva - prva) + v["length"]
    if ((0x400000 + rva) % 16 == 0) != (ea % 16 == 0):
        skipped += 1
        continue  # alignment disagrees with the Final build: not where this function starts
    f = ida_funcs.get_func(ea)
    if f and f.start_ea == ea:
        continue
    if f and f.start_ea < ea:
        ida_funcs.set_func_end(f.start_ea, ea)
        cut += 1
    ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, v["length"])
    ida_ua.create_insn(ea)
    if ida_funcs.add_func(ea, end):
        created += 1
ida_auto.auto_wait()
print(f"created {created} functions ({cut} cut out of a neighbour); {skipped} gaps differ in layout")

FLOW_END = ("retn", "ret", "jmp", "int3", "hlt")


def ends_flow(ea):
    mnem = idc.print_insn_mnem(ea)
    if mnem in FLOW_END:
        return True
    return mnem == "call" and not ida_funcs.func_does_return(idc.get_operand_value(ea, 0))


def repair_truncated():
    """A function that stops before its flow does (QCamera_Clear ending on the store before its
    retn): an explicit size above, or a junk function IDA started inside its tail, cut it.
    Walk on from the end to the instruction that ends the flow and take those bytes back; a
    function found starting in the middle of one of them was never real, so it goes."""
    matched = {v["ea"] for v in m.values() if v["ea"] is not None}
    insn = ida_ua.insn_t()
    fixed = removed = 0
    for fea in list(idautils.Functions()):
        f = ida_funcs.get_func(fea)
        if fea % 16 or fea not in matched or f.flags & ida_funcs.FUNC_LIB:
            continue
        last = idc.prev_head(f.end_ea, f.start_ea)
        if not ida_bytes.is_code(ida_bytes.get_flags(last)) or ends_flow(last):
            continue  # ends in a jump table, or ends properly
        if ida_bytes.get_byte(f.end_ea) in (0xCC, 0x90):
            continue  # padding follows: the last call does not return
        ea, junk = f.end_ea, []
        while ea - f.end_ea < 0x200:
            g = ida_funcs.get_func(ea)
            if g and g.start_ea == ea and ea % 16 == 0 and ea in matched:
                break  # a real function follows: not a truncation this walk can mend
            if g and g.start_ea != f.start_ea:
                junk.append(g.start_ea)
            n = ida_ua.decode_insn(insn, ea)
            if n <= 0:
                break
            junk += [s for s in range(ea + 1, ea + n)  # a function starting inside this instruction
                     if ida_funcs.get_func(s) and ida_funcs.get_func(s).start_ea == s]
            ea += n
            if insn.get_canon_mnem() in FLOW_END:
                for s in sorted(set(junk)):
                    removed += bool(ida_funcs.del_func(s))
                ida_bytes.del_items(f.end_ea, ida_bytes.DELIT_SIMPLE, ea - f.end_ea)
                i = f.end_ea
                while i < ea:
                    i += idc.create_insn(i) or 1
                fixed += bool(ida_funcs.set_func_end(fea, ea))
                break
    ida_auto.auto_wait()
    print(f"truncated functions mended {fixed} (junk functions removed {removed})")


repair_truncated()
idapro.close_database(save=True)
