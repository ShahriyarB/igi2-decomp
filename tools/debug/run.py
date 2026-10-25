"""Run the rebuilt client in the game folder under cdb and report what stopped it.

The game rewrites its settings (config.qsc/.qvm) when it exits: they are backed up first and put
back afterwards, so test runs never change the player's setup. On a crash cdb prints the event,
the registers and the stack with source lines; a run that is still going after the time limit
is stopped.

usage: uv run run.py [seconds=90] [game arguments...]     (default arguments: Window)
       IGI2_CDB='bp igi2!Script_New "da poi(esp+4); g"; ' uv run run.py   (extra debugger commands)
"""
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

from config import REPO, load_config

CDB = Path(r"C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\cdb.exe")
SETTINGS = ("config.qsc", "config.qvm")


def main():
    seconds = int(sys.argv[1]) if len(sys.argv) > 1 else 90
    args = sys.argv[2:] or ["Window", "WinInput"]  # windowed, with the mouse read from window messages
    game = Path(load_config()["game_dir"])
    # IGI2_BUILD picks another build directory (build/cmake-nofb: without the fallback's flags)
    exe = REPO / "build" / os.environ.get("IGI2_BUILD", "cmake") / "Release" / "igi2.exe"
    # a fatal error shows a message box first: stop there too, with the stack that raised it;
    # IGI2_CDB adds commands first (breakpoints that log as the game runs)
    commands = os.environ.get("IGI2_CDB", "") + ('bu user32!MessageBoxA ".echo ===EVENT===; .echo message box; da poi(esp+8); kn 40; '
                '.echo ===STACK===; .echo ===END===; q"; '
                "g; .echo ===EVENT===; .lastevent; r; .ecxr; kn 40; .echo ===ARGS===; kb 12; .echo ===STACK===; dps esp L800; .echo ===END===; q")
    with tempfile.TemporaryDirectory() as backup:
        for name in SETTINGS:
            if (game / name).exists():
                shutil.copy2(game / name, Path(backup) / name)
        try:
            r = subprocess.run([str(CDB), "-G", "-lines", "-y", str(exe.parent), "-c", commands, str(exe), *args],
                               cwd=game, capture_output=True, text=True, errors="replace", timeout=seconds)
            out = r.stdout
        except subprocess.TimeoutExpired as e:
            # subprocess killed cdb, and a debugger that goes takes its debuggee with it
            out = (e.stdout or b"").decode(errors="replace") if isinstance(e.stdout, bytes) else (e.stdout or "")
            out += f"\n=== still running after {seconds}s: stopped ===\n"
        finally:
            for name in SETTINGS:
                if (Path(backup) / name).exists():
                    shutil.copy2(Path(backup) / name, game / name)
    (REPO / "build" / "run.log").write_text(out)
    keep = [l for l in out.splitlines() if not l.startswith(("NatVis", "ModLoad"))]
    start = next((i for i, l in enumerate(keep) if "CommandLine:" in l), 0)
    print("\n".join(keep[start:])[-6000:])


if __name__ == "__main__":
    main()
