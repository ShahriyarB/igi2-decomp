"""Make functions of the code addresses decompiled text refers to by an address name.

A callback IDA never saw called shows up in decompiled code as loc_XXXXXX (taken as a pointer),
sub_XXXXXX (called, but not a function start) or "loc_XXXXXX + k" (an address IDA expressed
relative to the label before it); a tail call into code IDA filed under another function shows
up as JUMPOUT(0xXXXXXX). These are real functions: this defines them in the
functions-only base IDB, so every later apply/export includes them. Functions start 16-byte
aligned (MSVC's alignment), which tells real starts from bytes in the middle of other code.

usage: python tools/pipeline/ida_define_referenced.py   (system Python with idapro; then rerun the pipeline)
"""
import re
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parents[2]
IDB = REPO / "work" / "retail" / "igi2_1.0.exe.functions.i64"
targets = set()
for src in (REPO / "src").rglob("*.c"):
    text = src.read_text(encoding="utf-8", errors="replace")
    for m in re.finditer(r"\b(?:loc|sub)_([0-9A-F]{6,8})\b(?:\s*\+\s*(\d+))?", text):
        targets.add(int(m.group(1), 16) + int(m.group(2) or 0))
    for m in re.finditer(r"\bJUMPOUT\(0x([0-9A-F]+)\)", text):
        targets.add(int(m.group(1), 16))
    # a callback whose first bytes IDA read as a pointer: "&off_404120" (only code addresses count)
    for m in re.finditer(r"&off_([0-9A-F]{6,8})\b", text):
        targets.add(int(m.group(1), 16))
    # ... or inside data it named: "(void (__cdecl *)(int))&dword_4537F4[3]" is 0x453800
    for m in re.finditer(r"\(__cdecl \*\)\([^()]*\)\)&(byte|word|dword|unk)_([0-9A-F]{6,8})(?:\[(\d+)\])?", text):
        scale = {"byte": 1, "unk": 1, "word": 2, "dword": 4}[m.group(1)]
        targets.add(int(m.group(2), 16) + scale * int(m.group(3) or 0))

if idapro.open_database(str(IDB), run_auto_analysis=False):
    raise SystemExit(f"could not open {IDB}")
import ida_auto  # noqa: E402
import ida_bytes  # noqa: E402
import ida_funcs  # noqa: E402
import ida_segment  # noqa: E402
import idc  # noqa: E402

def data_pointer_targets():
    """Code addresses held in data that IDA took for data: HumanPlayer_apfAction's entries 2 and 7
    (0x4BF1E0, 0x4BF4E0) are action handlers it read as dwords, so they had no C, the table kept
    retail addresses, and the game jumped into retail code that our build cannot run. A target
    counts when it is 16-byte aligned in .text, outside every function, after alignment padding
    or a ret/jmp, and not itself a data item holding a pointer (DirectInput's data formats)."""
    import ida_ua
    text = ida_segment.get_segm_by_name(".text")
    out = set()
    for name in (".data", ".rdata"):
        seg = ida_segment.get_segm_by_name(name)
        if not seg:
            continue
        data = ida_bytes.get_bytes(seg.start_ea, seg.end_ea - seg.start_ea) or b""
        for off in range(0, len(data) - 3, 4):
            v = int.from_bytes(data[off:off + 4], "little")
            if not (text.start_ea <= v < text.end_ea) or v % 16 or ida_funcs.get_func(v):
                continue
            flags = ida_bytes.get_flags(v)
            if ida_bytes.is_off0(flags) or not ida_ua.decode_insn(ida_ua.insn_t(), v):
                continue
            prev = ida_bytes.get_byte(v - 1)
            prev_insn = idc.prev_head(v)
            inside_data = not ida_bytes.is_code(flags) and ida_bytes.get_item_head(v) != v
            if inside_data or prev in (0xCC, 0x90) or \
                    (prev_insn != idc.BADADDR and idc.print_insn_mnem(prev_insn) in ("retn", "jmp")):
                out.add(v)
    return out


