"""Apply pc.pdb knowledge to the retail IDB (work/retail/igi2_1.0.exe.i64), headless.

1. types: include/generated/igi2_types.h (system includes and asserts stripped) on top of mssdk_win10.til
2. functions: names, prototypes and a "source: file:line" comment from symbols/match.json
3. globals: names and types from symbols/data_match.json

usage: python tools/pipeline/ida_apply.py      (system Python with idapro, like ida_fingerprints.py)
"""
import json
import re
import sys
import time
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parents[2]
IDB = REPO / "work" / "retail" / "igi2_1.0.exe.i64"

t0 = time.time()
if idapro.open_database(str(IDB), run_auto_analysis=False):
    raise SystemExit(f"could not open {IDB}")

import ida_auto  # noqa: E402
import ida_bytes  # noqa: E402
import ida_funcs  # noqa: E402
import ida_name  # noqa: E402
import ida_segment  # noqa: E402
import ida_typeinf  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

# Placement by size sequence alone is weaker evidence than a code match: say so on the function.
WEAK = {"client-obj": "name placed by object/size alignment (medium confidence)",
        "leftover": "name placed next to its object (medium confidence)"}


def ida_header():
    text = (REPO / "include" / "generated" / "igi2_types.h").read_text()
    out = []
    for line in text.splitlines():
        s = line.strip()
        if s.startswith(("#include", "_Static_assert", "#pragma once", "#pragma warning")):
            continue
        out.append(line)
    text = "\n".join(out)
    # IDA parses bool/true/false as keywords; the game's own "enum bool" gets an IDA-only name
    # that export.py maps back (IDA_RENAMES).
    for ours, theirs in IDA_RENAMES.items():
        text = re.sub(rf"\b{re.escape(ours)}\b", theirs, text)
    return text


IDA_RENAMES = {"enum bool": "enum igi_bool", "false": "igi_false", "true": "igi_true"}


def ida_text(decl):
    for ours, theirs in IDA_RENAMES.items():
        decl = re.sub(rf"\b{re.escape(ours)}\b", theirs, decl)
    return decl


def declarations(text):
    """Top-level declarations, each with any #pragma pack lines that wrap it."""
    chunk, depth = [], 0
    for line in text.splitlines():
        if not line.strip() or line.lstrip().startswith("/*"):
            continue
        chunk.append(line)
        depth += line.count("{") - line.count("}")
        if depth == 0 and (line.rstrip().endswith(";") or line.startswith("#pragma pack(pop")):
            if not line.startswith("#pragma pack(push"):
                yield "\n".join(chunk)
                chunk = []
    if chunk:
        yield "\n".join(chunk)


def apply_types():
    ida_typeinf.add_til("mssdk_win10", ida_typeinf.ADDTIL_DEFAULT)
    failed = []
    for decl in declarations(ida_header()):
        if idc.parse_decls(decl, idc.PT_SILENT):
            failed.append(decl)
    (REPO / "build" / "ida_type_failures.txt").write_text("\n\n".join(failed))
    print(f"types: {len(failed)} declarations failed (build/ida_type_failures.txt), "
          f"local types {ida_typeinf.get_ordinal_count(None)}", flush=True)


def unique_name(name, ea, obj):
    cur = ida_name.get_name_ea(idc.BADADDR, name)
    if cur in (idc.BADADDR, ea):
        return name
    stem = obj.rsplit(".", 1)[0]
    return f"{name}__{stem}" if ida_name.get_name_ea(idc.BADADDR, f"{name}__{stem}") == idc.BADADDR \
        else f"{name}__{ea:x}"


def apply_functions():
    pc = json.loads((REPO / "symbols" / "final.json").read_text())
    m = json.loads((REPO / "symbols" / "match.json").read_text())
    by_rva = {str(f["rva"]): f for f in pc["functions"] if f["rva"] is not None}
    named = typed = bad_type = 0
    for rva, v in m.items():
        ea = v["ea"]
        if ea is None:
            continue
        f = by_rva[rva]
        if not ida_funcs.get_func(ea):
            ida_funcs.add_func(ea)
        fn = ida_funcs.get_func(ea)
        if fn and fn.start_ea == ea and v["lib"] == "j.lib" and fn.flags & ida_funcs.FUNC_LIB:
            fn.flags &= ~ida_funcs.FUNC_LIB  # a signature hit on game code (Texture_Open, tiny setters)
            ida_funcs.update_func(fn)
        name = unique_name(v["name"], ea, v["obj"])
        if ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            named += 1
        # library code has no type records in the PDB ("void __cdecl floor(void)"): its
        # prototypes come from the SDK headers (libtypes)
        if f["prototype"] and v["lib"] == "j.lib":
            proto = re.sub(r"\b" + re.escape(f["name"]) + r"\(", name + "(", f["prototype"], count=1)
            if idc.SetType(ea, ida_text(proto) + ";"):
                typed += 1
            else:
                bad_type += 1
        where = f"{f['file']}:{f['line_first']}" if f["file"] else v["obj"]
        note = f"source: {where}  [{v['how']}]"
        if v["how"] in WEAK:
            note += f"\n{WEAK[v['how']]}"
        idc.set_func_cmt(ea, note, 1)
    print(f"functions: named {named}, prototypes applied {typed}, rejected {bad_type}", flush=True)


def named_decl(ctype, name):
    """'char [3]' + zTokens -> 'char zTokens[3]'; 'void (__cdecl *)(int)' -> 'void (__cdecl *pf)(int)'."""
    if "(*" in ctype:
        return ctype.replace("(*", f"(*{name}", 1)
    if "[" in ctype:
        i = ctype.index("[")
        return f"{ctype[:i].rstrip()} {name}{ctype[i:]}"
    return f"{ctype} {name}"


