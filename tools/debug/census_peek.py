"""Show source and preprocessed text for the first errors of the given census buckets.

usage: uv run census_peek.py <error code> [count]
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

import msvc
from config import REPO

code, count = sys.argv[1], int(sys.argv[2]) if len(sys.argv) > 2 else 4
buckets = dict(json.loads((REPO / "build" / "census.json").read_text()))
key = next(k for k in buckets if k.startswith(code))
print("==", len(buckets[key]), key)
seen = set()
for e in buckets[key]:
    if e["file"] in seen:
        continue
    seen.add(e["file"])
    n = int(e["line"])
    src = open(e["file"], encoding="utf-8", errors="replace").read().splitlines()
    print(f"-- {e['file'].split('igi2-decomp')[-1]}:{n} [{e['function']}] {e['msg'][:80]}")
    print("   src:", src[n - 1].strip()[:200] if n <= len(src) else "?")
    r = msvc.run(["cl", "/nologo", "/E", "/TC", f"/I{REPO / 'include'}", e["file"]])
    pp = r.stdout.splitlines()
    marker = src[n - 1].strip()[:25] if n <= len(src) else None
    hit = next((l for l in pp if marker and l.strip().startswith(marker[:12])), None)
    if hit:
        print("   pp: ", hit.strip()[:300])
    if len(seen) >= count:
        break
