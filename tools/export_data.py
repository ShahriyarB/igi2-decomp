"""Globals at their original addresses, in a copy of the retail image.

Decompiled code names globals two ways: real names (AppContext_tAppContext) and the decompiler's
address names (dword_704324, unk_6948D4, stru_688D2C), and much code keeps raw addresses: loop
bounds ("while ( (int)p < 7505672 )"), computed elements ("2752 * iProfile + 7392072"), and
constants IDA could not tell from addresses. Rather than separate C objects, which lose aliasing,
array extents and every one of those numbers, the rebuilt exe reserves 0x400000 up to the image
end and the retail sections are copied there, so every global is a macro onto its own address:

    typedef struct AppContext_s igi2_g_AppContext_tAppContext;
    #define AppContext_tAppContext (*(igi2_g_AppContext_tAppContext *)IGI2_ADDR(0x6c07b8))

(one typedef per global: MSVC misparses a parenthesized abstract declarator right after a cast)

At startup data_init.c copies the section bytes in (the image.bin resource) and points stored
function addresses at the rebuilt functions. The exe has no relocation table, so those are found
by value: any aligned dword of loaded data (not code) equal to an exported function's address.

usage: python tools/export_data.py   (system Python with idapro; after the export step)
outputs: include/igi2_globals.h, data/data_init.c, build/image.bin; appends the library
declarations to include/igi2_protos.h
"""
import json
import re
import struct
import subprocess
import time
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parent.parent
IDB = REPO / "work" / "retail" / "igi2_1.0.exe.i64"
EXE = REPO / "work" / "retail" / "igi2_1.0.exe"
t0 = time.time()
if idapro.open_database(str(IDB), run_auto_analysis=False):
    raise SystemExit(f"could not open {IDB}")

import ida_bytes  # noqa: E402
import ida_funcs  # noqa: E402
import ida_nalt  # noqa: E402
import ida_name  # noqa: E402
import ida_typeinf  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

BASE = 0x400000
DUMMY = re.compile(r"^(byte|word|dword|qword|xmmword|tbyte|flt|dbl|unk|off|stru|asc|algn)_([0-9A-F]+)$")
ELEM = {"byte": "_BYTE", "word": "_WORD", "dword": "_DWORD", "qword": "_QWORD", "flt": "float",
        "dbl": "double", "off": "void *", "unk": "_BYTE", "stru": "_BYTE", "asc": "char",
        "xmmword": "_OWORD", "tbyte": "_BYTE", "algn": "_BYTE"}
ARRAYISH = {"unk", "stru", "asc", "algn"}
ELEM_SIZE = {"byte": 1, "word": 2, "dword": 4, "qword": 8, "flt": 4, "dbl": 8, "off": 4, "xmmword": 16,
             "tbyte": 1, "unk": 1, "stru": 1, "asc": 1, "algn": 1}
IDA_BACK = {"enum igi_bool": "enum bool", "igi_false": "false", "igi_true": "true"}


def to_c(text):
    for theirs, ours in IDA_BACK.items():
        text = re.sub(r"\b" + re.escape(theirs) + r"\b", ours, text)
    return text


# ---- the image, straight from the exe's section table ----------------------------------------
pe = EXE.read_bytes()
peo = struct.unpack_from("<I", pe, 0x3C)[0]
nsec = struct.unpack_from("<H", pe, peo + 6)[0]
opt = peo + 24
secs = []
for i in range(nsec):
    name, vsize, va, rsize, roff = struct.unpack_from("<8sIIII", pe, opt + struct.unpack_from("<H", pe, peo + 20)[0] + 40 * i)
    secs.append((name.rstrip(b"\0").decode(), BASE + va, vsize, rsize, roff))
END = max(va + max(vs, rs) for _, va, vs, rs, _ in secs)
END = (END + 0xFFF) & ~0xFFF
image = bytearray(END - BASE)
chunks = [(BASE, 0x1000)]  # headers: some code reads them through the image base
image[:0x1000] = pe[:0x1000]
for name, va, vsize, rsize, roff in secs:
    n = min(vsize, rsize) if vsize else rsize
    image[va - BASE:va - BASE + n] = pe[roff:roff + n]
    chunks.append((va, n))
# the resource holds only the bytes the exe file has; the rest of each section starts as zeros
(REPO / "build" / "image.bin").write_bytes(b"".join(bytes(image[va - BASE:va - BASE + n]) for va, n in chunks))
TEXT = next((va, va + vs) for n, va, vs, _, _ in secs if n == ".text")

status = json.loads((REPO / "build" / "export_status.json").read_text())
functions = {v["ea"]: name for name, v in status.items()}
fstarts = {f for f in idautils.Functions()}