def apply_locals():
    """The Final PDB's stack locals, with their types and names, onto the retail stack frames.
    The decompiler builds its variables from the frame: without the types it splits a struct
    whose address is passed out (DIDEVCAPS filled by GetCapabilities) into the few fields the
    code reads, and the rebuilt function then writes past them. The PDB's frame offsets are the
    frame-pointer offsets IDA uses; only functions of identical size in both builds are trusted
    to have the same frame."""
    import ida_frame
    cl = json.loads((REPO / "symbols" / "final.json").read_text())
    m = json.loads((REPO / "symbols" / "match.json").read_text())
    by_rva = {str(f["rva"]): f for f in cl["functions"] if f["rva"] is not None}
    applied = rejected = funcs = 0
    for rva, v in m.items():
        if v["ea"] is None or v["lib"] != "j.lib" or v["length"] != v["retail_size"]:
            continue
        pfn = ida_funcs.get_func(v["ea"])
        stack = [l for l in by_rva[rva]["locals"] if l.get("bp") is not None and l["bp"] < 0 and l["size"]]
        if not pfn or pfn.start_ea != v["ea"] or not pfn.frsize or not stack:
            continue
        if idc.print_insn_mnem(v["ea"]) == "push" and idc.print_operand(v["ea"], 0) == "ebp" \
                and idc.GetDisasm(idc.next_head(v["ea"], idc.BADADDR)).replace(" ", "") == "movebp,esp":
            base = -ida_frame.soff_to_fpoff(pfn, 0)  # frame-struct offset of ebp
        else:
            # no frame pointer: the PDB counts from the return address. (IDA's own frame
            # pointer is no guide here: it takes SoundSys_LoadSoundResource's "lea ebp,
            # [esp+2Dh]", a pointer difference, for one)
            base = ida_frame.frame_off_retaddr(pfn)
        claimed = []
        funcs += 1
        for loc in sorted(stack, key=lambda l: (l["depth"], l["bp"])):
            lo, hi = loc["bp"], loc["bp"] + loc["size"]
            if lo + base < 0 or hi > 0 or any(lo < b and a < hi for a, b in claimed):
                continue  # outside the locals area, or a later block's reuse of the same bytes
            tif = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tif, None, ida_text(named_decl(loc["ctype"], loc["name"])) + ";",
                                      ida_typeinf.PT_SIL) is None or tif.get_size() != loc["size"]:
                rejected += 1
                continue
            ida_frame.delete_frame_members(pfn, lo + base, hi + base)
            if ida_frame.define_stkvar(pfn, loc["name"], lo, tif):
                claimed.append((lo, hi))
                applied += 1
            else:
                rejected += 1
    print(f"locals: {applied} stack locals typed and named in {funcs} functions, {rejected} rejected", flush=True)


def apply_globals():
    d = json.loads((REPO / "symbols" / "data_match.json").read_text())
    named = typed = 0
    for ea_s, v in d.items():
        ea = int(ea_s)
        name = unique_name(v["name"], ea, v["obj"] or "global")
        if ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            named += 1
        decl = v["ctype"]
        if v["size"]:
            import ida_bytes
            ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, v["size"])  # one-dword items would block the type
        if decl and idc.SetType(ea, ida_text(decl) + ";"):
            typed += 1
    print(f"globals: named {named}, typed {typed} of {len(d)}", flush=True)


def pdb_registers(f, ea, abi):
    """{param index: register} for the parameters passed in registers, from the PDB.

    The Final PDB gives every parameter's location: a frame offset, or a register. A register
    record also covers a stack parameter the function keeps in a register (736 "in ebp", read
    from the stack first), so a register counts as the passing location only when the function
    reads it before writing it, or the decompiler saw it as an input."""
    full = {"al": "eax", "ax": "eax", "cl": "ecx", "cx": "ecx", "dl": "edx", "dx": "edx",
            "bl": "ebx", "bx": "ebx", "si": "esi", "di": "edi", "bp": "ebp"}
    params = f["params"]
    located = {i: p["reg"] for i, p in enumerate(params) if p.get("reg")}
    measured = {full.get(a[1], a[1]) for a in abi["args"] if a[0] == "reg"}
    if not located and not measured:
        return {}
    reads = set(entry_register_reads(ea))
    in_reg = {i: r for i, r in located.items() if full.get(r, r) in reads | measured}
    # The PDB is the Final build's, 25 days older than retail: link-time code generation can
    # have moved one more parameter into a register since (Network_Send takes nLen in eax).
    # When the code reads a register the PDB does not explain and the argument count still
    # agrees, the parameter that left the stack is the one whose removal lines the remaining
    # stack parameters up with what the decompiler saw in each slot (pointer/integer/float).
    unexplained = [r for r in measured if r in reads and r not in {full.get(x, x) for x in in_reg.values()}]
    stack_seen = [a for a in abi["args"] if a[0] == "stack"]
    on_stack = [i for i in range(len(params)) if i not in in_reg]
    import idautils
    # a function whose address is taken (a handler) is called through pointers with the stack
    # convention: link-time code generation cannot have moved its parameters
    address_taken = any(x.type not in (16, 17, 18, 19, 21) for x in idautils.XrefsTo(ea, 0))
    # ">=": retail may no longer read a trailing parameter at all (TerrainRender_DrawFace: LTCG
    # folded isCull away and moved iVertex1 to di; the decompiler counts only what is read)
    if unexplained and not address_taken and len(on_stack) - len(unexplained) >= len(stack_seen) \
            and len(unexplained) <= 2:
        import itertools

        def kind(p):
            t = p["ctype"]
            return "ptr" if "*" in t or "[" in t else ("float" if t in ("float", "double") else "int")

        best = None
        for moved in itertools.permutations(on_stack, len(unexplained)):
            rest = [i for i in on_stack if i not in moved]
            score = sum(kind(params[i]) == s[3] for i, s in zip(rest, stack_seen) if len(s) > 3 and s[3])
            if best is None or score > best[0]:
                best = (score, moved)
        for i, r in zip(best[1], unexplained):
            in_reg[i] = r
    return in_reg


