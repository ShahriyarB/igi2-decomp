"""Rebuild the retail function set and the matches from the analysis-only IDB.

  analysis-only copy -> create matched/predicted functions -> fingerprint -> match   (x rounds)
  -> save as the functions-only base -> define functions the decompiled text references

usage: uv run rebuild_functions.py [rounds=2]
"""
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

from config import REPO

SYSTEM_PY = "python"


def run(cmd, **kw):
    print(">", " ".join(map(str, cmd)), flush=True)
    subprocess.run(cmd, check=True, **kw)


def main():
    rounds = int(sys.argv[1]) if len(sys.argv) > 1 else 2
    tools, retail = REPO / "tools" / "pipeline", REPO / "work" / "retail"
    idb = retail / "igi2_1.0.exe.i64"
    for _ in range(rounds):
        shutil.copyfile(retail / "igi2_1.0.exe.analysis-only.i64", idb)
        run([SYSTEM_PY, tools / "ida_define_missing.py"])
        run([SYSTEM_PY, tools / "ida_fingerprints.py", retail / "igi2_1.0.exe", retail / "fingerprints.json"])
        run(["uv", "run", "-q", "match.py"], cwd=tools)
    shutil.copyfile(retail / "igi2_1.0.exe.analysis-only.i64", idb)
    run([SYSTEM_PY, tools / "ida_define_missing.py"])
    shutil.copyfile(idb, retail / "igi2_1.0.exe.functions.i64")
    if (REPO / "src").exists():
        run([SYSTEM_PY, tools / "ida_define_referenced.py"])


if __name__ == "__main__":
    main()