# ---- stored function addresses: loaded bytes only --------------------------------------------
# Data pointers need nothing: the image sits at its original addresses. Function addresses
# stored in data are pointed at the rebuilt functions.
fixups_code = []
for name, va, vsize, rsize, _ in secs:
    n = min(vsize, rsize) if vsize else rsize
    for off in range(0, n - 3, 4):
        ea = va + off
        v = struct.unpack_from("<I", image, ea - BASE)[0]
        if not (TEXT[0] <= v < TEXT[1]) or v not in functions:
            continue  # data, library code, or the middle of a function (jump tables): left as is
        if TEXT[0] <= ea < TEXT[1] and ida_bytes.is_code(ida_bytes.get_flags(ida_bytes.get_item_head(ea))):
            continue  # an instruction, not stored data
        fixups_code.append((ea, functions[v]))

# ---- globals: one macro per name the code uses ----------------------------------------------
text = "\n".join(p.read_text(encoding="utf-8", errors="replace") for p in (REPO / "src").rglob("*.c"))
used = set(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", text))
indexed = set(re.findall(r"([A-Za-z_][A-Za-z0-9_]*)\s*\[", text))
calls_through = set(re.findall(r"(?<![\w.>])([A-Za-z_][A-Za-z0-9_]*)\s*\(", text))
# a unary * (after "(", "=", ",", "return", a pointer cast "T *)", ...; not multiplication
# after an operand)
dereferenced = set(re.findall(r"(?:^|[=(,;!?:{}]|\breturn|\*\))\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\b(?!\s*\()",
                              text, re.M))
assigned = set(re.findall(r"(?<![\w.>])([A-Za-z_][A-Za-z0-9_]*)\s*(?:[-+*/|&^]|<<|>>)?=(?!=)", text))
assigned |= set(re.findall(r"(?:\+\+|--)\s*([A-Za-z_][A-Za-z0-9_]*)\b", text))
assigned |= set(re.findall(r"(?<![\w.>])([A-Za-z_][A-Za-z0-9_]*)\s*(?:\+\+|--)", text))
system_idents = set(json.loads((REPO / "build" / "system_idents.json").read_text()))
typedefs, macros, reindex = [], [], set()
scoped = set(json.loads((REPO / "build" / "scoped_names.json").read_text()))
for lv in (REPO / "build" / "export").glob("lvars_*.json"):
    scoped |= set(json.loads(lv.read_text()))  # locals and parameters are never globals
for ident in sorted(used):
    if ident in system_idents or ident in scoped:
        continue  # members/enumerators: globals sharing those names were renamed g_ by sanitize
    dummy = DUMMY.match(ident)
    ea = ida_name.get_name_ea(idc.BADADDR, ident)
    if ea == idc.BADADDR:
        ea = ida_name.get_name_ea(idc.BADADDR, "_" + ident)  # the decompiler drops one underscore
    if ea == idc.BADADDR and dummy:
        ea = int(dummy.group(2), 16)
    label = re.fullmatch(r"loc_([0-9A-F]+)", ident)
    if label and ida_name.get_name_ea(idc.BADADDR, ident) == idc.BADADDR:
        # bytes inside code the decompiler read as data ("&loc_656460 + 1"): the image has them
        macros.append(f"#define {ident} (*(char *)IGI2_ADDR({int(label.group(1), 16):#x}))")
        continue
    if ea == idc.BADADDR or not (BASE <= ea < END) or ea in fstarts:
        continue
    if TEXT[0] <= ea < TEXT[1] and ida_bytes.is_code(ida_bytes.get_flags(ea)):
        continue  # a code label, not data
    tname = f"igi2_g_{ident}"
    tif = ida_typeinf.tinfo_t()
    decl = None
    if ida_nalt.get_tinfo(tif, ea) and not tif.empty() and not tif.is_func():  # data cannot be a function
        decl = to_c(ida_typeinf.print_tinfo("", 0, 0, ida_typeinf.PRTYPE_1LINE, tif, tname, ""))
        if decl.startswith("const ") and "*" not in decl:
            decl = decl[len("const "):]  # the program writes to it; the original's const was advisory
        if ident in dereferenced and tif.is_integral() and tif.get_size() == 4:
            # a dword some decompile typed as an integer while the code reads through it
            # ("*dword_74C648"): the function that dereferences it saw a pointer
            decl = f"_DWORD *{tname}"
        elif ident in indexed and "[" not in decl and "*" not in decl:
            reindex.add(ident)  # a typed scalar the code also indexes
    if not decl:
        # the decompiler's own guess: where it is an array ("char *[3]"), the bare name it prints
        # is the address (mov esi, offset off_6B9678), and only an array type says so in C
        guess = ida_typeinf.tinfo_t()
        if ida_typeinf.guess_tinfo(guess, ea) and guess.is_array() and guess.get_size() > 0:
            decl = to_c(ida_typeinf.print_tinfo("", 0, 0, ida_typeinf.PRTYPE_1LINE, guess, tname, ""))
    if not decl:
        kind = dummy.group(1) if dummy else None
        if not kind:
            fl = ida_bytes.get_flags(ea)
            kind = "asc" if ida_bytes.is_strlit(fl) else \
                {1: "byte", 2: "word", 4: "dword", 8: "qword"}.get(ida_bytes.get_item_size(ea), "unk")
        elem = ELEM[kind]
        if kind in ARRAYISH and ident in assigned:
            kind, elem = "dword", "_DWORD"  # an unknown blob the code stores a value into
        if kind == "dword" and ident in calls_through:
            decl = f"int (__cdecl *{tname})()"  # the code calls through it: a function pointer
        elif kind == "dword" and ident in dereferenced:
            decl = f"_DWORD *{tname}"  # the code dereferences it: a pointer
        # Byte-ish blobs, and arrays the code indexes but never stores into as a whole, are
        # arrays (they decay to pointers). Anything else is a scalar lvalue; where the code also
        # indexes it, "x[i]" becomes "(&x)[i]" (reindex below).
        elif kind not in ARRAYISH and ida_bytes.get_item_size(ea) // ELEM_SIZE[kind] > 1:
            # an array IDA made of the item (off_6B9678: three string pointers): its bare name
            # in decompiled code is its address, as an array's is in C
            decl = f"{elem} {tname}[{ida_bytes.get_item_size(ea) // ELEM_SIZE[kind]}]"
        elif kind in ARRAYISH or (ident in indexed and ident not in assigned):
            decl = f"{elem} {tname}[1]"
        else:
            decl = f"{elem} {tname}"
            if ident in indexed:
                reindex.add(ident)
    typedefs.append(f"typedef {decl};")
    macros.append(f"#define {ident} (*({tname} *)IGI2_ADDR({ea:#x}))")

if reindex:
    rx = re.compile(r"(?<![\w.>])(" + "|".join(map(re.escape, sorted(reindex, key=len, reverse=True))) + r")\s*\[")
    for src in (REPO / "src").rglob("*.c"):
        old = src.read_text(encoding="utf-8", errors="replace")
        new = rx.sub(lambda m: f"(&{m.group(1)})[", old)
        if new != old:
            src.write_text(new, encoding="utf-8")

hdr = ["/* Generated by tools/export_data.py -- do not edit.",
       "   Globals live at their retail addresses: data/data_init.c reserves 0x400000 up to",
       "   IGI2_IMAGE_END in this exe and copies the retail sections there. */",
       "#pragma once", '#include "igi2_types.h"', "",
       f"#define IGI2_IMAGE_BASE {BASE:#x}u", f"#define IGI2_IMAGE_END {END:#x}u",
       "#define IGI2_ADDR(va) ((void *)(va))",
       "#define IGI2_VA(va) ((unsigned int)(va))", ""]
(REPO / "include" / "igi2_globals.h").write_text("\n".join(hdr + typedefs + [""] + macros) + "\n")

total = sum(n for _, n in chunks)
lines = [
    "/* Generated by tools/export_data.py -- do not edit.",
    "   Puts the retail image at its original addresses, 0x400000 up to IGI2_IMAGE_END.",
    "",
    "   The exe is based at 0x10000 (CMakeLists.txt), so its code ends below 0x400000; the",
    "   uninitialized section .igi2 that follows it is large enough to run past IGI2_IMAGE_END.",
    "   It takes no room in the file, and the loader maps it before anything else could claim",
    "   those addresses. Every global, every raw address and every pointer comparison in the",
    "   decompiled code then means what it meant in the original. */",
    '#include "igi2.h"', "",
    '#pragma bss_seg(".igi2")',
    "static unsigned char Igi2_aRegion[IGI2_IMAGE_END];",
    "#pragma bss_seg()", "",
    "/* the exe's bytes of each section, in the IGI2IMAGE resource back to back */",
    "typedef struct { unsigned int va, size; } ImageChunk;",
    "static const ImageChunk kChunks[] = {",
    *[f"    {{ {va:#x}, {n:#x} }}," for va, n in chunks], "    { 0, 0 }", "};", "",
    "typedef struct { unsigned int va; void *target; } CodePointer;",
    "static const CodePointer kCodePointers[] = {",
    *[f"    {{ {ea:#x}, (void *){name} }}," for ea, name in fixups_code], "    { 0, 0 }", "};", "",
    "static void Igi2_Fail(const char *zMessage)", "{",
    "    MessageBoxA(NULL, zMessage, \"IGI 2\", MB_ICONERROR);",
    "    ExitProcess(1);", "}", "",
    "static void __cdecl Igi2_InitImage(void)", "{",
    "    if ((unsigned int)Igi2_aRegion > IGI2_IMAGE_BASE)",
    "        Igi2_Fail(\"The code has grown past 0x400000: lower the base address in CMakeLists.txt.\");",
    "    HRSRC res = FindResourceA(NULL, \"IGI2IMAGE\", (LPCSTR)RT_RCDATA);",
    "    const unsigned char *bytes = res ? LockResource(LoadResource(NULL, res)) : NULL;",
    f"    if (!bytes || SizeofResource(NULL, res) != {total:#x}u)",
    "        Igi2_Fail(\"The game image resource is missing.\");",
    "    for (const ImageChunk *c = kChunks; c->size; bytes += c->size, ++c)",
    "        memcpy(IGI2_ADDR(c->va), bytes, c->size);",
    "    for (const CodePointer *c = kCodePointers; c->va; ++c)",
    "        *(void **)IGI2_ADDR(c->va) = c->target;", "}", "",
    "/* run before main: a C initializer in the CRT's user-initializer section */",
    '#pragma section(".CRT$XCU", read)',
    '__declspec(allocate(".CRT$XCU")) static void (__cdecl *const kInitImage)(void) = Igi2_InitImage;',
]
(REPO / "data").mkdir(exist_ok=True)
for old in (REPO / "data").glob("*.c"):
    old.unlink()
(REPO / "data" / "data_init.c").write_text("\n".join(lines) + "\n")

# ---- library functions the code calls: declared without a parameter list ---------------------
protos_path = REPO / "include" / "igi2_protos.h"
protos_text = protos_path.read_text()
LIB_MARK = "\n/* called library code"
protos_text = protos_text.split(LIB_MARK)[0].rstrip("\n") + "\n"  # the previous run's section goes
declared = set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", protos_text))
for hand_written in ("mss_api.h", "support.h"):
    declared |= set(re.findall(r"\b(\w+)\s*\(", (REPO / "include" / hand_written).read_text()))
lib = ["", "/* called library code: unprototyped, so each call site's argument count is accepted */"]
exported_names = set(functions.values())
# CRT internals today's runtime does not export: the public function they implement
CRT_ALIASES = {"_floor_pentium4": "floor", "_floor_default": "floor"}
for ident in sorted(used):  # called, or only taken as a function pointer
    if ident in declared or ident in system_idents or ident in exported_names:
        continue  # exported functions are declared by export.py
    ea = ida_name.get_name_ea(idc.BADADDR, ident)
    if ea == idc.BADADDR:  # the decompiler prints a C name without its underscore: _scprintf
        ea = ida_name.get_name_ea(idc.BADADDR, "_" + ident)
        if ea != idc.BADADDR and "_" + ident in system_idents:  # also imports: __WSAFDIsSet
            lib.append(f"#define {ident} _{ident}")
            continue
    if ea == idc.BADADDR or ea not in fstarts or ea in functions:
        continue
    # the C runtime under its real name: "exit__crt0dat" is exit (from crt0dat.obj), made unique
    real = re.sub(r"__\w+$", "", ida_name.get_name(ea)) or ida_name.get_name(ea)
    real = CRT_ALIASES.get(real, real)
    if real in system_idents:  # the system headers declare it under its real name
        if real != ident:
            lib.append(f"#define {ident} {real}")
        continue
    decl = ida_typeinf.print_type(ea, ida_typeinf.PRTYPE_1LINE) or f"int {ident}()"
    decl = re.sub(r"@<[^>]+>", "", to_c(decl))
    i = decl.find(f"{ident}(")
    decl = (decl[:i] if i >= 0 else "int ") + f"{ident}();"
    lib.append(re.sub(r"\b__(?:usercall|userpurge|thiscall|fastcall)\b", "__cdecl", decl))
protos_path.write_text(protos_text + "\n".join(lib) + "\n")

print(f"global macros {len(macros)}, image {len(image):#x} bytes ({total:#x} loaded), "
      f"code pointers {len(fixups_code)}, library declarations {len(lib) - 2}; {time.time() - t0:.0f}s")
idapro.close_database(save=False)
subprocess.run(["uv", "run", "-q", "rewrite.py"], cwd=str(REPO / "tools"), check=True)
