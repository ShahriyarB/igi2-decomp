"""Print a function's disassembly from the retail IDB (for writing overrides).

usage: python tools/ida_disasm.py <name or 0xaddr> [...]
"""
import sys
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parent.parent
if idapro.open_database(str(REPO / "work" / "retail" / "igi2_1.0.exe.i64"), run_auto_analysis=False):
    raise SystemExit("could not open the retail IDB")
import ida_funcs  # noqa: E402
import ida_lines  # noqa: E402
import ida_name  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

for arg in sys.argv[1:]:
    ea = int(arg, 16) if arg.startswith("0x") else ida_name.get_name_ea(idc.BADADDR, arg)
    f = ida_funcs.get_func(ea)
    print(f"// ---- {arg} @ {ea:#x}  type: {idc.get_type(ea)}  size {f.size() if f else '?'}")
    for h in (idautils.FuncItems(ea) if f else []):
        print(f"{h:#x}  {ida_lines.tag_remove(idc.generate_disasm_line(h, 0))}")
    print()
idapro.close_database(save=False)
