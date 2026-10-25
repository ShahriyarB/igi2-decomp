"""Map every function of the Final client PDB (2003-01-06) to its address in the retail exe.

The Final client build ("Unknown/igi2.pdb", obj\\Final) is the retail configuration 25 days
earlier: same object order, 87 % of functions byte-for-byte the same size. So:

1. Anchors: the DS 1.2 exe (exact PDB, real bytes) is matched to retail by code fingerprints
   (unique hashes, string sets, callee/caller propagation, mnemonic hashes); DS names give
   final rva -> retail ea for the shared code.
2. Anchors that break link order are dropped (longest increasing subsequence).
3. Between anchors, Final functions are aligned to retail functions by size (dynamic
   programming; equal size is free), which also covers the client-only renderer/sound/input.

Output: symbols/match.json {final rva: {name, obj, ea, how, cost}} and data_match.json.
"""
import bisect
import collections
import json
import ntpath

from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))  # tools/: config, msvc, sysnames, pdbfile

from config import REPO, load_config

IMAGEBASE = 0x400000
CLIENT = "final"  # symbols/<CLIENT>.json is the client PDB the names and types come from


def load(path):
    return json.loads((REPO / path).read_text())


def objbase(obj):
    return ntpath.basename(obj.replace("/", "\\")).lower()


def size_cost(a, b):
    return abs(a - b) / max(a, b, 1)


def retail_bytes():
    """The retail exe's loaded bytes by address: {va: byte} as a bytearray from IMAGEBASE."""
    import struct
    pe = Path(load_config()["retail_exe"]).read_bytes()
    peo = struct.unpack_from("<I", pe, 0x3C)[0]
    nsec, opt_size = struct.unpack_from("<H", pe, peo + 6)[0], struct.unpack_from("<H", pe, peo + 20)[0]
    image = bytearray()
    for k in range(nsec):
        _, vsize, va, rsize, roff = struct.unpack_from("<8sIIII", pe, peo + 24 + opt_size + 40 * k)
        n = min(vsize, rsize) if vsize else rsize
        if len(image) < va + n:
            image.extend(bytes(va + n - len(image)))
        image[va:va + n] = pe[roff:roff + n]
    return image


def aligned_start(image, ea):
    """Every game function starts 16-byte aligned. For an unaligned start IDA chose: if only
    padding lies between it and the next aligned address, the function starts there; otherwise
    IDA began inside it (after a misdecoded instruction) and it starts at the aligned address before."""
    up = (ea + 15) & ~15
    if all(image[a - IMAGEBASE] in (0xCC, 0x90) for a in range(ea, up)):
        return up
    return ea & ~15


