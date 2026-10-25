"""Compile every src/**.c and bucket the errors, so fixes go to the rule that clears the most.

usage: uv run census.py [--only <path substring>] [--show <bucket substring>]
writes build/census.json; prints buckets by count.
"""
import collections
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

import msvc
from config import REPO

ERR = re.compile(r"^(?P<file>.+?)\((?P<line>\d+)\): (?:fatal )?error (?P<code>C\d+): (?P<msg>.*)$")
UNINIT = re.compile(r"^(?P<file>.+?)\((?P<line>\d+)\) ?: warning C4700: uninitialized local variable '(?P<var>\w+)' used")
REGS = {"eax": 4, "ecx": 4, "edx": 4, "ebx": 4, "esi": 4, "edi": 4, "ebp": 4,
        "ax": 2, "cx": 2, "dx": 2, "bx": 2, "si": 2, "di": 2, "al": 1, "cl": 1, "dl": 1, "bl": 1}
FN_START = re.compile(r"^[A-Za-z_][\w\s\*\(\),@<>\[\]]*\b(\w+)\s*\(.*\)\s*$")


def bucket(code, msg):
    msg = re.sub(r"\s*\(compiling source file .*\)$", "", msg)
    msg = re.sub(r"'[^']*'", "'X'", msg)
    msg = re.sub(r"\b\d+\b", "N", msg)
    return f"{code}: {msg}"


def function_at(lines, n):
    """Name of the function whose body contains line n (1-based), scanning upwards."""
    for i in range(min(n, len(lines)) - 1, -1, -1):
        if lines[i] == "{" and i > 0:
            m = re.search(r"(\w+)\s*\(", lines[i - 1]) or (i > 1 and re.search(r"(\w+)\s*\(", lines[i - 2]))
            return m.group(1) if m else "?"
    return "?"


def write_register_hints(uninit, cache):
    """A variable the decompiler keeps in a register and reads before any write is, in the
    original, a register argument the prototype is missing (File_SubstituteAlias gets its
    destination in ecx). build/abi_hints.json {function: [[register, bytes]]} feeds the abi
    step of the next apply. Hints accumulate: once applied, a function's variable is an
    argument and no longer shows up, but its hint must keep being applied."""
    hints_path = REPO / "build" / "abi_hints.json"
    hints = collections.defaultdict(set)
    if hints_path.exists():
        for fn, regs in json.loads(hints_path.read_text()).items():
            hints[fn] |= {tuple(r) for r in regs}
    for w in uninit:
        path = w["file"]
        if ":" + chr(92) in path:  # parallel compiles can run two lines together: "DD:\..."
            path = path[path.rfind(":" + chr(92)) - 1:]
        if path not in cache:
            cache[path] = open(path, encoding="utf-8", errors="replace").read().splitlines()
        lines, n = cache[path], int(w["line"])
        fn = function_at(lines, n)
        for i in range(n - 1, max(0, n - 2000), -1):
            m = re.search(r"\b" + w["var"] + r"; // (\w+)$", lines[i])
            if m:
                if m.group(1) in REGS:
                    hints[fn].add((m.group(1), REGS[m.group(1)]))
                break
            if lines[i] == "{":
                break
    hints_path.write_text(
        json.dumps({fn: sorted(map(list, regs)) for fn, regs in sorted(hints.items())}, indent=1))
    print(f"register argument hints: {sum(map(len, hints.values()))} in {len(hints)} functions")


def main():
    only = sys.argv[sys.argv.index("--only") + 1] if "--only" in sys.argv else None
    show = sys.argv[sys.argv.index("--show") + 1] if "--show" in sys.argv else None
    files = sorted(p for p in (REPO / "src").rglob("*.c") if not only or only in p.as_posix())
    obj = REPO / "build" / "obj"
    obj.mkdir(parents=True, exist_ok=True)
    errors, uninit = [], []
    flags = ["/nologo", "/c", "/TC", "/std:c17", "/W1", "/O2", "/arch:IA32", "/permissive", f"/I{REPO / 'include'}"]
    # igi2.h (2.9 MB) parsed once into a precompiled header, then every file compiled in one
    # parallel cl run (a response file: the paths alone pass the command-line limit)
    pch, stub = obj / "igi2.pch", obj / "pch_stub.c"
    stub.write_text('#include "igi2.h"\n')
    r = msvc.run(["cl", *flags, "/Ycigi2.h", f"/Fp{pch}", f"/Fo{obj}\\", str(stub)], cwd=str(REPO))
    use_pch = r.returncode == 0
    if not use_pch:
        print("precompiled header failed, compiling without it:\n" + r.stdout[-2000:])
    rsp = obj / "census.rsp"
    rsp.write_text("\n".join([*flags, "/MP", *(["/Yuigi2.h", f"/Fp{pch}"] if use_pch else []), f"/Fo{obj}\\"]
                             + [f'"{p}"' for p in files]))
    for r in [msvc.run(["cl", f"@{rsp}"], cwd=str(REPO))]:
        for line in r.stdout.splitlines():
            m = ERR.match(line.strip())
            if m:
                errors.append(m.groupdict())
            m = UNINIT.match(line.strip())
            if m:
                uninit.append(m.groupdict())
    cache = {}
    buckets = collections.defaultdict(list)
    bad_funcs = set()
    for e in errors:
        path = e["file"]
        if path not in cache:
            try:
                cache[path] = open(path, encoding="utf-8", errors="replace").read().splitlines()
            except OSError:
                cache[path] = []
        fn = function_at(cache[path], int(e["line"]))
        bad_funcs.add((path, fn))
        buckets[bucket(e["code"], e["msg"])].append({**e, "function": fn})
    write_register_hints(uninit, cache)
    out = sorted(buckets.items(), key=lambda kv: -len(kv[1]))
    (REPO / "build" / "census.json").write_text(json.dumps(out, indent=1))
    bad_files = {e["file"] for e in errors}
    print(f"{len(files)} files, {len(bad_files)} with errors, {len(errors)} errors, "
          f"{len(bad_funcs)} functions affected")
    for k, v in out[:40]:
        print(f"{len(v):6d}  {k[:150]}")
    if show:
        for k, v in out:
            if show in k:
                for e in v[:15]:
                    print(f"   {e['file']}({e['line']}) [{e['function']}]: {e['msg'][:160]}")


if __name__ == "__main__":
    main()