def merge_abi(f, abi, in_reg):
    """PDB prototype + where its parameters arrive -> (IDA declaration, status).

    Link-time code generation moved some arguments into registers (Symbol_Register takes zName in
    ebx). in_reg (pdb_registers) puts those parameters in their registers and the rest on the
    stack in order; names and types stay the PDB's. The return location is what the decompiler
    measured (abi)."""
    params = f["params"]
    if not in_reg:
        return None, "pdb"  # every parameter on the stack, as the prototype says
    head = f["prototype"].partition("(")[0]
    ret, name = head.rsplit(" ", 1)
    for conv in ("__cdecl", "__stdcall", "__fastcall", "__thiscall"):
        ret = ret.replace(conv, "")
    ret = ret.strip()
    retloc = ""
    if abi["retloc"] and abi["retloc"][0] == "reg" and ret != "void":
        reg = abi["retloc"][1]
        # the decompiler names the x87 top "st7" internally; the convention syntax calls it st0
        retloc = "@<st0>" if reg.startswith("st") else f"@<{reg}>"
    elif ret == "void" and abi["retloc"] and abi["retloc"][0] == "reg" and abi["retloc"][1] in in_reg.values():
        # declared void, but the argument register comes back unchanged and link-time code
        # generation let callers go on using it (Real32x9_Create(ptDest@eax): the caller steps
        # eax to the next matrix): it is the return value
        i = next(k for k, r in in_reg.items() if r == abi["retloc"][1])
        if params[i]["size"] == 4 and "(" not in params[i]["ctype"]:
            ret, retloc = params[i]["ctype"], f"@<{abi['retloc'][1]}>"
    decls = []
    for i, p in enumerate(params):
        d = p["ctype"]
        fnptr = re.search(r"\(((?:__\w+\s*)?)\*\)", d)
        if fnptr:  # function pointer: the name goes inside the declarator
            d = d[:fnptr.start()] + f"({fnptr.group(1)}*{p['name']})" + d[fnptr.end():]
        elif d.endswith("]"):
            d = d.replace("[", f" {p['name']}[", 1)
        else:
            d = f"{d} {p['name']}"
        if i in in_reg:
            d += f"@<{in_reg[i]}>"
        decls.append(d)
    conv = "__userpurge" if abi["cc"] == "userpurge" else "__usercall"
    return f"{ret} {conv} {name}{retloc}({', '.join(decls)})", "usercall"


def measured_decl(name, abi):
    """A declaration from the argument locations alone (no PDB names): int-sized values, with
    pointers and floats where the decompiler saw them used so."""
    def ctype(size, kind):
        if kind == "float":
            return "float" if size == 4 else "double"
        if kind == "ptr" and size == 4:
            return "void *"
        return {1: "char", 2: "__int16", 8: "__int64"}.get(size, "int")

    args = []
    for k, (where_kind, where, size, kind, *_) in enumerate(abi["args"], 1):
        loc = f"@<{where}>" if where_kind == "reg" else ""
        args.append(f"{ctype(size, kind)} a{k}{loc}")
    ret = abi["ret"] if abi["ret"] and abi["ret"] != "void" else "void"
    retloc = ""
    if ret != "void" and abi["retloc"] and abi["retloc"][0] == "reg":
        retloc = "@<st0>" if abi["retloc"][1].startswith("st") else f"@<{abi['retloc'][1]}>"
    return f"{ret} __usercall {name}{retloc}({', '.join(args) or 'void'})"


_CALLEE_REGISTERS = None


def callee_registers():
    """{retail ea: registers the Final PDB records parameters in} for matched functions."""
    global _CALLEE_REGISTERS
    if _CALLEE_REGISTERS is None:
        cl = json.loads((REPO / "symbols" / "final.json").read_text())
        m = json.loads((REPO / "symbols" / "match.json").read_text())
        by_rva = {str(f["rva"]): f for f in cl["functions"] if f["rva"] is not None}
        # ebp records are where a parameter was kept, not how it was passed
        full = {"eax": "eax", "ax": "eax", "al": "eax", "ecx": "ecx", "cx": "ecx", "cl": "ecx",
                "edx": "edx", "dx": "edx", "dl": "edx", "ebx": "ebx", "bx": "ebx", "bl": "ebx",
                "esi": "esi", "si": "esi", "edi": "edi", "di": "edi"}
        _CALLEE_REGISTERS = {}
        for rva, v in m.items():
            if v["ea"] is not None and rva in by_rva:
                regs = {full[p["reg"]] for p in by_rva[rva]["params"] if p.get("reg") in full}
                if regs:
                    _CALLEE_REGISTERS[v["ea"]] = regs
    return _CALLEE_REGISTERS


def entry_register_reads(ea, calls_read=True):
    """General registers the function reads before it writes them, in order of first use: its
    register arguments. A push of a callee-saved register that the function pops again is a
    save wherever it stands (MSVC saves some only right before their first use), not a read;
    one never popped passes the value on ("push edi" as an argument). A call may read eax, ecx
    and edx (link-time code generation passes arguments in them)."""
    import ida_ua
    import idautils
    names = ("eax", "ecx", "edx", "ebx", "esi", "edi", "ebp")
    sub = {"al": "eax", "ah": "eax", "ax": "eax", "cl": "ecx", "ch": "ecx", "cx": "ecx",
           "dl": "edx", "dh": "edx", "dx": "edx", "bl": "ebx", "bh": "ebx", "bx": "ebx",
           "si": "esi", "di": "edi", "bp": "ebp"}
    seen, reads = set(), []

    def regs_in(text):
        return [sub.get(t, t) for t in re.findall(r"\b([a-d][lhx]|e[a-d]x|[sd]il?|e[sd]i|e?bp|si|di)\b", text)
                if sub.get(t, t) in names]

    items = sorted(idautils.FuncItems(ea))
    popped = {idc.print_operand(i, 0) for i in items if idc.print_insn_mnem(i) == "pop"}
    for item in items:
        insn = ida_ua.insn_t()
        if not ida_ua.decode_insn(insn, item):
            continue
        mnem = insn.get_canon_mnem()
        ops = [idc.print_operand(item, n) for n in range(2)]
        if mnem == "lea" and ops[1].replace(" ", "") in (f"[{ops[0]}+0]", f"[{ops[0]}]"):
            continue  # "lea ebx, [ebx+0]": alignment filler, reads nothing
        if mnem == "push" and ops[0] in ("ebx", "esi", "edi", "ebp") and ops[0] in popped:
            continue  # saving a callee-saved register, often only right before its first use
        if mnem == "push" and not calls_read and idc.get_operand_type(item, 0) == idc.o_reg:
            continue  # strict: "push ecx" also reserves a stack slot, it is not a use of ecx
        used = []  # read operands, then written ones
        if mnem in ("mov", "lea", "movzx", "movsx", "pop", "setz", "setnz") or mnem.startswith("set"):
            used = [(r, "r") for r in regs_in(ops[1])] + \
                   [(r, "r") for r in regs_in(ops[0]) if "[" in ops[0]] + \
                   [(r, "w") for r in regs_in(ops[0]) if "[" not in ops[0]]
        elif mnem == "xor" and ops[0] == ops[1]:
            used = [(r, "w") for r in regs_in(ops[0])]
        elif mnem == "call":
            # the callee may take any of them as a register argument (Node_Remove(eax)), and
            # reads the ones its PDB records say it takes (Game_New hands its edi straight to
            # QTask_NewFn's ptParent@edi); this list only confirms the PDB's register records,
            # so a possible read counts
            used = [(r, "r") for r in regs_in(ops[0])]
            if calls_read:
                used += [("eax", "r"), ("ecx", "r"), ("edx", "r")] + \
                        [(r, "r") for r in sorted(callee_registers().get(idc.get_operand_value(item, 0), ()))]
        else:
            used = [(r, "r") for o in ops for r in regs_in(o)]
        for r, how in used:
            if r in seen:
                continue
            seen.add(r)
            if how == "r":
                reads.append(r)
    return reads


