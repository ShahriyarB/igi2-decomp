"""Start a hand fix: copy a function's decompiled text to overrides/<name>.c and list its errors.

usage: uv run override_start.py <function name> [--show]   (--show prints, writes nothing)
The exporter then uses overrides/<name>.c instead of decompiling that function.
"""
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

from config import REPO


def find(name):
    status = json.loads((REPO / "build" / "export_status.json").read_text())
    st = status.get(name)
    if not st:
        raise SystemExit(f"{name}: not an exported function")
    path = REPO / "src" / st["file"]
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    sig = re.compile(r"\b" + re.escape(name) + r"\s*\(")
    for i, line in enumerate(lines):
        if sig.search(line) and not line.startswith((" ", "\t")) and not line.rstrip().endswith(";"):
            start = i
            while start > 0 and lines[start - 1].startswith("//"):
                start -= 1
            end = next(j for j in range(i, len(lines)) if lines[j] == "}")
            return path, start, end, lines
    raise SystemExit(f"{name}: definition not found in {path}")


def main():
    name = sys.argv[1]
    path, start, end, lines = find(name)
    census = json.loads((REPO / "build" / "census.json").read_text())
    errs = [(int(e["line"]), e["code"], e["msg"]) for _, v in census for e in v
            if e["file"].replace("\\", "/").endswith(str(path.relative_to(REPO)).replace("\\", "/"))
            and start < int(e["line"]) <= end + 1]
    text = "\n".join(lines[start:end + 1])
    if "--show" in sys.argv:
        print(text)
    else:
        out = REPO / "overrides" / f"{name}.c"
        out.write_text(text + "\n", encoding="utf-8")
        print(f"wrote {out.relative_to(REPO)} ({end - start + 1} lines)")
    for n, code, msg in sorted(set(errs)):
        print(f"  line {n - start}: {code} {msg[:110]}")


if __name__ == "__main__":
    main()