def immediate_targets():
    """Code addresses written into memory as immediates: sub_4BF4E0 stores 0x4BF510 as its
    action's state function ("mov [ecx+18h], 4BF510h") and then jumps there, so IDA made the two
    one function, the C kept 4977936 as a number, and the state ran retail code. Taken only where
    a function could start: 16-byte aligned, inside another function, after a jmp/ret (checked
    by the loop below)."""
    import ida_ua
    text = ida_segment.get_segm_by_name(".text")
    out = set()
    for fea in idautils.Functions(text.start_ea, text.end_ea):
        for item in idautils.FuncItems(fea):
            insn = ida_ua.insn_t()
            if not ida_ua.decode_insn(insn, item):
                continue
            for op in insn.ops:
                if op.type == idc.o_void:
                    break
                v = op.value if op.type == idc.o_imm else None
                if v is None or not (text.start_ea <= v < text.end_ea) or v % 16:
                    continue
                f = ida_funcs.get_func(v)
                if f and f.start_ea != v:
                    out.add(v)
    return out


import idautils  # noqa: E402
targets |= data_pointer_targets() | immediate_targets()


def tail_owners(chunk):
    """The functions sharing a tail chunk. The iterator locks the chunk while it lives, so it
    must be gone before the chunk can be changed."""
    it = ida_funcs.func_parent_iterator_t(chunk)
    owners = []
    ok = it.first()
    while ok:
        owners.append(it.parent())
        ok = it.next()
    del it
    return owners


created = skipped = changed = 0
failed = []
for ea in sorted(targets):
    seg = ida_segment.getseg(ea)
    if not seg or idc.get_segm_name(ea) != ".text":
        continue
    f = ida_funcs.get_func(ea)
    if f and f.start_ea == ea:
        continue
    if f and f.start_ea % 16 == 0 or ea % 16:
        pass
    elif f and not f.flags & ida_funcs.FUNC_LIB:
        ida_funcs.del_func(f.start_ea)  # an unaligned function is junk IDA made: it never owned this
        changed += 1
        f = None
    prev = ida_bytes.get_byte(ea - 1)
    prev_insn = idc.prev_head(ea)
    after_ret = prev_insn != idc.BADADDR and idc.print_insn_mnem(prev_insn) in ("retn", "ret", "jmp")
    if ea % 16 or (f and not (prev in (0xCC, 0x90) or after_ret)):
        skipped += 1
        continue  # not where a function starts
    changed += 1
    chunk = ida_funcs.get_fchunk(ea)
    if f and chunk and chunk.start_ea == ea and chunk.start_ea != f.start_ea:
        # a function IDA took for a tail its callers share: detach it from every one of them
        for owner in tail_owners(chunk) or [f.start_ea]:
            ida_funcs.remove_func_tail(ida_funcs.get_func(owner), ea)
    elif f:  # a callback IDA glued onto the function before it
        ida_funcs.set_func_end(f.start_ea, ea)
    head = ida_bytes.get_item_head(ea)
    if head != ea or not ida_bytes.is_code(ida_bytes.get_flags(ea)):
        # data, or the middle of an instruction IDA decoded out of step ("loc_45357F + 1"); a
        # data item goes whole, so the function's code after these 16 bytes can be followed too
        size = ida_bytes.get_item_size(head) if not ida_bytes.is_code(ida_bytes.get_flags(head)) else 0
        ida_bytes.del_items(head, ida_bytes.DELIT_SIMPLE, max(ea + 16, head + size) - head)
        idc.create_insn(ea)
    if ida_funcs.add_func(ea):
        created += 1
    else:
        failed.append(ea)
ida_auto.auto_wait()
print(f"referenced code addresses {len(targets)}, functions created {created}, not a start {skipped}"
      + (f", failed at {', '.join(map(hex, failed))}" if failed else ""))
# unchanged, the database is left as it was: pipeline.py skips apply when its inputs are unchanged
idapro.close_database(save=changed > 0)