def decl_stack_bytes(decl):
    """Bytes of stack arguments a declaration has, by IDA's own reading of it (None: unparsable)."""
    tif = ida_typeinf.tinfo_t()
    if ida_typeinf.parse_decl(tif, None, ida_text(decl) + ";", ida_typeinf.PT_SIL) is None:
        return None
    fi = ida_typeinf.func_type_data_t()
    if not tif.get_func_details(fi):
        return None
    return max([a.argloc.stkoff() + ((a.type.get_size() + 3) & ~3) for a in fi if a.argloc.is_stkoff()] or [0])


def ltcg_extra_decl(f, ea, measured, decl):
    """A register argument the Final PDB does not have at all: link-time code generation gave
    the retail function one more (SkyDome_Draw is "(void)" in the PDB, and reads the sky dome
    from esi, which its caller loads with it). Taken when the decompiler measures that register
    as an argument and the function reads it itself before writing it; never for a function
    whose address is taken (calls through a pointer pass nothing in registers). It goes last,
    as an int: what it was is the caller's business. Stack arguments past the PDB's are taken
    for those too: every caller pushes them (GunPickup_New reads an eighth, a pointer)."""
    address_taken = any(True for _ in idautils.DataRefsTo(ea))
    measured_regs = set() if address_taken else {a[1] for a in measured.get("args", []) if a[0] == "reg"}
    base = decl or f["prototype"]
    if not base or "..." in base:
        return None
    full = {"al": "eax", "ax": "eax", "cl": "ecx", "cx": "ecx", "dl": "edx", "dx": "edx",
            "bl": "ebx", "bx": "ebx", "si": "esi", "di": "edi"}
    have = {full.get(r, r) for r in re.findall(r"@<(\w+)>", base.split("(", 1)[1] if "(" in base else "")}
    reads = entry_register_reads(ea, calls_read=False)
    extra = [r for r in reads if r in measured_regs and r not in have and r in ("eax", "ecx", "edx", "ebx", "esi", "edi")]
    # stack arguments past the PDB's last (MagicObjContainer_RunHandler takes ptQTask, and in
    # retail also the LOD in the next slot, which went into the shadow request as its index)
    extra_stack = 0
    measured_bytes = max([a[1] + ((a[2] + 3) & ~3) for a in measured.get("args", []) if a[0] == "stack"] or [0])
    declared_bytes = decl_stack_bytes(base)
    if declared_bytes is not None and not f["ret_is_aggregate"] and measured_bytes > declared_bytes:
        extra_stack = (measured_bytes - declared_bytes) // 4
    if not extra and not extra_stack:
        return None
    # "struct QTask_s *__cdecl GunPickup_New(": no space between a returned pointer's star and the
    # convention, which skipped every function returning a pointer
    m = re.match(r"^(?P<ret>.+?)\s*__(?:cdecl|usercall|stdcall)\s+(?P<name>\w+)(?P<retloc>@<\w+>)?\((?P<args>.*)\)$", base.strip())
    if not m or "__stdcall" in base:
        return None
    ret, args = m.group("ret").strip(), m.group("args").strip()
    retloc = m.group("retloc") or ""
    if not retloc and ret != "void":
        if re.search(r"\b(float|double)\b", ret):
            retloc = "@<st0>"
        elif re.search(r"__int64|long long", ret):
            return None
        else:
            retloc = "@<eax>"
    # a register the PDB names that the function never reads (not even by passing it on to a
    # callee) went to one of the registers it does read: the argument moved, it was not added
    # (TerrainRender_SetBlendMode: the PDB has eBlendMode in ecx, retail overwrites ecx first and
    # takes the mode in edx; kept in ecx, every caller's blend mode was lost)
    read_lenient = set(entry_register_reads(ea, calls_read=True))
    for stale in [r for r in re.findall(r"@<(\w+)>", args) if full.get(r, r) not in read_lenient]:
        if not extra:
            break
        args = args.replace(f"@<{stale}>", f"@<{extra.pop(0)}>", 1)
    new = [f"int ltcg_{r}@<{r}>" for r in extra] + [f"int ltcg_arg{declared_bytes // 4 + k}" for k in range(extra_stack)]
    args = ", ".join(([] if args in ("", "void") else [args]) + new)
    return f"{ret} __usercall {m.group('name')}{retloc}({args})"


def struct_return_decl(decl, ea):
    """A struct returned through a hidden buffer, with register arguments besides: IDA has no
    way to write that convention. LTCG passes the buffer in a register of its own and returns
    it in eax (SplinePathDynCubeObj_GetInterpolatedPosition: buffer in eax, ptQTask in ecx,
    nSegment in edx, vT on the stack; its callers lost every argument). Say it as what it is:
    a function returning a pointer to the result, the buffer an explicit register argument -
    the one it reads on entry that no named parameter is in."""
    m = re.match(r"^(?P<ret>.+?)\s+__usercall\s+(?P<name>\w+)(?:@<\w+>)?\((?P<args>.*)\)$", decl.strip())
    if not m:
        return None
    used = set(re.findall(r"@<(\w+)>", m.group("args")))
    full = {"al": "eax", "ax": "eax", "cl": "ecx", "cx": "ecx", "dl": "edx", "dx": "edx",
            "bl": "ebx", "bx": "ebx", "si": "esi", "di": "edi"}
    used = {full.get(r, r) for r in used}
    # registers the function itself reads first (a call's possible reads would point at any)
    spare = [r for r in entry_register_reads(ea, calls_read=False)
             if r not in used and r in ("eax", "ecx", "edx", "ebx", "esi", "edi")]
    ret = m.group("ret").strip()
    args = m.group("args").strip()
    if spare:
        buffer = f"{ret} *retstr@<{'eax' if 'eax' in spare else spare[0]}>"
    else:
        # none: the buffer is the first stack argument, as plain C passes it
        # (NetworkConfig_SetIntFromStringArg reads it from [esp+arg_0])
        buffer = f"{ret} *retstr"
    return f"{ret} *__usercall {m.group('name')}@<eax>({buffer}{', ' + args if args and args != 'void' else ''})"


