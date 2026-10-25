"""Turn decompiler output into C that MSVC accepts. Pure text rules over the exported files;
idempotent, so it can run again after every export or rule change.

Calling conventions do not have to match the binary: every caller and callee is recompiled
together, so register conventions and __thiscall become plain __cdecl.

usage: uv run rewrite.py        (export.py also runs it)
"""
import json
import re
import sys

from config import REPO

RULES = [
    # IDA-only declaration syntax
    (re.compile(r"__attribute__\(\((?:[^()]|\([^()]*\))*\)\)\s*"), ""),
    (re.compile(r"@<[^>]+>"), ""),
    (re.compile(r"\b__(?:usercall|userpurge|thiscall|fastcall)\b"), "__cdecl"),
    (re.compile(r"\b__spoils<[^>]*>\s*"), ""),
    (re.compile(r"\b__hidden\s+"), ""),
    (re.compile(r"\b__return_ptr\s+"), ""),
    (re.compile(r"\b__struct_ptr\s+"), ""),
    (re.compile(r"\b__shifted\([^)]*\)\s*"), ""),
    (re.compile(r"\b__ptr32\b"), ""),
    (re.compile(r"\b__unaligned\b"), ""),
    (re.compile(r"\b__high\s+"), ""),
    # the IDA-only names of the game's own enum bool
    (re.compile(r"\benum igi_bool\b"), "enum bool"),
    (re.compile(r"\bigi_false\b"), "false"),
    (re.compile(r"\bigi_true\b"), "true"),
]
# Rules for decompiled code and its prototypes only (not data or system types)
CODE_RULES = [
    # the decompiler merges variables, so code writes through pointers the PDB declared const
    (re.compile(r"\bconst\s+(?=[\w\s\*]*[\w\*])"), ""),
    # DBL_MAX printed to 16 digits rounds past the largest double
    (re.compile(r"(?<![\w.])1\.797693134862316e308\b"), "DBL_MAX"),
    # "(char *)a + (char *)b - (char *)c" adds two pointers in C's left-to-right grouping
    (re.compile(r"\+ (\((?:char|_BYTE) \*\)&?[\w.\->\[\]]+) - (\((?:char|_BYTE) \*\)&?[\w.\->\[\]]+)"),
     r"+ (\1 - \2)"),
    # "(char *)a + b - (T *)c" where b is a pointer too: group the byte difference first
    (re.compile(r"\(((?:char|_BYTE|unsigned __int8)) \*\)(&?[\w.\->\[\]]+) \+ (&?[\w.\->\[\]]+) - "
                r"\((?:char|_BYTE|unsigned __int8|_UNKNOWN) \*\)(&?[\w.\->\[\]]+)"),
     r"(\1 *)\2 + ((char *)(\3) - (char *)(\4))"),
    # the same, wrapped over lines: "*((_BYTE *)p\n + (char *)dst\n - (char *)&src + 4)" (a strcpy)
    (re.compile(r"\(\((_BYTE|char) \*\)(\w+)\s*\+\s*\(char \*\)(\w+)\s*-\s*\(char \*\)(&[\w.\[\]>-]+)"),
     r"((\1 *)\2 + ((char *)\3 - (char *)\4)"),
    # the 2003 runtime's feof() was a macro, "fp->_flag & _IOEOF" (0x10 at +12): today's
    # runtime keeps its FILE elsewhere and 0x10 there means an error, so the graph loader read
    # past the end forever. Ask the runtime instead
    (re.compile(r"\*\(_(?:BYTE|DWORD) \*\)\(([\w.\[\]>-]+) \+ 12\) & 0x10\b"), r"feof((FILE *)\1)"),
    # a COM method is __stdcall whatever cast the decompiler put on the call: through a __cdecl
    # (or convention-less) pointer, the caller would pop the arguments the method already popped
    (re.compile(r"\(\(([^()]*?)\s*\((?:__cdecl\s*)?\*\)(\([^()]*\))\)([\w.\[\]>-]*?lpVtbl->\w+)\)"),
     r"((\1 (__stdcall *)\2)\3)"),
    # a 32-bit integer store that adds/subtracts a pointer value: the original did it in int
    (re.compile(r"^(\s*\*\(?\(?_DWORD \*\)[^;=]*?) ([+-])= (?!\(int\)\()([^;]+);$", re.M), r"\1 \2= (int)(\3);"),
    # a struct cast reinterprets an lvalue: C spells it through a pointer
    (re.compile(r"\((struct|union) (\w+)\)0(?![\w.])"), r"(\1 \2){0}"),
    (re.compile(r"\((struct|union) (\w+)\)(\*?[A-Za-z_][\w.\->\[\]]*)(?![\w.\->\[\]]*\s*\()"),
     r"(*(\1 \2 *)&\3)"),
    # a byte of a double's bits: take it from the variable itself
    (re.compile(r"\b((?:BYTE|WORD|DWORD|HIBYTE|LOBYTE|HIWORD|LOWORD|HIDWORD|LODWORD)\d*)\(COERCE_UNSIGNED_INT64\((\w+)\)\)"),
     r"\1(\2)"),
    # the x87 expansion of 2^x: fscale(f2xm1(x - round(x)) + 1, round(x))
    (re.compile(r"__FSCALE__\(__F2XM1__\((\w+) - _ST\d\) \+ 1\.0, _ST\d\)"), r"pow(2.0, \1)"),
    (re.compile(r"^\s*_ST\d = [^;]+;\n", re.M), ""),
    # SEH frame bookkeeping: the __try body is already inline
    (re.compile(r"^\s*CPPEH_RECORD ms_exc;.*\n", re.M), ""),
    (re.compile(r"^\s*ms_exc\.[^;]*;\s*\n", re.M), ""),
    # old C runtime FILE internals: _flag & _IOEOF is feof()
    (re.compile(r"\((\w+)->_flag & 0x10\) == 0"), r"!feof(\1)"),
    (re.compile(r"\((\w+)->_flag & 0x10\) != 0"), r"feof(\1)"),
    # a debugger trap left in the code
    (re.compile(r"^\s*__asm \{ icebp \}\s*\n", re.M), ""),
    # "&p[n / 0xFFFFFFE8]": stepping a pointer back over n bytes of 24-byte elements. The divisor
    # is -24, but as an unsigned constant C divides unsigned and gets 0 (World_TraceLines handed
    # the trace context pointers past the end of its point arrays). Divide signed.
    (re.compile(r"\[(\w+) / (0xFFFFFF[0-9A-F]{2})\]"), r"[(int)\1 / (int)\2]"),
    # "fstcw Real_nTempCW; or Real_nTempCW, 0C00h; fldcw Real_nTempCW" (truncating rounding):
    # the decompiler keeps only the or, and the FPU was never switched (igi2_fpu_or)
    (re.compile(r"\bReal_nTempCW \|= (0x[0-9A-Fa-f]+)u;"), r"Real_nTempCW = igi2_fpu_or(\1u);"),
    # a numeric pseudo-member: the byte at that offset inside the object
    (re.compile(r"&([A-Za-z_][\w\->.]*(?:\[[^\]\[]+\])?)\.(\d+)\b"), r"((char *)&\1 + \2)"),
    # 16-byte locals: 32-bit MSVC has no __int128
    (re.compile(r"\b(?:unsigned )?__int128\b"), "IGI2_INT128"),
    # a DS: segment override on a flat 32-bit address means nothing
    (re.compile(r"\s_ds\s*\*"), " *"),
    # a far return the decompiler could not follow: these stubs only return
    (re.compile(r"return MK_FP\(\*\(_WORD \*\)retaddr, \*\(_DWORD \*\)retaddr\)\(\);"), "return;"),
]
NORETURN = re.compile(r"^(\S.*?)\b__noreturn\s+", re.M)  # top-level declarations only


