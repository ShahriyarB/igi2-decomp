"""Where the player first differs, by field: the replay (runtime/replay.c) dumps the whole
HumanPlayer_t every frame (IGI2_REPLAY_DUMP); this runs a script all retail and as our C, finds
the first frame whose bytes differ, and names the fields from the offsetof assertions of
include/generated/igi2_types.h. A field names the code that writes it, without bisecting. Pointers hold
addresses that differ from run to run: for them only whether they are set is compared.

usage: uv run replay_fields.py <script.rpl> [selection for ours, default: all C] [frames to show=3]
"""
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

from config import REPO

WORK = REPO / "build" / "replay"
TYPES = (REPO / "include" / "generated" / "igi2_types.h").read_text(errors="replace")
ROOT = "HumanPlayer_t"
SIZE = int(re.search(rf"sizeof\(struct {ROOT}\) == (\d+)", TYPES).group(1))

sizes = {m.group(1): int(m.group(2)) for m in re.finditer(r"sizeof\((?:struct|union) (\w+)\) == (\d+)", TYPES)}
offsets = {}
for m in re.finditer(r"offsetof\((?:struct|union) (\w+), (\w+)\) == (\d+)", TYPES):
    offsets.setdefault(m.group(1), []).append((int(m.group(3)), m.group(2)))
member_type = {}
pointer_members = set()
for m in re.finditer(r"^(struct|union) (\w+) \{\n(.*?)^\};", TYPES, re.M | re.S):
    for line in m.group(3).splitlines():
        t = re.match(r"\s*(?:struct|union) (\w+) (\w+)(\[[\d\]\[]+)?;", line)
        if t:
            member_type[(m.group(2), t.group(2))] = (t.group(1), t.group(3) or "")
        ptr = re.match(r"\s*[^;(]*\*\s*(?:const\s+)?(\w+)(?:\[[\d\]\[]+)?;", line) or \
            re.match(r"\s*[^;]*\(\s*(?:__\w+\s*)?\*+\s*(\w+)(?:\[[\d\]\[]+)?\)\s*\(", line)
        if ptr:
            pointer_members.add((m.group(2), ptr.group(1)))


def field_info(struct_name, off, depth=0):
    """(dotted member path of a byte offset inside a struct, start offset of that field, is pointer)"""
    best = None
    for o, name in sorted(offsets.get(struct_name, [])):
        if o <= off:
            best = (o, name)
    if not best or depth > 8:
        return f"+{off}", off, False
    o, name = best
    sub = member_type.get((struct_name, name))
    if sub and sub[0] in sizes:
        if not sub[1]:
            path, start, ptr = field_info(sub[0], off - o, depth + 1)
            return f"{name}.{path}", o + start, ptr
        n = (off - o) // sizes[sub[0]]
        path, start, ptr = field_info(sub[0], off - o - n * sizes[sub[0]], depth + 1)
        return f"{name}[{n}].{path}", o + n * sizes[sub[0]] + start, ptr
    return name, o, (struct_name, name) in pointer_members


def run(script, selection, tag, later=""):
    WORK.mkdir(parents=True, exist_ok=True)
    dump = WORK / f"{tag}.dump"
    dump.unlink(missing_ok=True)
    env = dict(os.environ, IGI2_FALLBACK=selection, IGI2_FALLBACK_LATER=later,
               IGI2_REPLAY=str(Path(script).resolve()), IGI2_REPLAY_LOG=str(WORK / f"{tag}.log"),
               IGI2_REPLAY_DUMP=str(dump), IGI2_FALLBACK_LOG=str(WORK / f"{tag}.fallback.log"))
    env.pop("IGI2_BUILD", None)
    env.pop("IGI2_CDB", None)
    subprocess.run(["uv", "run", "-q", "run.py", "900"], cwd=REPO / "tools" / "debug", env=env, capture_output=True)
    data = dump.read_bytes() if dump.exists() else b""
    rec = 4 + SIZE
    return {struct.unpack_from("<i", data, i)[0]: data[i + 4:i + rec] for i in range(0, len(data) - rec + 1, rec)}


def is_code(v):
    """an address in the retail code (0x401000..) or in ours (the exe is based at 0x10000)"""
    return 0x401000 <= v < 0x6A0000 or 0x11000 <= v < 0x400000