def apply_abi():
    """Give every game function its arguments' real locations: the PDB prototype with the
    registers its own records name (pdb_registers). Functions the PDB has no match for get the
    decompiler's measurement plus the registers the census saw read uninitialized (hints)."""
    cl = json.loads((REPO / "symbols" / "final.json").read_text())
    m = json.loads((REPO / "symbols" / "match.json").read_text())
    abi = json.loads((REPO / "symbols" / "abi.json").read_text())
    by_rva = {str(f["rva"]): f for f in cl["functions"] if f["rva"] is not None}
    # registers the last export read before writing (census.py): arguments the measurement missed
    hints_path = REPO / "build" / "abi_hints.json"
    hints = json.loads(hints_path.read_text()) if hints_path.exists() else {}
    status, report = {}, {}
    for rva, v in m.items():
        f = by_rva[rva]
        if v["ea"] is None or not f["prototype"] or v["lib"] != "j.lib":
            continue  # library code takes its prototypes from the SDK headers (libtypes)
        name = ida_name.get_name(v["ea"])
        measured = abi.get(str(v["ea"]), {"cc": "cdecl", "ret": "void", "retloc": None, "args": []})
        decl, st = merge_abi(f, measured, pdb_registers(f, v["ea"], measured))
        extra = ltcg_extra_decl(f, v["ea"], measured, decl)
        if extra:
            decl, st = extra, "usercall-ltcg-extra"
        if decl:
            decl = decl.replace(f" {f['name']}(", f" {name}(", 1).replace(f" {f['name']}@", f" {name}@", 1)
            if not idc.SetType(v["ea"], ida_text(decl) + ";"):
                # a register location written after a declarator that wraps the name:
                # "X *(*papt)[5]@<eax>" is "X *(*papt@<eax>)[5]" to IDA
                fixed = re.sub(r"\(\*(\w+)\)((?:\[\d+\])+)@<(\w+)>", r"(*\1@<\3>)\2", decl)
                fixed = re.sub(r"\(\*(\w+)\)(\([^()]*\))@<(\w+)>", r"(*\1@<\3>)\2", fixed)
                if fixed != decl and idc.SetType(v["ea"], ida_text(fixed) + ";"):
                    decl = fixed
                else:
                    st = "usercall-rejected"
            if st == "usercall-rejected":
                if f["ret_is_aggregate"]:
                    alt = struct_return_decl(decl, v["ea"])
                    if alt and idc.SetType(v["ea"], ida_text(alt) + ";"):
                        decl, st = alt, "usercall-struct-return"
        status[st] = status.get(st, 0) + 1
        report[str(v["ea"])] = {"name": name, "status": st, "decl": decl}
    # functions the PDB has no match for (sub_XXXXXX) with hints: measured plus hinted
    for name, regs in hints.items():
        ea = ida_name.get_name_ea(idc.BADADDR, name)
        if ea == idc.BADADDR or str(ea) in report or str(ea) not in abi:
            continue
        if any(True for _ in idautils.DataRefsTo(ea)):
            # its address is taken (an event handler in a table, Water_UpdateInternalDataHandler):
            # such calls pass everything on the stack, and the census's uninitialized reads are
            # the decompiler's, not arguments
            continue
        measured = dict(abi[str(ea)])
        have = {a[1] for a in measured["args"] if a[0] == "reg"}
        measured["args"] = [["reg", r, size, None] for r, size in regs if r not in have] + measured["args"]
        decl = measured_decl(name, measured)
        st = "unmatched+hint" if idc.SetType(ea, decl + ";") else "unmatched+hint-rejected"
        status[st] = status.get(st, 0) + 1
        report[str(ea)] = {"name": name, "status": st, "decl": decl}
    (REPO / "symbols" / "abi_applied.json").write_text(json.dumps(report, indent=1))
    print(f"abi: {status}", flush=True)


FPU_COMPARE = ("fcom", "fcomp", "fcompp", "fucom", "fucomp", "fucompp", "ficom", "ficomp", "ftst")
FPU_KEEPS_FLAGS = ("fld", "fild", "fld1", "fldz", "fldpi", "fxch", "fst", "fstp", "fist", "fistp", "fchs",
                   "fabs", "fadd", "faddp", "fsub", "fsubp", "fsubr", "fsubrp", "fmul", "fmulp", "fdiv",
                   "fdivp", "fdivr", "fdivrp", "fiadd", "fisub", "fimul", "fidiv")


def fpu_flags():
    """Move "fnstsw ax" up to the comparison it reads, in the analysis database only.

    The compiler scheduled independent work between an x87 compare and the fnstsw that fetches
    its result (fcomp; fld x; fnstsw ax; test ah, 5). The hardware leaves C0/C2/C3 alone across
    that work, but the manuals call them undefined, so the decompiler drops the comparison and
    the branch tests flags nothing set ("if ( v20 | v21 )" on c0/c2). Swapping the bytes so the
    fnstsw follows the compare changes nothing the program does; the rebuilt exe runs no retail
    code, and the image it carries is read from the exe file, not from this database."""
    import ida_funcs
    import idautils
    moved = 0
    for fea in idautils.Functions():
        f = ida_funcs.get_func(fea)
        if f.flags & ida_funcs.FUNC_LIB or not 0x401000 <= fea < 0x65C000:
            continue
        items = sorted(idautils.FuncItems(fea))
        for k, ea in enumerate(items):
            if idc.print_insn_mnem(ea) not in FPU_COMPARE:
                continue
            between = []
            for nxt in items[k + 1:k + 6]:
                mnem = idc.print_insn_mnem(nxt)
                if mnem == "fnstsw":
                    if between and idc.print_operand(nxt, 0) == "ax" and \
                            not any(ida_xref_to(b) for b in between + [nxt]):
                        start = between[0]
                        end = nxt + idc.get_item_size(nxt)
                        code = ida_bytes.get_bytes(start, end - start)
                        cut = nxt - start
                        ida_bytes.patch_bytes(start, code[cut:] + code[:cut])
                        ida_bytes.del_items(start, ida_bytes.DELIT_SIMPLE, end - start)
                        at = start
                        while at < end:
                            at += idc.create_insn(at) or 1
                        moved += 1
                    break
                ops = idc.print_operand(nxt, 0) + " " + idc.print_operand(nxt, 1)
                touches_ax = re.search(r"\b(e?ax|ah|al)\b", ops)
                if mnem in FPU_KEEPS_FLAGS and not touches_ax:
                    between.append(nxt)
                elif not mnem.startswith(("f", "j", "call", "ret", "push", "pop")) and not touches_ax \
                        and mnem in ("mov", "lea", "add", "sub", "inc", "dec", "shl", "shr", "and", "or"):
                    between.append(nxt)  # integer work: leaves the FPU status alone
                else:
                    break
    ida_auto.auto_wait()
    print(f"fpu flags: {moved} fnstsw moved next to their compare", flush=True)