STRUCT_CAST = re.compile(r"\((struct|union) (\w+)\)(?=\()")


def struct_casts(text):
    """(struct T)(expr) reinterprets the value's bits: C needs an object to reinterpret, so the
    value goes into a compound literal of its own type first."""
    out, pos = [], 0
    for m in STRUCT_CAST.finditer(text):
        if m.start() < pos:
            continue
        i, depth = m.end(), 0
        # the operand: an optional "(type)" cast, then one parenthesized expression
        j = i
        while True:
            depth = 0
            k = j
            while k < len(text):
                depth += text[k] == "("
                depth -= text[k] == ")"
                k += 1
                if depth == 0:
                    break
            inner = text[j:k]
            if re.fullmatch(r"\((?:unsigned )?(?:__int64|int|float|double|_QWORD|_DWORD)\)", inner):
                j = k
                if j < len(text) and text[j] != "(":  # "(type)identifier": the operand is a name
                    ident = re.match(r"[\w.\->\[\]]+", text[j:])
                    k = j + (ident.end() if ident else 0)
                    break
                continue
            break
        operand = text[i:k]
        cast = re.match(r"\(((?:unsigned )?(?:__int64|int|float|double|_QWORD|_DWORD))\)", operand)
        ctype = cast.group(1) if cast else "__int64"
        out.append(text[pos:m.start()])
        out.append(f"(*({m.group(1)} {m.group(2)} *)&({ctype}){{{operand}}})")
        pos = k
    out.append(text[pos:])
    return "".join(out)


