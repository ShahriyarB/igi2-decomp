"""Dump a PDB's functions, globals, modules and source layout to symbols/<name>.json.

usage: uv run gen_symbols.py <config key of the pdb> <out name>
       e.g.  uv run gen_symbols.py client_pdb pc
"""
import bisect
import collections
import json
import sys
from pathlib import Path

from config import load_config, REPO
from pdb.cdecl import TypeNamer
from pdb.dbi import Dbi
from pdb.msf import Msf
from pdb.symbols import global_symbols, module_symbols
from pdb.tpi import Tpi

STACK_PARAM_BASE = 8  # [ebp+8] is the first stack argument in a framed x86 function


def source_path(path):
    """c:\\project\\igi2\\j\\0\\weapons\\gun.c -> j/0/weapons/gun.c (None outside the game tree)."""
    p = path.replace("\\", "/")
    low = p.lower()
    key = "/project/igi2/"
    i = low.find(key)
    return p[i + len(key):].lower() if i >= 0 else None


def main():
    key, out_name = sys.argv[1], sys.argv[2]
    cfg = load_config()
    msf = Msf(cfg[key])
    dbi = Dbi(msf)
    tpi = Tpi(msf.stream(2))
    publics, gdata, udts = global_symbols(msf, dbi)
    namer = TypeNamer(tpi, {ti: n for n, ti in udts.items()})

    modules, functions, data = [], [], []
    kinds = collections.Counter()
    for mod in dbi.modules:
        entry = {"index": mod.index, "name": mod.name, "obj": mod.obj, "lib": mod.lib,
                 "files": [f for f in mod.files], "game_files": sorted(
                     {s for s in map(source_path, mod.files) if s})}
        modules.append(entry)
        if mod.stream == 0xFFFF:
            continue
        procs, mdata, compile_info, lines = module_symbols(msf, dbi, mod)
        entry["compile"] = compile_info
        # flatten line tables to a sorted (rva, file, line) index for the module
        index = sorted((rva, f, ln) for f, pairs in lines for rva, ln in pairs if rva is not None)
        rvas = [r for r, _, _ in index]
        for p in procs:
            kinds["static" if p["static"] else "global"] += 1
            lo = bisect.bisect_left(rvas, p["rva"])
            hi = bisect.bisect_left(rvas, p["rva"] + max(p["length"], 1))
            span = index[lo:hi]
            t = tpi.get(p["type"]) if p["type"] >= 0x1000 else None
            nparams = len(tpi[t["args"]]["args"]) if t and t["kind"] in ("procedure", "mfunction") else 0
            top = [l for l in p["locals"] if l["depth"] == 0]
            params = top[:nparams]
            for l in p["locals"]:
                l["ctype"] = namer.decl(l["type"])
                l["size"] = namer.size(l["type"])
            for s in p["statics"]:
                s["ctype"] = namer.decl(s["type"], s["name"])
                s["size"] = namer.size(s["type"])
            functions.append({
                "name": p["name"], "rva": p["rva"], "length": p["length"], "static": p["static"],
                "module": mod.index, "obj": mod.name,
                "file": source_path(span[0][1]) if span else None,
                "file_raw": span[0][1] if span else None,
                "line_first": min((l for _, _, l in span), default=None),
                "line_last": max((l for _, _, l in span), default=None),
                "type": p["type"],
                "ret_size": namer.size(t["ret"]) if t and t["kind"] == "procedure" else None,
                "ret_is_aggregate": bool(t and t["kind"] == "procedure" and t["ret"] >= 0x1000
                                         and tpi[namer.resolve(t["ret"])]["kind"] in ("struct", "class", "union")),
                "prototype": namer.prototype(p["type"], p["name"], [x["name"] for x in params])
                if t and t["kind"] == "procedure" else None,
                "params": params, "locals": p["locals"][len(params):] if params == top[:nparams]
                else p["locals"], "statics": p["statics"], "labels": p["labels"],
                "frame": {"dbg_start": p["dbg_start"], "dbg_end": p["dbg_end"],
                          "flags": p["flags"]},
            })
        for d in mdata:
            data.append({**d, "module": mod.index, "ctype": namer.decl(d["type"], d["name"]),
                         "size": namer.size(d["type"])})

    seen = {(d["name"], d["rva"]) for d in data}
    for g in gdata:
        if (g["name"], g["rva"]) not in seen:
            data.append({**g, "module": None, "ctype": namer.decl(g["type"], g["name"]),
                         "size": namer.size(g["type"])})

    functions.sort(key=lambda f: (f["rva"] is None, f["rva"] or 0))
    out = {
        "pdb": {"path": cfg[key], "guid": dbi.guid, "age": dbi.age_dbi, "signature": dbi.signature},
        "sections": [{"name": n, "rva": r, "size": s} for n, r, s in dbi.sections],
        "modules": modules,
        "functions": functions,
        "data": sorted(data, key=lambda d: (d["rva"] is None, d["rva"] or 0)),
        "publics": publics,
        "typedefs": udts,
    }
    path = REPO / "symbols" / f"{out_name}.json"
    path.write_text(json.dumps(out, indent=1))

    game = [f for f in functions if f["file"]]
    nlocals = sum(len(f["params"]) + len(f["locals"]) for f in functions)
    print(f"{path.name}: {len(modules)} modules, {len(functions)} functions "
          f"({kinds['global']} global / {kinds['static']} static), {len(game)} in game source, "
          f"{nlocals} params+locals, {len(data)} data, {len(publics)} publics, {len(udts)} typedefs, "
          f"{len({f['file'] for f in game})} game source files")


if __name__ == "__main__":
    main()