def ida_xref_to(ea):
    """True when anything but the previous instruction's flow reaches ea (a jump target)."""
    import idautils
    return any(x.type not in (21,) for x in idautils.XrefsTo(ea, 0))  # 21: ordinary flow


SCRATCH = ("eax", "ecx", "edx")
REG32 = {"al": "eax", "ah": "eax", "ax": "eax", "eax": "eax", "cl": "ecx", "ch": "ecx", "cx": "ecx", "ecx": "ecx",
         "dl": "edx", "dh": "edx", "dx": "edx", "edx": "edx"}
IMPLICIT = {"mul": ("eax", "edx"), "div": ("eax", "edx"), "idiv": ("eax", "edx"), "cdq": ("edx",),
            "cwde": ("eax",), "cbw": ("eax",), "cwd": ("edx",), "lahf": ("eax",), "fnstsw": ("eax",),
            "cpuid": SCRATCH, "rdtsc": ("eax", "edx"), "lods": ("eax",), "scas": ("ecx",),
            "xlat": ("eax",), "stos": ("ecx",), "movs": ("ecx",), "cmps": ("ecx",), "loop": ("ecx",)}


def apply_spoils():
    """Which of eax/ecx/edx each game function really changes, its callees' included, as
    __spoils<...> in its type. Link-time code generation knew, and let callers keep values in the
    ones a callee leaves alone (VehicleType_DefineVehicleType walks its wings in ecx across
    Wing_Init(ptWing@ecx)); the decompiler assumes all three are lost at every call unless the
    type says otherwise, and the rebuilt caller then reads a register nothing set."""
    import ida_funcs
    import ida_ua
    import idautils
    game = [ea for ea in idautils.Functions() if not ida_funcs.get_func(ea).flags & ida_funcs.FUNC_LIB
            and 0x401000 <= ea < 0x65C000]
    direct, calls = {}, {}
    for ea in game:
        written, callees = set(), set()
        for item in idautils.FuncItems(ea):
            insn = ida_ua.insn_t()
            if not ida_ua.decode_insn(insn, item):
                continue
            mnem = insn.get_canon_mnem()
            if mnem == "call":
                target = idc.get_operand_value(item, 0)
                f = ida_funcs.get_func(target) if insn.ops[0].type in (ida_ua.o_near, ida_ua.o_far) else None
                if f and f.start_ea == target:
                    callees.add(target)
                else:
                    written |= set(SCRATCH)  # through a pointer, or an import: assume the worst
                continue
            if mnem in ("jmp",) and insn.ops[0].type in (ida_ua.o_near, ida_ua.o_far):
                target = idc.get_operand_value(item, 0)
                f = ida_funcs.get_func(target)
                if f and f.start_ea == target and target != ea:
                    callees.add(target)  # a tail call
                continue
            for r in IMPLICIT.get(mnem, ()):
                written.add(r)
            if mnem == "imul" and insn.ops[1].type == ida_ua.o_void:
                written |= {"eax", "edx"}
            feature = insn.get_canon_feature()
            for n in range(3):
                op = insn.ops[n]
                if op.type == ida_ua.o_reg and feature & (ida_idp_chg(n)):
                    name = idc.print_operand(item, n)
                    if name in REG32:
                        written.add(REG32[name])
            if mnem == "xchg":
                written |= {REG32[o] for o in (idc.print_operand(item, 0), idc.print_operand(item, 1)) if o in REG32}
        direct[ea], calls[ea] = written, callees
    spoils = {ea: set(w) for ea, w in direct.items()}
    changed = True
    while changed:
        changed = False
        for ea, callees in calls.items():
            before = len(spoils[ea])
            for c in callees:
                spoils[ea] |= spoils.get(c, set(SCRATCH))  # library code: the C convention
            changed |= len(spoils[ea]) != before
    applied = 0
    for ea, regs in spoils.items():
        regs &= set(SCRATCH)
        if regs == set(SCRATCH):
            continue
        decl = idc.get_type(ea)
        if not decl or "__spoils" in decl:
            continue
        name = ida_name.get_name(ea)
        cc = re.search(r"__(cdecl|stdcall|usercall|userpurge|fastcall|thiscall)\b", decl)
        if not cc:
            continue
        spoil = f"__spoils<{', '.join(r for r in SCRATCH if r in regs)}>"
        full = decl[:cc.end()] + f" {spoil} {name}" + decl[cc.end():]
        applied += bool(idc.SetType(ea, full + ";"))
    print(f"spoils: {applied} functions leave some of eax/ecx/edx alone", flush=True)


def ida_idp_chg(n):
    import ida_idp
    return (ida_idp.CF_CHG1, ida_idp.CF_CHG2, ida_idp.CF_CHG3)[n]


ARITH = {"and", "or", "xor", "test", "cmp", "add", "sub", "adc", "sbb", "imul", "mul", "shl", "shr",
         "sar", "rol", "ror", "bt", "bts", "btr", "btc"}