# locals only: export.py marks a variable in the argument area ARGSLOT (it is that argument's
# slot, initialized from it) and the frame union leaves it out
STACK_DECL = re.compile(r"^  (?P<decl>[^/\n=]*?;) // \[esp[+-][0-9A-F]+h\] \[ebp(?P<sign>[+-])(?P<off>[0-9A-F]+)h\](?P<tail>(?!.*ARGSLOT).*)$")
FNPTR_NAME = re.compile(r"\(\s*(?:__\w+\s+)?\*+\s*(\w+)\)\s*\(")
PLAIN_NAME = re.compile(r"(\w+)\s*(?:\[[^\]]*\]\s*)*;$")
STRING = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'')


def frame_layout(text):
    """Keep each function's stack locals where the original had them. Decompiled code reaches
    from one local into the next ("&zFilename[259]" is the byte before zSearchPath, the start of
    a strcat), and splits structs into neighbouring pieces; MSVC orders locals its own way. A
    function with arrays or address-taken locals gets one packed union, each local a member at
    its original frame offset (from the decompiler's [ebp-N] comment), and its uses become
    igi2_frame.<name>."""
    lines = text.split("\n")
    out, i = [], 0
    while i < len(lines):
        if lines[i] != "{" or i == 0:
            out.append(lines[i])
            i += 1
            continue
        end = next((j for j in range(i + 1, len(lines)) if lines[j] == "}"), len(lines) - 1)
        body = lines[i + 1:end]
        if any("igi2_frame" in line for line in body[:3]):
            out.extend(lines[i:end + 1])
            i = end + 1
            continue
        decls, rest = [], []
        for k, line in enumerate(body):
            if not line.strip():
                rest = body[k:]
                break
            decls.append(line)
        else:
            rest = []
        stack = []
        for line in decls:
            m = STACK_DECL.match(line)
            if not m:
                continue
            decl = m.group("decl")
            nm = FNPTR_NAME.search(decl) or PLAIN_NAME.search(decl)
            if nm:
                off = int(m.group("off"), 16) * (1 if m.group("sign") == "+" else -1)
                stack.append((off, nm.group(1), decl, line))
        if len(stack) < 2 or not any("BYREF" in s[3] or "[" in s[2] for s in stack):
            out.extend(lines[i:end + 1])
            i = end + 1
            continue
        base = min(s[0] for s in stack)
        members = []
        for n, (off, name, decl, _) in enumerate(sorted(stack)):
            pad = f"char igi2_o{n}[{off - base}]; " if off > base else ""
            members.append(f"    struct {{ {pad}{decl} }};")
        if base < 0:
            members.append(f"    char igi2_extent[{-base}];")  # the whole locals area, up to the frame pointer
        names = {s[1] for s in stack}
        moved = {s[3] for s in stack}
        frame = ["  #pragma pack(push, 1)", "  union", "  {", *members,
                 "  } igi2_frame; // the original stack frame: every local at its own offset",
                 "  #pragma pack(pop)"]
        use = re.compile(r"(?<![\w.>])(" + "|".join(map(re.escape, sorted(names, key=len, reverse=True))) + r")\b")

        def requalify(line):
            parts, pos = [], 0
            for s in STRING.finditer(line):
                parts.append(use.sub(r"igi2_frame.\1", line[pos:s.start()]))
                parts.append(s.group(0))
                pos = s.end()
            parts.append(use.sub(r"igi2_frame.\1", line[pos:]))
            return "".join(parts)

        kept = [d for d in decls if d not in moved]
        out.extend([lines[i], *frame, *kept, *map(requalify, rest), lines[end]])
        i = end + 1
    return "\n".join(out)