def differences(a, b):
    """{(field, start): [byte offsets]} of what differs, addresses compared only for being set,
    and a retail code address against one of ours (a handler the field points at) as alike"""
    fields = {}
    for i in range(SIZE):
        if a[i] == b[i]:
            continue
        name, start, ptr = field_info(ROOT, i)
        if ptr and (a[start:start + 4] == b"\0" * 4) == (b[start:start + 4] == b"\0" * 4):
            continue
        if start + 4 <= SIZE and is_code(int.from_bytes(a[start:start + 4], "little")) and \
                is_code(int.from_bytes(b[start:start + 4], "little")):
            continue
        fields.setdefault((name, start), []).append(i)
    return fields


# intersection fields the code leaves unset for terrain hits: stack garbage in both runs
IGNORED = re.compile(r"\.(iSector|iFace|iPortal|tHitUV\.\w+|vLight)$")


NOISY = set()   # fields that differ between two identical runs (timers, counters)


def learn_noise(script, base):
    """fields two all-retail runs disagree on: what changes from run to run, not with the code"""
    other = run(script, "all", "bnoise")
    for frame in sorted(set(base) & set(other)):
        NOISY.update(name for name, _ in differences(base[frame], other[frame]))
    print(f"fields that vary from run to run: {sorted(NOISY)[:12]}{' ...' if len(NOISY) > 12 else ''}")


def first_frame(base, ours):
    for frame in sorted(set(base) & set(ours)):
        fields = {k: v for k, v in differences(base[frame], ours[frame]).items()
                  if not IGNORED.search(k[0]) and k[0] not in NOISY}
        if fields:
            return frame, fields
    if len(ours) < len(base):
        return (max(ours) + 1 if ours else 0), {("(run ended)", 0): []}
    return None, {}


def bisect(script, names):
    """the functions whose C makes the player's bytes first differ; the script's "switch" frame
    makes them C (the load stays retail), and a subset counts when it differs no later than the
    whole set does"""
    base = run(script, "all", "bbase")
    learn_noise(script, base)
    path = WORK / "c_set.txt"
    target = [None]
    k = [0]

    def bad(subset):
        k[0] += 1
        path.write_text("\n".join(subset) + "\n")
        frame, fields = first_frame(base, run(script, "all", f"b{k[0]}", later=f"@{path}"))
        if target[0] is None:
            target[0] = frame
        verdict = frame is not None and frame <= target[0]
        print(f"  {len(subset):5d} as C -> " + (f"frame {frame}: {next(iter(fields))[0]}" if frame is not None else "same"),
              flush=True)
        return verdict

    def find(names, fixed):
        while len(names) > 1:
            a, b = names[:len(names) // 2], names[len(names) // 2:]
            if bad(fixed + a):
                names = a
            elif bad(fixed + b):
                names = b
            else:
                print(f"  neither half of {len(names)} alone: narrowing each with the other kept", flush=True)
                found_b = find(b, fixed + a)
                return find(a, fixed + found_b) + found_b
        return names

    if not bad(names):
        print("no difference")
        return
    print("found: " + ", ".join(find(names, [])))


def main():
    if sys.argv[1] == "bisect":
        names = [l.strip() for l in Path(sys.argv[3]).read_text().splitlines() if l.strip()]
        bisect(sys.argv[2], names)
        return
    script = sys.argv[1]
    selection = sys.argv[2] if len(sys.argv) > 2 else ""
    show = int(sys.argv[3]) if len(sys.argv) > 3 else 3
    base = run(script, "all", "fbase")
    ours = run(script, selection, "fours")
    print(f"frames: retail {len(base)}, ours {len(ours)}")
    shown = 0
    for frame in sorted(set(base) & set(ours)):
        fields = differences(base[frame], ours[frame])
        if not fields:
            continue
        print(f"frame {frame}: {len(fields)} fields differ")
        for (name, start), idx in list(fields.items())[:25]:
            hi = max(idx[-1] + 1, start + 4)
            print(f"  {name:70s} retail {base[frame][start:hi].hex()} ours {ours[frame][start:hi].hex()}")
        shown += 1
        if shown >= show:
            break
    if not shown:
        print("no difference in the player")


if __name__ == "__main__":
    main()