def immediates():
    """The retail BSS spans 0x6AB000-0x8273000, so IDA takes many constants in that numeric range
    (0x800000, the MMX CPUID bit) for addresses and the decompiler prints them as &global[...].
    An immediate that is an operand of arithmetic or a comparison is a number: make it one."""
    import ida_funcs
    import ida_ua
    import idautils
    fixed = 0
    for fea in idautils.Functions():
        f = ida_funcs.get_func(fea)
        if f.flags & ida_funcs.FUNC_LIB:
            continue
        for ea in idautils.FuncItems(fea):
            fl = ida_bytes.get_flags(ea)
            if not ida_bytes.is_code(fl):
                continue
            mnem = idc.print_insn_mnem(ea)
            if mnem == "mov" and idc.print_operand(ea, 0) == "eax" and ida_bytes.is_off(fl, 1):
                # the fill value of a "rep stosd" (memset32) is a number, never an address
                nxt = ea
                for _ in range(6):
                    nxt = idc.next_head(nxt, f.end_ea)
                    if nxt == idc.BADADDR or "eax" in idc.print_operand(nxt, 0):
                        break
                    if "stosd" in idc.GetDisasm(nxt):
                        ida_bytes.op_num(ea, 1)
                        fixed += 1
                        break
                continue
            if mnem in ("cmp", "mov", "push"):
                for n in range(2):
                    v = idc.get_operand_value(ea, n)
                    target = ida_funcs.get_func(v) if idc.get_operand_type(ea, n) == idc.o_imm else None
                    if target and target.start_ea == v and v % 16 == 0 and not ida_bytes.is_off(fl, n):
                        idc.op_plain_offset(ea, n, 0)  # a game function's address IDA left a number
                        fixed += 1
            if mnem not in ARITH:
                continue
            for n in range(2):
                if idc.get_operand_type(ea, n) == idc.o_imm and ida_bytes.is_off(fl, n):
                    target = ida_funcs.get_func(idc.get_operand_value(ea, n))
                    if target and target.start_ea == idc.get_operand_value(ea, n):
                        continue  # "cmp [eax+18h], offset Handler": a function's identity
                    ida_bytes.op_num(ea, n)
                    fixed += 1
    # any immediate "pointing" into code but not at a function start is a constant that happens
    # to fall in the .text range (0x0065736E is the four characters "nse")
    text_seg = ida_segment.get_segm_by_name(".text")
    for fea in idautils.Functions():
        if ida_funcs.get_func(fea).flags & ida_funcs.FUNC_LIB:
            continue
        for ea in idautils.FuncItems(fea):
            fl = ida_bytes.get_flags(ea)
            if not ida_bytes.is_code(fl):
                continue
            for n in range(2):
                if idc.get_operand_type(ea, n) != idc.o_imm or not ida_bytes.is_off(fl, n):
                    continue
                v = idc.get_operand_value(ea, n)
                target = ida_funcs.get_func(v)
                if text_seg.start_ea <= v < text_seg.end_ea and not (target and target.start_ea == v):
                    ida_bytes.op_num(ea, n)
                    fixed += 1
    # the same in data: a stored value IDA made an offset into the middle of code
    for s in idautils.Segments():
        if idc.get_segm_name(s) not in (".rdata", ".data", ".data1"):
            continue
        for ea in idautils.Heads(s, idc.get_segm_end(s)):
            fl = ida_bytes.get_flags(ea)
            if ida_bytes.is_code(fl) or not ida_bytes.is_off0(fl) or ida_bytes.get_item_size(ea) != 4:
                continue
            v = ida_bytes.get_dword(ea)
            target = ida_funcs.get_func(v)
            if text_seg.start_ea <= v < text_seg.end_ea and not (target and target.start_ea == v):
                ida_bytes.op_num(ea, 0)
                fixed += 1
    print(f"immediates: {fixed} arithmetic constants were addresses, now numbers", flush=True)


def manual_types():
    """overrides/ida_types.json: prototypes checked by hand against the disassembly, where the
    automatic steps get a convention wrong. Applied last, every time. A key that is an address
    ("0x5986B0") is retail code with no Final counterpart: it also takes the name in its decl."""
    path = REPO / "overrides" / "ida_types.json"
    if not path.exists():
        return
    n = bad = 0
    for name, decl in json.loads(path.read_text()).items():
        if name == "_comment":
            continue
        if name.startswith("0x"):
            ea = int(name, 16)
            ida_name.set_name(ea, re.search(r"(\w+)(?:@<\w+>)?\s*\(", decl).group(1), ida_name.SN_FORCE)
        else:
            ea = ida_name.get_name_ea(idc.BADADDR, name)
        if ea != idc.BADADDR and idc.SetType(ea, ida_text(decl) + ";"):
            n += 1
        else:
            bad += 1
            print(f"  manual type rejected: {name}", flush=True)
    print(f"manual types: {n} applied, {bad} rejected", flush=True)


def library_types():
    """Library code the signatures recognised (strncpy, sprintf, ...) has a name but no type:
    give each its prototype from the SDK type library, so calls decompile with the right arity."""
    import ida_funcs
    import idautils
    system = set(json.loads((REPO / "build" / "system_idents.json").read_text()))
    protos = json.loads((REPO / "build" / "system_protos.json").read_text())
    n = 0
    for ea in idautils.Functions():
        f = ida_funcs.get_func(ea)
        name = ida_name.get_name(ea)
        named_like_crt = name.lstrip("_") in system and not idc.get_type(ea)  # CRT names from the PDB
        if not (f.flags & ida_funcs.FUNC_LIB or f.flags & ida_funcs.FUNC_THUNK or named_like_crt):
            continue
        for candidate in (name, name.lstrip("_"), name.lstrip("j_").lstrip("_")):
            if ida_typeinf.apply_named_type(ea, candidate):
                n += 1
                break
            if candidate in protos and idc.SetType(ea, protos[candidate] + ";"):
                n += 1  # the C runtime: its prototype as today's headers declare it
                break
    print(f"library types: {n} prototypes from the SDK type library", flush=True)