HASH_TABLE = r"[\w.>-]+?"  # Symbol_ptSymbolHashTable, v8, ptQVM->ptTable ...
HASH2 = re.compile(r"(?P<var>\w+) = (?P<t>" + HASH_TABLE + r")->tPrivate\.pfHashFunction\(\s*(?P<size>[^,;()]+(?:\([^()]*\))?[^,;()]*),\s*(?P<key>[^;]+?)\);")
HASH1 = re.compile(r"(?P<var>\w+) = \(\((?:unsigned )?int \(__cdecl \*\)\(unsigned int\)\)(?P<t>" + HASH_TABLE + r")->tPrivate\.pfHashFunction\)\(\s*(?P<size>[^;()]+)\);")
LOOKUP = re.compile(r"\(\((?P<ret>[\w ]+?\s*\**)\s*\(__cdecl \*\)\(struct QHashTable_s \*, (?:unsigned )?int\)\)(?P<t>" + HASH_TABLE + r")->tPrivate\.pf(?P<op>Find|Delete)Element\)\(\s*(?P<a>[^,;()]+),\s*(?P<h>\w+)\)")


_VOID_FUNCS = None


def void_functions():
    """Library functions declared void (qsort, srand, AIL_pause_stream...)."""
    global _VOID_FUNCS
    if _VOID_FUNCS is None:
        # the C runtime's void functions (system_protos.json has only what the SDK headers type)
        _VOID_FUNCS = {"qsort", "srand", "free", "exit", "abort", "_splitpath", "_makepath", "perror",
                       "rewind", "setbuf", "clearerr", "_exit", "longjmp"}
        protos = REPO / "build" / "system_protos.json"
        if protos.exists():
            _VOID_FUNCS |= {n for n, p in json.loads(protos.read_text()).items() if re.match(r"void\s+(?!\*)", p)}
        mss = (REPO / "include" / "mss_api.h").read_text()
        _VOID_FUNCS |= set(re.findall(r"^void\s+__stdcall (\w+)\(", mss, re.M))
    return _VOID_FUNCS


SELF_INDEXED = re.compile(r"\b(?P<base>\w+)\[\(_DWORD\)(?P<p>\w+)\] = \*(?P=p);")


def self_indexed_copies(text):
    """An inlined strcpy into a local array keeps the distance array - source in a register and
    stores through [source + distance]; the decompiler prints it "zPath[(_DWORD)p] = *p",
    dropping the "- source" (devSTD_CheckAndCreateDir copies its drive name over the frame).
    The source is the walking pointer's last assignment before the loop."""
    def fix(m):
        base, p = m.group("base"), m.group("p")
        if not re.search(rf"^  [^/\n]*\b{base}\[\d+\];", text[:m.start()], re.M):
            return m.group(0)  # not an array: the variable already holds the distance
        starts = list(re.finditer(rf"^\s*{p} = (?:\([^()]*\))?(?P<src>[\w.>-]+);$", text[:m.start()], re.M))
        if not starts:
            return m.group(0)
        return f"{base}[{p} - (char *){starts[-1].group('src')}] = *{p};"
    return SELF_INDEXED.sub(fix, text)


# the hash call may be wrapped over lines: [^;] spans them
RAW_HASH = re.compile(r"^\s*(?P<h>\w+) = \(\*\(int \(__cdecl \*\*\)\([^()]*\)\)\([^;]+? \+ 12\)\)\((?P<args>[^;]*)\);$", re.M)


def top_level_args(args):
    out, depth, cur = [], 0, ""
    for ch in args:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    return out + [cur.strip()]


