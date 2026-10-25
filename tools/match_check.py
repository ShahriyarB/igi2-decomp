"""Independent check of symbols/match.json: functions whose strings name a function.

A retail function referencing a string that contains a pc function name (e.g. an error message
"HumanPlayer_Update: ...") is evidence. Per match method we count strings that name the matched
function (agree), name a function of the same prefix (near) or name an unrelated one (conflict).
"""
import collections
import json
import re

from config import REPO

IDENT = re.compile(r"[A-Za-z][A-Za-z0-9]*_[A-Za-z0-9_]+")


def main():
    m = json.loads((REPO / "symbols" / "match.json").read_text())
    fre = json.loads((REPO / "work" / "retail" / "fingerprints.json").read_text())
    names = {v["name"] for v in m.values()}
    strings = {f["ea"]: f["strings"] for f in fre["functions"]}
    stats = collections.defaultdict(collections.Counter)
    examples = collections.defaultdict(list)
    for v in m.values():
        if v["ea"] is None:
            continue
        mentioned = {t for s in strings.get(v["ea"], ()) for t in IDENT.findall(s) if t in names}
        if not mentioned:
            stats[v["how"]]["no evidence"] += 1
            continue
        if v["name"] in mentioned:
            stats[v["how"]]["agree"] += 1
        elif any(t.split("_")[0] == v["name"].split("_")[0] for t in mentioned):
            stats[v["how"]]["same prefix"] += 1
        else:
            stats[v["how"]]["conflict"] += 1
            examples[v["how"]].append((v["name"], hex(v["ea"]), sorted(mentioned)[:3]))
    for how, c in sorted(stats.items()):
        print(f"{how:12s} {dict(c)}")
        for e in examples[how][:4]:
            print("      conflict:", e)


if __name__ == "__main__":
    main()