def library_names():
    """Library code the matcher has no anchors in (d3dx8, the ASE query SDK, Miles' static part)
    keeps its layout between the Final build and retail, only shifted: name each unnamed function
    from the Final map's publics, trying the shifts of the nearest matched functions and taking
    one that lands exactly on a public. A stdcall public (_X@N) also gives the argument bytes.
    Library functions matched on size alone are renamed the same way when the shift says
    otherwise (ASEQuery_shutdown had been taken for a C++ destructor of the same size)."""
    import bisect
    import idautils
    cl = json.loads((REPO / "symbols" / "final.json").read_text())
    m = json.loads((REPO / "symbols" / "match.json").read_text())
    publics = {p["rva"] + 0x400000: p["name"] for p in cl["publics"] if p["code"] or p["function"]}
    anchors = sorted((v["ea"], v["ea"] - (int(rva) + 0x400000)) for rva, v in m.items()
                     if v["ea"] and not v["how"].startswith("size"))  # only matches the code confirmed
    weak = {v["ea"] for v in m.values() if v["ea"] and v["how"].startswith("size")
            and (v["lib"] != "j.lib" or "::" in v["name"])}  # library, or the C++ the game links
    starts = [a for a, _ in anchors]
    named = typed = 0
    for ea in idautils.Functions():
        if not (ida_name.get_name(ea).startswith("sub_") or ea in weak):
            continue
        k = bisect.bisect_left(starts, ea)
        near = sorted(anchors[max(0, k - 4):k + 4], key=lambda a: abs(a[0] - ea))
        public = next((publics[ea - d] for _, d in near if ea - d in publics), None)
        if not public or public.startswith("?"):
            continue  # nothing there, or C++ internals of a library: never called by the game
        stdcall = re.fullmatch(r"_(\w+)@(\d+)", public)
        name = stdcall.group(1) if stdcall else public[1:] if public.startswith("_") else public
        if ida_name.get_name_ea(idc.BADADDR, name) not in (idc.BADADDR, ea):
            continue
        if ea in weak and ida_name.get_name(ea).lstrip("_") == name.lstrip("_"):
            continue  # the size match was right
        ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_NOCHECK)
        named += 1
        if stdcall:
            args = ", ".join(["int"] * (int(stdcall.group(2)) // 4)) or "void"
            typed += bool(idc.SetType(ea, f"int __stdcall {name}({args});"))
    print(f"library names: {named} named from the Final map, {typed} stdcall prototypes", flush=True)


def sanitize():
    """Rename game functions and globals whose names the system headers already declare
    (string, c_dfDIKeyboard, ...): the rebuilt program includes those headers."""
    import ida_funcs
    import idautils
    reserved = set(json.loads((REPO / "build" / "system_idents.json").read_text()))
    reserved |= {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                 "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register",
                 "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch",
                 "typedef", "union", "unsigned", "void", "volatile", "while", "bool", "true", "false"}
    # Globals become macros onto the retail image (export_data.py), and macros are not scoped:
    # a global may not share its name with any member, enumerator, parameter or local.
    scoped = set(json.loads((REPO / "build" / "scoped_names.json").read_text()))  # from gen_types.py
    cl = json.loads((REPO / "symbols" / "final.json").read_text())
    for f in cl["functions"]:
        scoped |= {l["name"] for l in f["params"] + f["locals"]}
    m = json.loads((REPO / "symbols" / "match.json").read_text())
    game = {v["ea"] for v in m.values() if v["ea"] and v["lib"] == "j.lib"}
    renamed = 0
    for ea, name in list(idautils.Names()):
        f = ida_funcs.get_func(ea)
        if f and f.flags & (ida_funcs.FUNC_LIB | ida_funcs.FUNC_THUNK):
            continue  # library code keeps its names: calls resolve to today's runtime
        if f and f.start_ea == ea and (ea not in game or name == "WinMain"):
            continue  # the C runtime's own functions (fprintf, qsort), and the entry point it calls
        if name in reserved:
            ida_name.set_name(ea, f"{name}_{ea:x}", ida_name.SN_NOWARN | ida_name.SN_NOCHECK | ida_name.SN_FORCE)
            renamed += 1
        elif not f and (name in scoped or name.lstrip("_") in scoped
                        or re.match(r"^(?:[av]\d+|result|retstr)$", name)):
            ida_name.set_name(ea, f"g_{name}", ida_name.SN_NOWARN | ida_name.SN_NOCHECK | ida_name.SN_FORCE)
            renamed += 1
    print(f"sanitize: renamed {renamed}", flush=True)


steps = sys.argv[1:] or ["types", "immediates", "functions", "fpuflags", "libnames", "globals", "locals", "abi", "libtypes", "manual",
                         "sanitize"]
if "types" in steps:
    apply_types()
if "immediates" in steps:
    immediates()
if "functions" in steps:
    apply_functions()
if "fpuflags" in steps:
    fpu_flags()
if "libnames" in steps:
    library_names()
if "globals" in steps:
    apply_globals()
if "locals" in steps:
    apply_locals()
if "abi" in steps:
    apply_abi()
if "libtypes" in steps:
    library_types()
if "settle" in steps:
    # Store each function's decompiled signature as its type, so call sites (printed from the
    # callee's stored type) agree with the definition the decompiler prints for the callee.
    import ida_funcs
    import ida_hexrays
    ida_hexrays.init_hexrays_plugin()
    n = bad = 0
    for p in sorted((REPO / "build" / "export").glob("types_*.json")):
        for ea, decl in json.loads(p.read_text()).items():
            if decl and idc.SetType(int(ea), decl + ";"):
                n += 1
            else:
                bad += 1
    # Functions the decompiler refused under their stored type: drop the type (and, when the
    # failing spot is a call, the callee's) so the decompiler deduces the convention, then store
    # what it deduced right away so pass 2 prints callers that agree.
    fixed = still = 0
    system = set(json.loads((REPO / "build" / "system_idents.json").read_text()))
    for p in sorted((REPO / "build" / "export").glob("status_*.json")):
        for name, st in json.loads(p.read_text()).items():
            if st["state"] != "failed":
                continue
            ea = st["ea"]
            idc.SetType(ea, "")
            for _ in range(4):
                hf = ida_hexrays.hexrays_failure_t()
                cf = ida_hexrays.decompile_func(ida_funcs.get_func(ea), hf, ida_hexrays.DECOMP_NO_CACHE)
                if cf:
                    break
                callee = idc.get_operand_value(hf.errea, 0) if hf.errea != idc.BADADDR else idc.BADADDR
                cf_ = ida_funcs.get_func(callee)
                library = cf_ and (cf_.flags & ida_funcs.FUNC_LIB or ida_name.get_name(callee).lstrip("_") in system)
                if cf_ and cf_.start_ea == callee and not library:
                    idc.SetType(callee, "")  # library prototypes are right: never drop those
                else:
                    break
            if cf:
                idc.SetType(ea, ida_typeinf.print_tinfo("", 0, 0, ida_typeinf.PRTYPE_1LINE, cf.type,
                                                        ida_name.get_name(ea), "") + ";")
                fixed += 1
            else:
                still += 1
    print(f"settle: {fixed} failed functions now decompile, {still} still fail", flush=True)
    print(f"settle: {n} function types stored, {bad} rejected", flush=True)
if "manual" in steps or "settle" in steps:
    manual_types()  # last word over every automatic step
    apply_spoils()  # the stored types above lose it
if "sanitize" in steps:
    # let analysis settle first: IDA names data after the parameters it is passed to (a string
    # passed as zName becomes "zName"), and those names must be sanitized too
    ida_auto.auto_wait()
    sanitize()
ida_auto.auto_wait()
idapro.close_database(save=True)
print(f"done in {time.time() - t0:.0f}s")