def raw_hash_lookups(text):
    """A hash table reached through an untyped pointer (a hierarchy's anim table:
    Hierarchy_GetAnim, WeaponTypeAnim_MakeAnimTable): pfHashFunction (+12) takes the key and
    pfFindElement (+28) needs it again, but the compiler pushed it once for both and the
    decompiler gives the find only (table, hash), so the key came from whatever was on the
    stack. The find's key is the hash call's last argument."""
    out = []
    for fn in re.split(r"(?<=\n}\n)", text):  # a hash and its find are in one function
        for m in reversed(list(RAW_HASH.finditer(fn))):  # from the end: earlier offsets stay valid
            h = m.group("h")
            key = re.sub(r"\s+", " ", top_level_args(m.group("args"))[-1])
            # pfFindElement (+28) and pfDeleteElement (+32): MTP_Free deleted with no key, and
            # the chained delete compared names at address 0x100 when the game closed
            find = re.compile(rf"\(\*\((?P<rt>[^()]*?)\s*\(__cdecl \*\*\)\(int, int\)\)\((?P<x>\w+) \+ (?P<off>28|32)\)\)\((?P=x), {h}\)")
            rest = fn[m.end():]
            f = find.search(rest)
            if f:
                fixed = (f"(*({f.group('rt')} (__cdecl **)(int, int, const void *))({f.group('x')} + {f.group('off')}))"
                         f"({f.group('x')}, {h}, (const void *)({key}))")
                fn = fn[:m.end()] + rest[:f.start()] + fixed + rest[f.end():]
        out.append(fn)
    return "".join(out)


# QTask_s header fields the decompiler reaches through "ptQTask[12].ptParent" when the slot is
# really an int in the task type's own data (SplinePathDynCubeObj's node count at +0x200)
TASK_POINTER_FIELD = r"[A-Za-z_]\w*(?:\[\d+\])?(?:\.|->)(?:ptParent|ptNext|ptPrev|tQTaskChildren\.pt\w+|tQTaskRefList\.pt\w+)\b"


def _group_end(t, i):
    """index of the parenthesis closing the one at t[i]"""
    depth = 0
    for j in range(i, len(t)):
        depth += t[j] == "("
        depth -= t[j] == ")"
        if depth == 0:
            return j
    return -1


def com_stdcall_casts(text):
    """"(*(int (__cdecl **)(int))(*(_DWORD *)*a3 + 48))(*a3)": a COM method (the object whose
    table is read is the first argument; here IDirect3DIndexBuffer8::Unlock) cast as cdecl. The
    method pops its argument and the C popped it again: esp ended 4 high, the epilogue's pops of
    edi/esi/ebx came back one slot off, and the caller's task pointer was garbage
    (sub_5C5600 -> EditRigidObj_UpdateInternalDataHandler crashed loading mission 36)."""
    out, pos = [], 0
    for m in re.finditer(r"\(\*\([^()]*?\(__cdecl \*\*\)", text):
        start = m.start()
        if start < pos:
            continue
        end = _group_end(text, start)
        if end < 0 or end + 1 >= len(text) or text[end + 1] != "(":
            continue
        group = text[start:end + 1]
        mm = re.search(r"\)\)\(\*\(_DWORD \*\)(.+) \+ (\d+)\)\)$", group)
        if not mm:
            continue
        args = text[end + 2:_group_end(text, end + 1)]
        obj = mm.group(1)
        if args == obj or args.startswith(obj + ","):
            out.append(text[pos:start])
            out.append(group.replace("(__cdecl **)", "(__stdcall **)", 1))
            pos = end + 1
    out.append(text[pos:])
    return "".join(out)