# ---- code fingerprints -------------------------------------------------------------------------
def match_code(fa, fb):
    """Pairs a.ea -> b.ea between two fingerprint sets."""
    A = {f["ea"]: f for f in fa["functions"]}
    B = {f["ea"]: f for f in fb["functions"]}
    pairs, how, taken = {}, {}, set()

    def add(a, b, why):
        if a in pairs or b in taken:
            return False
        pairs[a] = b
        taken.add(b)
        how[a] = why
        return True

    def close(x, y):
        return abs(A[x]["size"] - B[y]["size"]) <= max(16, A[x]["size"] // 4)

    def unique_by(keyf, why, min_insn=4):
        ka, kb = collections.defaultdict(list), collections.defaultdict(list)
        for f in A.values():
            if f["ea"] not in pairs and f["ninsn"] >= min_insn and (k := keyf(f)):
                ka[k].append(f["ea"])
        for f in B.values():
            if f["ea"] not in taken and f["ninsn"] >= min_insn and (k := keyf(f)):
                kb[k].append(f["ea"])
        return sum(add(la[0], kb[k][0], why) for k, la in ka.items()
                   if len(la) == 1 and len(kb.get(k, ())) == 1)

    def propagate():
        n = 0
        for a, b in list(pairs.items()):
            ca, cb = A[a]["calls"], B[b]["calls"]
            if len(ca) == len(cb):
                for x, y in zip(ca, cb):
                    if x in A and y in B and x not in pairs and y not in taken and close(x, y):
                        n += add(x, y, "callee")
            ua = [x for x in A[a]["callers"] if x not in pairs]
            ub = [y for y in B[b]["callers"] if y not in taken]
            if len(ua) == 1 and len(ub) == 1 and close(ua[0], ub[0]):
                n += add(ua[0], ub[0], "caller")
        return n

    unique_by(lambda f: f["hash"], "hash", min_insn=6)
    unique_by(lambda f: tuple(f["strings"]) if f["strings"] else None, "strings", min_insn=1)
    while propagate():
        pass
    for _ in range(3):
        unique_by(lambda f: f["hash"], "hash", min_insn=3)
        unique_by(lambda f: (tuple(sorted(set(f["strings"]))), tuple(f["imports"]))
                  if f["strings"] or f["imports"] else None, "refs", min_insn=1)
        unique_by(lambda f: f["mhash"], "mhash", min_insn=8)
        while propagate():
            pass
    return pairs, how


def lis(items):
    """items sorted by x: the longest subsequence increasing in y."""
    tails, tails_i, prev = [], [], [-1] * len(items)
    for i, (_, y) in enumerate(items):
        k = bisect.bisect_left(tails, y)
        if k == len(tails):
            tails.append(y)
            tails_i.append(i)
        else:
            tails[k], tails_i[k] = y, i
        prev[i] = tails_i[k - 1] if k else -1
    out, i = [], tails_i[-1] if tails_i else -1
    while i >= 0:
        out.append(items[i])
        i = prev[i]
    return out[::-1]


def align(xs, ys, pair_cost, gap=1.0, limit=4_000_000):
    """Global alignment; pair_cost(x, y) -> cost or None (not allowed). Returns [(i, j, cost)]."""
    n, m = len(xs), len(ys)
    if not n or not m or n * m > limit:
        return []
    INF = float("inf")
    dp = [[INF] * (m + 1) for _ in range(n + 1)]
    bt = [[0] * (m + 1) for _ in range(n + 1)]
    dp[0][0] = 0.0
    for i in range(n + 1):
        row, nrow = dp[i], dp[i + 1] if i < n else None
        for j in range(m + 1):
            d = row[j]
            if d == INF:
                continue
            if nrow is not None and d + gap < nrow[j]:
                nrow[j] = d + gap
                bt[i + 1][j] = 1
            if j < m and d + gap < row[j + 1]:
                row[j + 1] = d + gap
                bt[i][j + 1] = 2
            if nrow is not None and j < m:
                c = pair_cost(xs[i], ys[j])
                if c is not None and d + c < nrow[j + 1]:
                    nrow[j + 1] = d + c
                    bt[i + 1][j + 1] = 3
    out, i, j = [], n, m
    while i or j:
        b = bt[i][j]
        if b == 3:
            out.append((i - 1, j - 1, pair_cost(xs[i - 1], ys[j - 1])))
            i, j = i - 1, j - 1
        elif b == 1:
            i -= 1
        else:
            j -= 1
    return out[::-1]


# ---- globals ------------------------------------------------------------------------------------
def match_data(fn_pairs, ffa, ffb, sym_a, sym_client, base_a=IMAGEBASE):
    """Globals: zip the ordered data references of function pairs with identical instruction
    shape; each reference votes for retail_base = retail_addr - (addr_a - global_a_start).
    sym_a names/sizes the globals of side A; sym_client supplies the type text."""
    A = {f["ea"]: f for f in ffa["functions"]}
    B = {f["ea"]: f for f in ffb["functions"]}
    glob = sorted(((base_a + d["rva"], d) for d in sym_a["data"] if d["rva"] is not None),
                  key=lambda x: x[0])
    starts = [g for g, _ in glob]
    votes = collections.defaultdict(collections.Counter)
    for a, b in fn_pairs.items():
        fa, fb = A.get(a), B.get(b)
        if not fa or not fb or fa["mhash"] != fb["mhash"] or len(fa["drefs"]) != len(fb["drefs"]):
            continue
        for (ia, na, va), (ib, nb, vb) in zip(fa["drefs"], fb["drefs"]):
            if (ia, na) != (ib, nb):
                break
            k = bisect.bisect_right(starts, va) - 1
            if k < 0:
                continue
            g, d = glob[k]
            if va - g >= max(d["size"], 1):
                continue
            votes[g][vb - (va - g)] += 1
    by_key = {(objbase(sym_client["modules"][d["module"]]["name"]) if d["module"] is not None else None,
               d["name"]): d for d in sym_client["data"]}
    by_name = collections.defaultdict(list)
    for d in sym_client["data"]:
        by_name[d["name"]].append(d)
    out, used = {}, set()
    for g, c in votes.items():
        base, n = c.most_common(1)[0]
        if base in used or n < max(1, sum(c.values()) // 2):
            continue
        d = glob[bisect.bisect_left(starts, g)][1]
        obj = objbase(sym_a["modules"][d["module"]]["name"]) if d["module"] is not None else None
        p = by_key.get((obj, d["name"])) or (by_name[d["name"]][0] if len(by_name[d["name"]]) == 1 else None)
        out[base] = {"name": d["name"], "obj": obj, "static": d["static"], "size": d["size"],
                     "votes": n, "ctype": (p or d)["ctype"], "type_from": CLIENT if p else "ds12"}
        used.add(base)
    return out


def predict_globals(cl, seeds, referenced, window=4):
    """Every client global at final address + the local shift its neighbours agree on.

    seeds: {retail_base: {name, obj}} from match_data. Seeds voted with DS 1.2 offsets can be a
    few bytes off where a struct changed after January, so a seed only counts through the
    consensus of the seeds around it: a global is placed when the `window` seeds on each side
    agree on one shift. Where they disagree, the candidate shift whose address retail code
    references (`referenced`) wins, nearest seed first."""
    key = lambda d: (objbase(cl["modules"][d["module"]]["name"]) if d["module"] is not None else None,
                     d["name"])
    finals = sorted((d for d in cl["data"] if d["rva"] is not None), key=lambda d: d["rva"])
    addr = {key(d): IMAGEBASE + d["rva"] for d in finals}
    by_name = collections.defaultdict(list)
    for d in finals:
        by_name[d["name"]].append(d)
    pts = []
    for base, s in seeds.items():
        k = (s["obj"], s["name"])
        f = addr.get(k) or (IMAGEBASE + by_name[s["name"]][0]["rva"] if len(by_name[s["name"]]) == 1 else None)
        if f is not None:
            pts.append((f, base - f))
    pts.sort()
    xs = [p for p, _ in pts]
    out = {}
    for d in finals:
        f = IMAGEBASE + d["rva"]
        k = bisect.bisect_left(xs, f)
        left = [s for _, s in pts[max(0, k - window):k]]
        right = [s for _, s in pts[k:k + window]]
        exact = k < len(xs) and xs[k] == f
        cand = collections.Counter(left + right).most_common(1)
        if not cand:
            continue
        shift, n = cand[0]
        how = "consensus"
        if n < len(left + right) - 1 or not left or not right or left[-1] != shift or right[0] != shift:
            # neighbours disagree (the layout changed around here): nearest referenced candidate
            near = sorted({s for s in left + right},
                          key=lambda s: min(abs(p - f) for p, q in pts[max(0, k - window):k + window] if q == s))
            shift = next((s for s in near if f + s in referenced), None)
            if shift is None:
                continue
            how = "referenced"
        out[f + shift] = {"name": d["name"], "obj": key(d)[0], "static": d["static"], "size": d["size"],
                          "ctype": d["ctype"], "final_rva": d["rva"], "shift": shift,
                          "seeded": exact, "how": how}
    return out


def main():
    cl = load(f"symbols/{CLIENT}.json")
    ds = load("symbols/ds12.json")
    fds = load("work/ds12/fingerprints.json")
    fre = load("work/retail/fingerprints.json")

    # 1. anchors through DS 1.2
    pairs, how = match_code(fds, fre)
    ds_name = {IMAGEBASE + f["rva"]: (objbase(ds["modules"][f["module"]]["name"]), f["name"])
               for f in ds["functions"] if f["rva"] is not None}
    funcs = sorted((f for f in cl["functions"] if f["rva"] is not None and f["length"]),
                   key=lambda f: f["rva"])
    obj_of = {f["rva"]: objbase(cl["modules"][f["module"]]["name"]) for f in funcs}
    by_key = {(obj_of[f["rva"]], f["name"]): i for i, f in enumerate(funcs)}
    retail = sorted(fre["functions"], key=lambda f: f["ea"])
    ridx = {f["ea"]: j for j, f in enumerate(retail)}
    anchors = sorted((by_key[ds_name[a]], ridx[b], how[a]) for a, b in pairs.items()
                     if a in ds_name and ds_name[a] in by_key)
    kept = lis([(i, j) for i, j, _ in anchors])
    anchor_how = {i: h for i, _, h in anchors}
    print(f"DS 1.2 <-> retail code pairs {len(pairs)}; {CLIENT} anchors {len(anchors)}, in order {len(kept)}")

    # 2/3. align between anchors
    result = {i: (j, "anchor-" + anchor_how[i], 0.0) for i, j in kept}

    def cost(f, r):
        # same compiler and linker: a function 16-byte aligned in the Final build is aligned in
        # retail too (95 % are); a pair that disagrees is mid-function code or junk
        if ((IMAGEBASE + f["rva"]) % 16 == 0) != (r["ea"] % 16 == 0):
            return None
        c = size_cost(f["length"], r["size"])
        return 0.0 if c == 0 else (None if c > 0.5 else 0.3 + 2 * c)

    bounds = [(-1, -1)] + kept + [(len(funcs), len(retail))]
    for (i0, j0), (i1, j1) in zip(bounds, bounds[1:]):
        xs, ys = funcs[i0 + 1:i1], retail[j0 + 1:j1]
        for a, b, c in align(xs, ys, cost):
            result[i0 + 1 + a] = (j0 + 1 + b, "size" if c == 0 else "size~", round(c, 3))

    # between two anchors exactly as far apart in both builds, the code in between is laid out
    # the same: every function is at its Final offset from the first anchor, whether or not IDA
    # found it there (cursor.c: a size guess paired Cursor_IsMoved with Cursor_SetSprite, the
    # one 4-byte function IDA had defined in a run of seven)
    retail_at = {r["ea"]: j for j, r in enumerate(retail)}
    placed = {}
    for (i0, j0), (i1, j1) in zip(kept, kept[1:]):
        if i1 - i0 < 2 or retail[j1]["ea"] - retail[j0]["ea"] != funcs[i1]["rva"] - funcs[i0]["rva"]:
            continue
        for i in range(i0 + 1, i1):
            ea = retail[j0]["ea"] + funcs[i]["rva"] - funcs[i0]["rva"]
            j = retail_at.get(ea)
            if result.get(i, (None,))[0] != j or j is None:
                placed[i] = ea
                result[i] = (j, "layout", 0.0)

    # pairs checked by hand and found wrong: a same-size neighbour that is other code
    rejected = {k for k in json.loads((REPO / "overrides" / "match_reject.json").read_text()) if k != "_comment"}
    code = retail_bytes()
    out = {}
    for i, f in enumerate(funcs):
        j, h, c = result.get(i, (None, "unmatched", None))
        if f["name"] in rejected:
            j, h, c = None, "rejected", None
        ea = retail[j]["ea"] if j is not None else placed.get(i)
        if h == "rejected":
            ea = None
        if ea is not None and ea % 16 and (IMAGEBASE + f["rva"]) % 16 == 0:
            ea = aligned_start(code, ea)  # an anchor on a start IDA got wrong (strings, callers)
        out[str(f["rva"])] = {"name": f["name"], "obj": obj_of[f["rva"]],
                              "lib": objbase(cl["modules"][f["module"]]["lib"]), "length": f["length"],
                              "static": f["static"], "ea": ea,
                              "retail_size": retail[j]["size"] if j is not None else (f["length"] if ea else None),
                              "how": h, "cost": c}
    (REPO / "symbols" / "match.json").write_text(json.dumps(out, indent=1))

    by_how = collections.Counter(v["how"].split("-")[0] for v in out.values())
    exact = sum(1 for v in out.values() if v["ea"] is not None and v["length"] == v["retail_size"])
    print(f"{CLIENT} functions {len(funcs)}: {dict(by_how)}; matched with identical size {exact}")
    per_lib = collections.defaultdict(collections.Counter)
    for v in out.values():
        per_lib[v["lib"] or "(direct)"][v["ea"] is not None] += 1
    for lib, c in sorted(per_lib.items(), key=lambda kv: -sum(kv[1].values())):
        print(f"  {lib:14s} matched {c[True]} / {c[True] + c[False]}")
    named = {v["ea"] for v in out.values() if v["ea"] is not None}
    print(f"retail functions named {len(named)} of {len(retail)}")

    # globals: DS 1.2 pairs seed the shift; every Final global is placed by local consensus
    seeds = match_data(pairs, fds, fre, ds, cl)
    referenced = {v for f in fre["functions"] for _, _, v in f["drefs"]}
    data = predict_globals(cl, seeds, referenced)
    (REPO / "symbols" / "data_match.json").write_text(
        json.dumps({str(k): v for k, v in sorted(data.items())}, indent=1))
    moved = sum(1 for base, s in seeds.items() if base not in data)
    print(f"globals: {len(seeds)} seeds from DS 1.2 code, {len(data)} of "
          f"{sum(1 for d in cl['data'] if d['rva'] is not None)} {CLIENT} globals placed "
          f"({moved} seeds overruled by their neighbours)")


if __name__ == "__main__":
    main()
