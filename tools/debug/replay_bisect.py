"""Find the decompiled functions behind a behaviour difference, with no one at the keyboard.

A replay script (runtime/replay.c) drives the game the same way every run, one tick per frame,
and logs the player's state each frame. The baseline runs every function as retail code
(IGI2_FALLBACK=all); a test runs a set of functions as our C and the rest as retail. Where the
logs first part is where that set misbehaves. Halving the set until one function is left needs
about log2(n) runs of a minute or two each.

usage:
  uv run replay_bisect.py check  <script.rpl>                        two baselines agree?
  uv run replay_bisect.py diff   <script.rpl> [selection]            baseline vs a selection
  uv run replay_bisect.py bisect <script.rpl> <candidates.txt|file:..> find the function(s)
In "bisect" every run starts all retail and the candidates become C at the script's "switch"
frame (runtime/replay.c), so the mission loads unmixed; put the switch after the load.
Selections use runtime/fallback.c's syntax ("all" = everything retail). Candidates are function
names, one per line, or "file:<text>" for every function of files containing that text.
"""
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

from config import REPO

WORK = REPO / "build" / "replay"
TABLE = REPO / "data" / "fallback_gen.c"


def table():
    """[(name, file)] of every function the fallback can switch"""
    return re.findall(r'^    \{ "(\w+)", "([^"]+)",', TABLE.read_text(), re.M)


def run(script, selection, tag, seconds=900, later=""):
    """one replay; returns its log lines. later: what becomes C at the script's "switch" frame"""
    WORK.mkdir(parents=True, exist_ok=True)
    log = WORK / f"{tag}.log"
    log.unlink(missing_ok=True)
    env = dict(os.environ, IGI2_FALLBACK=selection, IGI2_REPLAY=str(Path(script).resolve()),
               IGI2_REPLAY_LOG=str(log), IGI2_FALLBACK_LOG=str(WORK / f"{tag}.fallback.log"),
               IGI2_FALLBACK_LATER=later)
    env.pop("IGI2_BUILD", None)
    env.pop("IGI2_CDB", None)
    subprocess.run(["uv", "run", "-q", "run.py", str(seconds)], cwd=REPO / "tools" / "debug", env=env,
                   capture_output=True, text=True)
    crash = ""
    out = (REPO / "build" / "run.log").read_text(errors="replace")
    (WORK / f"{tag}.run.log").write_text(out, errors="replace")  # each run's debugger output stays
    m = re.search(r"^===EVENT===$", out, re.M)  # a line of its own: cdb also echoes its commands
    if m:
        crash = "\n".join(l for l in out[m.end():].splitlines() if not l.startswith(("NatVis", "ModLoad")))[:600]
    lines = log.read_text(errors="replace").splitlines() if log.exists() else []
    return lines, crash


def first_difference(a, b):
    """(frame, line a, line b) where two logs first part, or None"""
    for x, y in zip(a, b):
        if x != y:
            return x.split(" ", 1)[0], x, y
    if len(a) != len(b):
        longer = a if len(a) > len(b) else b
        return longer[min(len(a), len(b))].split(" ", 1)[0], "(log ends)" if len(a) < len(b) else longer[len(b)], \
            "(log ends)" if len(b) < len(a) else longer[len(a)]
    return None


def selection_with_c(names):
    """everything retail except these, which run as our C"""
    path = WORK / "c_set.txt"
    path.write_text("\n".join("-" + n for n in names) + "\n")
    return f"all,@{path}"


def candidates(spec):
    if spec.startswith("file:"):
        return [n for n, f in table() if spec[5:] in f]
    return [l.strip() for l in Path(spec).read_text().splitlines() if l.strip() and not l.startswith("#")]