def fpu_status_bytes(text):
    """"fcomp; fnstsw ax; test ah, 5; jp": the decompiler computes the compare's condition codes
    into variables (c0, c2, c3) but leaves the status byte they make ("fps^1") unassigned and
    tests that: World_TriggerQTaskEventAlongLineSpecificTree's isTouchingLine (and doors, gears,
    hatches, the human view...) came from stack garbage. The byte is C0 in bit 0, C2 in bit 2 and
    C3 in bit 6 (fnstsw's high byte): assign it after the compare's last flag."""
    out = []
    for fn in re.split(r"(?<=\n}\n)", text):
        fps = re.findall(r"^  \w[\w ]*? (v\d+); // fps\^1$", fn, re.M)
        if fps:
            flags = {kind: set(re.findall(rf"^  \w[\w ]*? (v\d+); // {kind}$", fn, re.M)) for kind in ("c0", "c2", "c3")}

            def assign(m):
                body = m.group(0)
                last = {}
                for lm in re.finditer(r"^\s*(v\d+) = [^;]*;$", body, re.M):
                    for kind, names in flags.items():
                        if lm.group(1) in names:
                            last[kind] = lm.group(1)
                if "c3" not in last and "c0" not in last:
                    return body
                parts = [last.get("c0", "0"), f"({last.get('c2', '0')} << 2)", f"({last.get('c3', '0')} << 6)"]
                return body + f"\n{m.group('ind')}{fps[0]} = (char)({' | '.join(parts)});"

            c3 = "|".join(sorted(flags["c3"] | flags["c0"])) or "(?!)"
            # a run of flag assignments ending with the c3 (or c0) one
            fn = re.sub(rf"(?P<ind>^[ \t]*)(?:(?:v\d+) = [^;\n]*;\n[ \t]*){{0,3}}(?:{c3}) = [^;\n]*;(?=\n)(?!\n[ \t]*{fps[0]} = )",
                        assign, fn, flags=re.M)
        out.append(fn)
    return "".join(out)


def counter_fields(text):
    """"++ptQTask[12].ptParent" is an inc of an int slot the decompiler typed as a QTask
    pointer: in C, ++ on a pointer adds the size it points to (0x28, so the spline path's
    node count went 0 -> 40 and InitPath read nodes that are not there). Count in ints."""
    text = re.sub(rf"(\+\+|--)({TASK_POINTER_FIELD})", r"\1*(int *)&\2", text)
    return re.sub(rf"(?<![\w.>\]])({TASK_POINTER_FIELD})(\+\+|--)", r"(*(int *)&\1)\2", text)


def signed_dword_conversions(text):
    """"(double)v12[0]" of a _DWORD local is an fild, a signed load: the decompiler leaves the
    sign to _DWORD, which is unsigned here, and a mouse delta of -1 became 4294967295 (the menu
    cursor ran to the edge of the screen). Per function: its locals declared _DWORD."""
    out = []
    for fn in re.split(r"(?<=\n}\n)", text):
        names = set(re.findall(r"^  _DWORD (\w+)(?:\[\d+\])*; //", fn, re.M))
        if names:
            fn = re.sub(rf"\((double|float)\)(?=({'|'.join(sorted(names))})\b)", r"(\1)(int)", fn)
        out.append(fn)
    return "".join(out)


def void_results(text):
    """"return (T *)qsort(...);": a function that ends by jumping to a void library function
    returns whatever eax held, which nothing uses. In C a void call has no value: make the call
    a statement and return 0 (or assign 0)."""
    names = void_functions()
    out, pos = [], 0
    for m in re.finditer(r"^(?P<ind>[ \t]*)(?P<lhs>return|\w+ =) (?:\([^()]*\))?(?P<f>\w+)\(", text, re.M):
        if m.group("f") not in names or m.start() < pos:
            continue
        depth, k = 0, m.end() - 1
        while k < len(text):
            depth += text[k] == "("
            depth -= text[k] == ")"
            k += 1
            if depth == 0:
                break
        if text[k:k + 1] != ";":
            continue
        call = text[m.end() - len(m.group("f")) - 1:k]
        lhs = "return 0;" if m.group("lhs") == "return" else f"{m.group('lhs')} 0;"
        out.append(text[pos:m.start()])
        out.append(f"{m.group('ind')}{call};\n{m.group('ind')}{lhs}")
        pos = k + 1
    out.append(text[pos:])
    return "".join(out)


CREATE = re.compile(r"\(\((?P<ret>[\w ]+?\s*\**)\s*\(__cdecl \*\)\(struct QHashTable_s \*, (?:unsigned )?int\)\)(?P<t>" + HASH_TABLE + r")->tPrivate\.pfCreateElement\)\(\s*(?P<a>[^,;()]+),\s*(?P<h>\w+)\)")
_IDA_TYPES = None


def hash_elements():
    """overrides/hash_elements.json: the element each hash-table insert passes, by function."""
    path = REPO / "overrides" / "hash_elements.json"
    return json.loads(path.read_text()) if path.exists() else {}


