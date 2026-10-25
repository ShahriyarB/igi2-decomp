"""Decompile named functions from the retail IDB and print them (spot checks).

usage: python tools/debug/ida_decompile.py [--db=retail|ds12] <name or 0xaddr> [...]
"""
import sys
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parents[2]
DBS = {"retail": REPO / "work" / "retail" / "igi2_1.0.exe.i64", "ds12": REPO / "work" / "ds12" / "igi2.exe.i64"}
db = "retail"
if sys.argv[1].startswith("--db="):
    db = sys.argv.pop(1)[5:]
if idapro.open_database(str(DBS[db]), run_auto_analysis=False):
    raise SystemExit(f"could not open {DBS[db]}")

import ida_hexrays  # noqa: E402
import ida_name  # noqa: E402
import idc  # noqa: E402

ida_hexrays.init_hexrays_plugin()
for arg in sys.argv[1:]:
    ea = int(arg, 16) if arg.startswith("0x") else ida_name.get_name_ea(idc.BADADDR, arg)
    try:
        cf = ida_hexrays.decompile(ea)
        print(f"// ---- {arg} @ {ea:#x}\n{cf}\n")
    except ida_hexrays.DecompilationFailure as e:
        print(f"// ---- {arg} @ {ea:#x}: decompilation failed: {e}\n")
idapro.close_database(save=False)