def main():
    cmd, script = sys.argv[1], sys.argv[2]
    if cmd == "check":
        a, ca = run(script, "all", "base1")
        b, cb = run(script, "all", "base2")
        print(f"baseline lines {len(a)}, {len(b)}; crash: {bool(ca)} {bool(cb)}")
        d = first_difference(a, b)
        print("baselines agree" if not d else f"baselines differ at frame {d[0]}:\n  {d[1]}\n  {d[2]}")
        return
    base, crash = run(script, "all", "base")
    if crash:
        print("baseline crashed:\n" + crash)
        return
    if cmd == "diff":
        sel = sys.argv[3] if len(sys.argv) > 3 else ""
        test, crash = run(script, sel, "test")
        d = first_difference(base, test)
        print(f"lines {len(base)} vs {len(test)}" + (f"; crash:\n{crash}" if crash else ""))
        print("same" if not d else f"first difference at frame {d[0]}:\n  retail {d[1]}\n  ours   {d[2]}")
        return
    names = candidates(sys.argv[3])
    print(f"{len(names)} candidates")
    if cmd == "fix":
        # all C shows the difference at frame T; find the functions whose retail code removes it.
        # Most of the program stays C in every run, as in the real build.
        ours, crash = run(script, "", "ours")
        d = first_difference(base, ours)
        if not d:
            print("our build matches the baseline: nothing to fix")
            return
        target = int(d[0])
        print(f"target: our build first differs at frame {target}\n  retail {d[1]}\n  ours   {d[2]}")

        def verdict(subset, tag):
            path = WORK / "retail_set.txt"
            path.write_text("\n".join(subset) + "\n")
            test, crash = run(script, f"@{path}", tag)
            d = first_difference(base, test)
            frame = int(d[0]) if d and d[0].isdigit() else None
            v = "fixed" if not crash and (not d or (frame is not None and frame > target)) else \
                ("still" if d and frame == target else "other")
            print(f"  {len(subset):5d} retail -> {v}" + (f" (frame {d[0]})" if d else "") + (" crash" if crash else ""), flush=True)
            return v

        if verdict(names, "rall") != "fixed":
            print("sending every candidate to retail does not remove it")
            return
        k = 0
        while len(names) > 1:
            half = len(names) // 2
            a, b = names[:half], names[half:]
            k += 1
            va = verdict(a, f"f{k}a")
            if va == "fixed":
                names = a
                continue
            vb = verdict(b, f"f{k}b")
            if vb == "fixed":
                names = b
                continue
            print(f"neither half alone removes it ({va}, {vb}). Remaining {len(names)}:")
            print("\n".join(names))
            return
        print(f"found: {names[0]}")
        return

    # The first difference the whole set makes is the one hunted: a subset that only differs
    # later shows another bug (one at a time), and stays out of this search.
    target = [None]

    def bad(subset, tag):
        path = WORK / "c_set.txt"
        path.write_text("\n".join(subset) + "\n")
        test, crash = run(script, "all", tag, later=f"@{path}")
        d = first_difference(base, test)
        frame = int(d[0]) if d and d[0].isdigit() else None
        if target[0] is None:
            target[0] = frame
            verdict = bool(d or crash)
        else:
            verdict = frame is not None and frame <= target[0]
        print(f"  {len(subset):5d} as C -> {'DIFFERS at ' + d[0] if d else ('crash' if crash else 'same')}"
              + ("" if verdict or not d else "  (later: another bug)"), flush=True)
        return verdict

    if not bad(names, "all"):
        print("the candidates as C match the baseline: nothing to find here")
        return
    print(f"hunting the difference at frame {target[0]}")
    counter = [0]

    def find(names, fixed):
        """the functions of names that, with fixed also C, make the difference: when neither half
        does it alone the difference needs both, so each half is narrowed with the other kept"""
        while len(names) > 1:
            half = len(names) // 2
            a, b = names[:half], names[half:]
            counter[0] += 1
            k = counter[0]
            if bad(fixed + a, f"r{k}a"):
                names = a
            elif bad(fixed + b, f"r{k}b"):
                names = b
            else:
                print(f"  neither half of {len(names)} alone: narrowing each with the other kept")
                found_b = find(b, fixed + a)
                found_a = find(a, fixed + found_b)
                return found_a + found_b
        return names

    found = find(names, [])
    print("found: " + ", ".join(found))


if __name__ == "__main__":
    main()