def ida_types():
    """Each exported function's IDA declaration (build/export/types_*.json), with the registers
    its arguments arrive in, which the C text no longer shows."""
    global _IDA_TYPES
    if _IDA_TYPES is None:
        _IDA_TYPES = {}
        for p in (REPO / "build" / "export").glob("types_*.json"):
            for decl in json.loads(p.read_text()).values():
                m = re.search(r"(\w+)(?:@<\w+>)?\(", decl or "")
                if m:
                    _IDA_TYPES[m.group(1)] = decl
    return _IDA_TYPES


def hash_table_calls(text):
    """The game's hash-table macros expand to t->pfFindElement(t, t->pfHashFunction(size, key),
    key): the key is pushed before the hash call and the decompiler hands that push to the
    wrong call, or (pushed straight from an ecx argument with "push ecx") takes it for a stack
    reservation and drops it. The key the lookup lost is the one the hash call hashed; where the
    hash call lost it too, it is the function's one parameter the body never reads."""
    out, pos = [], 0
    for fn in re.finditer(r"^\{\n(?P<body>.*?)^\}", text, re.M | re.S):
        body = fn.group("body")
        if "pfHashFunction" not in body:
            continue
        keys = {m.group("var"): m.group("key") for m in HASH2.finditer(body)}
        head = "".join(line for line in text[text.rfind("\n\n", 0, fn.start()) + 1:fn.start()].splitlines(True)
                       if not line.startswith("//"))  # the signature, without the source comment
        name = re.search(r"(\w+)\s*\(", head)
        name = name.group(1) if name else ""
        if HASH1.search(body):
            params = [re.findall(r"(\w+)\s*(?:\[[^\]]*\])?$", p.strip()) for p in
                      re.sub(r"\([^()]*\)", "", head.split("(", 1)[1].rsplit(")", 1)[0]).split(",")] \
                if "(" in head else []
            unused = [p[0] for p in params if p and p[0] != "void" and not re.search(rf"\b{p[0]}\b", body)]
            in_regs = re.findall(r"(\w+)@<\w+>", ida_types().get(name, ""))
            if len(unused) == 1:
                key = unused[0]
            elif len(in_regs) == 1:  # pushed straight from its register ("push edi" twice)
                key = in_regs[0]
            else:
                continue  # cannot tell which value was the key: leave it for an override

            def fix_hash(m):
                keys[m.group("var")] = key
                return f"{m.group('var')} = {m.group('t')}->tPrivate.pfHashFunction({m.group('size')}, {key});"
            body = HASH1.sub(fix_hash, body)

        def fix_lookup(m):
            key = keys.get(m.group("h"))
            if key is None:
                return m.group(0)
            return (f"(({m.group('ret')} (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))"
                    f"{m.group('t')}->tPrivate.pf{m.group('op')}Element)({m.group('a')}, {m.group('h')}, "
                    f"(const void *)({key}))")
        body = LOOKUP.sub(fix_lookup, body)

        def fix_create(m):
            key, element = keys.get(m.group("h")), hash_elements().get(name)
            if key is None or element is None:
                return m.group(0)
            if m.group("ret").strip() == "void":
                return (f"{m.group('t')}->tPrivate.pfCreateElement({m.group('a')}, {m.group('h')}, "
                        f"(const void *)({key}), (const void *)({element}))")
            # the caller passes on what the insert left in eax: keep the decompiler's return type
            return (f"(({m.group('ret')} (__cdecl *)(struct QHashTable_s *, unsigned int, const void *, const void *))"
                    f"{m.group('t')}->tPrivate.pfCreateElement)({m.group('a')}, {m.group('h')}, "
                    f"(const void *)({key}), (const void *)({element}))")
        body = CREATE.sub(fix_create, body)
        out.append(text[pos:fn.start("body")])
        out.append(body)
        pos = fn.end("body")
    out.append(text[pos:])
    return "".join(out)


# "x = a * log2(e); __asm { frndint } y = 1.0 / pow(2.0, x);": the decompiler turns the x87 2^x
# sequence (frndint, f2xm1, fscale) into pow(2.0, x) and leaves its frndint behind as a statement.
# Compiled, that rounds whatever the FPU holds on top, which can be x itself: the fog factor then
# stepped in whole powers of two (Direct3DRender_SetFogParameters: the view model went flat fog
# colour as the view pitched and flashed on landing; TerrainRender_CalculateRenderVertex too)
STRAY_FRNDINT = re.compile(r"^[ \t]*__asm \{ frndint \}\n(?=[^\n]*\bpow\(2\.0, )", re.M)


