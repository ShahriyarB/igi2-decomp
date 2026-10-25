"""Final client PDB types -> include/igi2_types.h.

Emits every aggregate, enum and typedef reachable from the game's own modules, in dependency
order, skipping what decomp_system.h already defines (those get size asserts instead). Each
struct is checked against MSVC's natural layout; one that disagrees is emitted packed with
explicit padding. Every emitted struct gets sizeof/offsetof static asserts.

usage: uv run gen_types.py [pdb key=final_pdb] [symbols=final]
"""
import collections
import json
import re
import sys

from config import REPO, load_config
from pdb.cdecl import TypeNamer
from pdb.msf import Msf
from pdb.symbols import global_symbols
from pdb.dbi import Dbi
from pdb.tpi import Tpi
from sysnames import system_names, system_sizes

AGG = ("struct", "class", "union")
_TAGREF = re.compile(r"\b(?:struct|union|enum) (\w+)")
# Layouts that changed between the VC 7.0 CRT/SDK and today's; the game only uses them by pointer.
KNOWN_SYSTEM_DIFFERENCES = {"_iobuf"}
MAX_PACK = 8  # MSVC x86 default /Zp8


class Gen:
    def __init__(self, tpi, typedefs, symbols, sysn):
        self.tpi = tpi
        self.sys = sysn
        self.sys_sizes = system_sizes({
            (t.get("unique") or t["name"]): ("union" if t["kind"] == "union" else "struct")
            for t in tpi.types.values()
            if t["kind"] in AGG and not t["fwdref"] and (t.get("unique") or t["name"]) in sysn["tags"]})
        self.namer = TypeNamer(tpi)
        self.typedefs = typedefs
        self.symbols = symbols
        self._choose_canonical()
        self._align_memo = {}
        self.packed = set()

    # ---- which definition wins when one tag name has several layouts --------------------
    def _choose_canonical(self):
        tpi = self.tpi
        by_name = collections.defaultdict(list)
        for ti, t in tpi.types.items():
            if t["kind"] in AGG + ("enum",) and not t["fwdref"]:
                name = t.get("unique") or t["name"]
                if name.startswith(("<unnamed", "__unnamed")):
                    continue  # anonymous types are distinct per index, never one name
                by_name[(t["kind"] == "enum", name)].append(ti)
        refs = collections.Counter()
        for f in self.symbols["functions"]:
            for x in [f["type"]] + [l["type"] for l in f["params"] + f["locals"]]:
                refs[self._strip(x)] += 1
        for d in self.symbols["data"]:
            refs[self._strip(d["type"])] += 1
        for ti, t in tpi.types.items():
            if t["kind"] == "fieldlist":
                for m in t["members"]:
                    if m["kind"] == "member":
                        refs[self._strip(m["type"])] += 1
        self.canonical = {}   # name key -> ti
        self.renamed = {}     # ti -> unique tag for a non-canonical layout
        for key, tis in by_name.items():
            # forward refs resolve by name; count them toward whichever layout is canonical
            best = max(tis, key=lambda ti: (refs[ti], ti))
            sys_size = self.sys_sizes.get(key[1])
            if sys_size is not None:  # the system's own layout wins its name
                best = next((ti for ti in tis if tpi[ti].get("size") == sys_size), best)
            self.canonical[key] = best
            for ti in tis:
                if ti != best and not self._same_layout(ti, best):
                    self.renamed[ti] = f"{tpi[ti]['name']}__{ti:x}"
        # make the namer resolve forward references to the canonical layout
        self.namer._defs = {k[1]: v for k, v in self.canonical.items()}
        base_tag = self.namer.tag

        def tag(ti):
            r = self.namer.resolve(ti)
            return self.renamed.get(r) or base_tag(ti)
        self.namer.tag = tag

    def _strip(self, ti):
        """Pointer/array/modifier chains down to the aggregate (or basic) they lead to."""
        seen = 0
        while ti >= 0x1000 and seen < 32:
            t = self.tpi[ti]
            if t["kind"] in ("pointer", "modifier", "array"):
                ti = t["type"]
            else:
                break
            seen += 1
        return ti

    def _members(self, ti):
        t = self.tpi[ti]
        return self.tpi[t["fields"]]["members"] if t["fields"] else []

    def _same_layout(self, a, b):
        ma = [(m["kind"], m.get("offset", m.get("value")), m.get("name"), self.namer.size(m["type"]) if "type" in m else 0)
              for m in self._members(a)]
        mb = [(m["kind"], m.get("offset", m.get("value")), m.get("name"), self.namer.size(m["type"]) if "type" in m else 0)
              for m in self._members(b)]
        return self.tpi[a].get("size") == self.tpi[b].get("size") and ma == mb

    # ---- reachability ------------------------------------------------------------------
    def reachable(self, roots):
        """Aggregates/enums reachable from `roots`, plus whether each is needed by value."""
        seen, out = set(), set()
        stack = list(roots)
        while stack:
            ti = stack.pop()
            if ti < 0x1000 or ti in seen:
                continue
            seen.add(ti)
            t = self.tpi.get(ti)
            if t is None:
                continue
            k = t["kind"]
            if k in AGG + ("enum",):
                r = self.namer.resolve(ti)
                if r != ti:
                    stack.append(r)
                    continue
                out.add(ti)
                if k != "enum":
                    for m in self._members(ti):
                        if "type" in m and m["kind"] in ("member", "stmember"):
                            stack.append(m["type"])
            elif k in ("pointer", "modifier", "array", "bitfield"):
                stack.append(t["type"])
            elif k in ("procedure", "mfunction"):
                stack.append(t["ret"])
                stack.extend(self.tpi[t["args"]]["args"])
        return out

    # ---- layout ------------------------------------------------------------------------
    def align(self, ti):
        if ti < 0x1000:
            return min(self.namer.size(ti) or 1, MAX_PACK)
        if ti in self._align_memo:
            return self._align_memo[ti]
        ti = self.namer.resolve(ti)
        t = self.tpi[ti]
        k = t["kind"]
        if k in ("pointer",):
            a = 4
        elif k in ("modifier", "array", "bitfield"):
            a = self.align(t["type"])
        elif k == "enum":
            a = self.align(t["utype"])
        elif k in AGG:
            if ti in self.packed:
                a = 1
            else:
                a = max((self.align(m["type"]) for m in self._members(ti) if m["kind"] == "member"),
                        default=1)
        else:
            a = 1
        self._align_memo[ti] = min(a, MAX_PACK)
        return self._align_memo[ti]

    def build_nodes(self, ti):
        """Member list with flattened anonymous unions rebuilt as union nodes.

        node = ("m", member) | ("u", [alt, ...]) where alt is a list of nodes (an anonymous struct
        when it holds more than one node)."""
        members = [m for m in self._members(ti) if m["kind"] == "member"]
        out, i = [], 0
        while i < len(members):
            m = members[i]
            end = max((self._end(n) for n in out), default=0)
            if out and m["offset"] < end and not self._is_bitfield(m):
                k = next((j for j, n in enumerate(out) if self._start(n) == m["offset"]), None)
                if k is None:
                    return None  # overlap inside a member: cannot express, caller emits bytes
                alts, cur = [out[k:]], [("m", m)]
                del out[k:]
                i += 1
                while i < len(members):
                    n = members[i]
                    uend = max(self._alt_end(a) for a in alts + [cur])
                    if n["offset"] == m["offset"]:
                        alts.append(cur)
                        cur = [("m", n)]
                    elif m["offset"] < n["offset"] < uend:
                        cur.append(("m", n))
                    else:
                        break
                    i += 1
                alts.append(cur)
                out.append(("u", alts))
            else:
                out.append(("m", m))
                i += 1
        return out

    def opaque(self, ti):
        """C++ library types: never emitted, so anything holding one by value is raw bytes."""
        name = self.tpi[ti].get("name", "")
        return "::" in name or ("<" in name and not name.startswith("<unnamed"))

    def _is_bitfield(self, m):
        return m["type"] >= 0x1000 and self.tpi[m["type"]]["kind"] == "bitfield"

    def _start(self, n):
        return n[1]["offset"] if n[0] == "m" else self._start(n[1][0][0])

    def _end(self, n):
        if n[0] == "m":
            return n[1]["offset"] + self.namer.size(n[1]["type"])
        return max(self._alt_end(a) for a in n[1])

    def _alt_end(self, alt):
        return max(self._end(n) for n in alt)

    def natural_ok(self, ti, nodes):
        """Would MSVC place every member at its PDB offset without #pragma pack?"""
        t = self.tpi[ti]
        if t["kind"] == "union":
            size = max((self._end(n) for n in nodes), default=0)
            a = self.align(ti)
            return all(self._start(n) == 0 for n in nodes) and (-(-size // a) * a) == t["size"]
        off, a_max, prev_bit = 0, 1, None
        for n in nodes:
            if n[0] == "m" and self._is_bitfield(n[1]):
                if prev_bit == n[1]["offset"]:
                    continue
                prev_bit = n[1]["offset"]
            else:
                prev_bit = None
            a = self._node_align(n)
            a_max = max(a_max, a)
            off = -(-off // a) * a
            if off != self._start(n):
                return False
            off = self._end(n)
        size = -(-off // a_max) * a_max if off else 0
        return size == t["size"] or (not nodes and t["size"] <= 1)

    def _node_align(self, n):
        if n[0] == "m":
            return self.align(n[1]["type"])
        return max(self._node_align(x) for alt in n[1] for x in alt)

    # ---- emission ----------------------------------------------------------------------
    def decl(self, ti, name):
        d = self.namer.decl(ti, name)
        return d.replace("[]", "[0]")

    def emit_nodes(self, nodes, indent, packed, base, lines, pad_counter):
        pos = base
        prev_bit = None
        for n in nodes:
            start = self._start(n)
            if packed and start > pos:
                lines.append(f"{indent}unsigned char __pad{pad_counter[0]:x}[{start - pos}];")
                pad_counter[0] += 1
            if n[0] == "m":
                m = n[1]
                lines.append(f"{indent}{self.decl(m['type'], self._member_name(m))};")
                if self._is_bitfield(m):
                    if prev_bit != m["offset"]:
                        prev_bit = m["offset"]
                        pos = start + self.namer.size(m["type"])
                    continue
                prev_bit = None
                pos = max(pos, self._end(n))
            else:
                lines.append(f"{indent}union {{")
                for alt in n[1]:
                    if len(alt) == 1 and alt[0][0] == "m":
                        m = alt[0][1]
                        lines.append(f"{indent}    {self.decl(m['type'], self._member_name(m))};")
                    else:
                        lines.append(f"{indent}    struct {{")
                        self.emit_nodes(alt, indent + "        ", packed, start, lines, pad_counter)
                        lines.append(f"{indent}    }};")
                lines.append(f"{indent}}};")
                prev_bit = None
                pos = max(pos, self._end(n))
        return pos

    @staticmethod
    def _member_name(m):
        return m["name"] if m["name"] and not m["name"].startswith("<") else "__unnamed"

    def emit_aggregate(self, ti, lines, asserts):
        t = self.tpi[ti]
        kw = "union" if t["kind"] == "union" else "struct"
        tag = self.namer.tag(ti)
        nodes = self.build_nodes(ti)
        if nodes is None or any(self.opaque(d) for d in value_deps(self, ti)):
            lines.append(f"/* overlapping members could not be expressed; raw bytes */")
            lines.append(f"{kw} {tag} {{ unsigned char __raw[{t['size']}]; }};")
            asserts.append(f"_Static_assert(sizeof({kw} {tag}) == {t['size']}, \"{tag}\");")
            return
        packed = not self.natural_ok(ti, nodes)
        if packed:
            self.packed.add(ti)
            self._align_memo.clear()
            lines.append("#pragma pack(push, 1)")
        lines.append(f"{kw} {tag} {{")
        pc = [0]
        end = self.emit_nodes(nodes, "    ", packed, 0, lines, pc)
        if packed and t["size"] > end:
            lines.append(f"    unsigned char __pad{pc[0]:x}[{t['size'] - end}];")
        if not nodes and not packed:
            lines.append(f"    unsigned char __empty[{max(t['size'], 1)}];")
        lines.append("};")
        if packed:
            lines.append("#pragma pack(pop)")
        asserts.append(f"_Static_assert(sizeof({kw} {tag}) == {t['size']}, \"sizeof {tag}\");")
        for n in nodes:
            if n[0] == "m" and not self._is_bitfield(n[1]) and n[1]["name"] and not n[1]["name"].startswith("<"):
                asserts.append(f"_Static_assert(offsetof({kw} {tag}, {n[1]['name']}) == "
                               f"{n[1]['offset']}, \"{tag}.{n[1]['name']}\");")

    def emit_enum(self, ti, lines, enumerators):
        t = self.tpi[ti]
        tag = self.namer.tag(ti)
        body = []
        for m in self._members(ti):
            if m["kind"] != "enumerate":
                continue
            name, val = m["name"], m["value"]
            if name in self.sys["macros"] or name in enumerators:
                body.append(f"    /* {name} = {val} (already defined) */")
                continue
            enumerators[name] = tag
            body.append(f"    {name} = {val},")
        lines.append(f"enum {tag} {{")
        lines.extend(body or ["    __empty_" + tag])
        lines.append("};")


def value_deps(gen, ti):
    """Aggregates a definition needs complete (by-value members and arrays)."""
    deps = set()

    def walk(x):
        while x >= 0x1000:
            t = gen.tpi[x]
            if t["kind"] in ("modifier", "array", "bitfield"):
                x = t["type"]
            elif t["kind"] in AGG + ("enum",):
                deps.add(gen.namer.resolve(x))
                return
            else:
                return
    for m in gen._members(ti):
        if m["kind"] == "member":
            walk(m["type"])
    return deps


def main():
    key = sys.argv[1] if len(sys.argv) > 1 else "final_pdb"
    sym_name = sys.argv[2] if len(sys.argv) > 2 else "final"
    msf = Msf(load_config()[key])
    tpi = Tpi(msf.stream(2))
    _pub, _gd, udts = global_symbols(msf, Dbi(msf))
    symbols = json.loads((REPO / "symbols" / f"{sym_name}.json").read_text())
    sysn = system_names()
    (REPO / "build").mkdir(exist_ok=True)
    (REPO / "build" / "system_idents.json").write_text(json.dumps(sorted(sysn["idents"])))
    (REPO / "build" / "system_protos.json").write_text(json.dumps(sysn["prototypes"], indent=0))
    gen = Gen(tpi, udts, symbols, sysn)

    game_mods = {m["index"] for m in symbols["modules"] if m["game_files"] and m["lib"].lower() != "libc.lib"
                 and not m["obj"].lower().endswith(("libcp.lib",))}
    roots = set()
    for f in symbols["functions"]:
        if f["module"] in game_mods:
            roots.add(f["type"])
            roots.update(l["type"] for l in f["params"] + f["locals"])
            roots.update(s["type"] for s in f["statics"])
    for d in symbols["data"]:
        if d["module"] in game_mods or (d["module"] is None and not d["name"].startswith(("_", "?"))):
            roots.add(d["type"])
    reach = gen.reachable(roots)

    def is_system(ti):
        return gen.namer.tag(ti) in sysn["tags"]

    def cxx_only(name):
        return "::" in name or ("<" in name and not name.startswith("<unnamed"))

    aggs = sorted(ti for ti in reach if tpi[ti]["kind"] in AGG and not is_system(ti)
                  and not cxx_only(tpi[ti]["name"]))
    enums = sorted(ti for ti in reach if tpi[ti]["kind"] == "enum" and not is_system(ti)
                   and "::" not in tpi[ti]["name"])
    system_aggs = sorted(ti for ti in reach if tpi[ti]["kind"] in AGG and is_system(ti))

    lines = ["/* Generated by tools/gen_types.py from the Final client PDB -- do not edit. */", "#pragma once",
             '#include "decomp_system.h"', "", "#pragma warning(push)",
             "#pragma warning(disable: 4200 4201 4214)", ""]
    lines.append("/* ---- forward declarations ---- */")
    for ti in aggs:
        kw = "union" if tpi[ti]["kind"] == "union" else "struct"
        lines.append(f"{kw} {gen.namer.tag(ti)};")
    lines.append("")
    lines.append("/* ---- enums ---- */")
    enumerators = {}
    for ti in enums:
        gen.emit_enum(ti, lines, enumerators)
    lines.append("")

    # typedefs whose target needs nothing complete go first; the rest follow their target
    typedef_lines_early, typedef_after = [], collections.defaultdict(list)
    emitted_tags = {gen.namer.tag(ti) for ti in aggs + enums}
    for name, ti in sorted(udts.items()):
        if name in sysn["typedefs"] or name in sysn["tags"] or name in sysn["macros"]:
            continue
        if ti >= 0x1000 and tpi[ti]["kind"] in AGG + ("enum",) and gen.namer.tag(ti) == name:
            continue  # typedef struct X X: the C code already spells "struct X" in our output
        try:
            text = f"typedef {gen.decl(ti, name)};"
        except (KeyError, ValueError):
            continue
        if name.startswith("_") or "::" in text or "<" in text.replace("<unnamed", ""):
            continue  # reserved names belong to the CRT / C++ library, not the game
        if any(tag not in emitted_tags and tag not in sysn["tags"] for tag in _TAGREF.findall(text)):
            continue  # refers to a type the game never uses
        dep = gen._strip(ti)
        if ti >= 0x1000 and tpi[ti]["kind"] == "array" and dep >= 0x1000 and \
                tpi[gen.namer.resolve(dep)]["kind"] in AGG:
            typedef_after[gen.namer.resolve(dep)].append(text)
        else:
            typedef_lines_early.append(text)
    lines.append("/* ---- typedefs ---- */")
    lines.extend(typedef_lines_early)
    lines.append("")

    lines.append("/* ---- aggregates ---- */")
    agg_set = set(aggs)
    done, visiting, asserts = set(), set(), []

    def visit(ti):
        if ti in done or ti not in agg_set:
            return
        if ti in visiting:
            raise RuntimeError(f"by-value cycle at {gen.namer.tag(ti)}")
        visiting.add(ti)
        for d in sorted(value_deps(gen, ti)):
            visit(d)
        visiting.discard(ti)
        done.add(ti)
        gen.emit_aggregate(ti, lines, asserts)
        lines.extend(typedef_after.get(ti, []))
        lines.append("")
    for ti in aggs:
        visit(ti)

    lines.append("/* ---- layout checks ---- */")
    lines.extend(asserts)
    for ti in system_aggs:
        t = tpi[ti]
        if t["size"]:
            kw = "union" if t["kind"] == "union" else "struct"
            if gen.namer.tag(ti) in KNOWN_SYSTEM_DIFFERENCES:
                continue
            lines.append(f"_Static_assert(sizeof({kw} {gen.namer.tag(ti)}) == {t['size']}, "
                         f"\"system {gen.namer.tag(ti)}\");")
    lines.append("")
    lines.append("#pragma warning(pop)")
    out = REPO / "include" / "igi2_types.h"
    out.write_text("\n".join(lines) + "\n")
    # every member and enumerator name: globals become macros, which must not share these
    scoped = set(enumerators)
    for ti in aggs:
        scoped |= {m["name"] for m in gen._members(ti) if m.get("name")}
    (REPO / "build").mkdir(exist_ok=True)
    (REPO / "build" / "scoped_names.json").write_text(json.dumps(sorted(scoped)))
    print(f"{out.name}: {len(aggs)} aggregates ({len(gen.packed)} packed, {len(gen.renamed)} "
          f"renamed duplicate layouts), {len(enums)} enums, {len(typedef_lines_early) + sum(map(len, typedef_after.values()))} "
          f"typedefs, {len(system_aggs)} system types asserted")


if __name__ == "__main__":
    main()
