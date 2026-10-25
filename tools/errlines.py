"""Print the source lines the last census flagged, for files matching a substring.

usage: uv run errlines.py <path substring> [...]
"""
import json
import sys

from config import REPO

census = json.loads((REPO / "build" / "census.json").read_text())
rows = sorted({(e["file"], int(e["line"]), e["code"], e["msg"][:100]) for _, v in census for e in v})
for want in sys.argv[1:]:
    for path, line, code, msg in rows:
        if want.replace("/", "\\") in path or want in path:
            src = open(path, encoding="utf-8", errors="replace").read().splitlines()
            text = src[line - 1].strip()[:160] if line <= len(src) else "?"
            print(f"{path.split('igi2-decomp')[-1]}:{line} {code} {msg}\n      {text}")