def rewrite(text):
    for rx, repl in RULES:
        text = rx.sub(repl, text)
    text = STRAY_FRNDINT.sub("", text)
    # "ret __cdecl __noreturn f(...)" -> "__declspec(noreturn) ret __cdecl f(...)"
    text = NORETURN.sub(lambda m: "__declspec(noreturn) " + m.group(1), text)
    text = re.sub(r"\b__noreturn\s*", "", text)  # inside casts and expressions: meaningless in C
    return text


def files():
    yield from (REPO / "src").rglob("*.c")
    yield from (REPO / "data").glob("*.c")
    yield REPO / "include" / "igi2_protos.h"
    yield REPO / "include" / "igi2_globals.h"


def apply_patches():
    """overrides/patches.json: exact one-line fixes, for spots no general rule covers."""
    path = REPO / "overrides" / "patches.json"
    if not path.exists():
        return
    stale = []
    for p in json.loads(path.read_text()):
        src = REPO / "src" / p["file"]
        text = src.read_text(encoding="utf-8") if src.exists() else ""
        if p["replace"] in text or p["replace"] in text.replace("igi2_frame.", ""):
            continue  # already applied
        if p["find"] not in text and p["find"] in text.replace("igi2_frame.", ""):
            continue  # applied before the frame layout requalified its locals
        if p["find"] not in text:
            stale.append(f"{p['file']}: {p['find'][:60]}")
            continue
        src.write_text(text.replace(p["find"], p["replace"]), encoding="utf-8")
    for s in stale:
        print(f"  patch no longer matches: {s}")


def main():
    changed = 0
    for p in files():
        if not p.exists():
            continue
        old = p.read_text(encoding="utf-8", errors="replace")
        new = rewrite(old)
        if p.name == "igi2_protos.h" or (p.suffix == ".c" and p.parent.name != "data"):
            for rx, repl in CODE_RULES:
                new = rx.sub(repl, new)
            new = struct_casts(new)
        if new != old:
            p.write_text(new, encoding="utf-8")
            changed += 1
    print(f"rewrite: {changed} files changed")
    apply_patches()
    framed = 0
    for p in (REPO / "src").rglob("*.c"):  # after the patches, which match the decompiler's text
        old = p.read_text(encoding="utf-8", errors="replace")
        new = frame_layout(hash_table_calls(void_results(counter_fields(com_stdcall_casts(fpu_status_bytes(signed_dword_conversions(raw_hash_lookups(self_indexed_copies(old)))))))))
        new = STRAY_FRNDINT.sub("", new)  # the pow() it precedes is only complete by now
        if new != old:
            p.write_text(new, encoding="utf-8")
            framed += new.count("} igi2_frame;") - old.count("} igi2_frame;")
    print(f"frame layout: {framed} functions keep their original stack frame")
    drifted = underscore_drift()
    if drifted:
        print(f"underscore drift: {drifted} names put back")


def underscore_drift():
    """IDA renames a function after the parameter it is passed to, and sanitize adds an underscore
    to a clashing name, so a name can grow by one each run (qr_basic_callback____ is called
    qr_basic_callback________ in gamespy.c by the next one). An identifier the prototypes do not
    declare, that differs from a declared function only in trailing underscores, means it."""
    protos = (REPO / "include" / "igi2_protos.h").read_text(encoding="utf-8", errors="replace")
    declared = set(re.findall(r"\b(\w+)\(", protos))
    by_stem = {}
    for name in declared:
        if name.endswith("_"):
            by_stem.setdefault(name.rstrip("_"), set()).add(name)
    n = 0
    for p in (REPO / "src").rglob("*.c"):
        old = p.read_text(encoding="utf-8", errors="replace")

        def fix(m):
            ident = m.group(0)
            if ident in declared:
                return ident
            match = by_stem.get(ident.rstrip("_"), set())
            return next(iter(match)) if len(match) == 1 else ident
        new = re.sub(r"\b[A-Za-z]\w*?_{2,}\b", fix, old)
        if new != old:
            p.write_text(new, encoding="utf-8")
            n += 1
    return n


if __name__ == "__main__":
    sys.exit(main())
