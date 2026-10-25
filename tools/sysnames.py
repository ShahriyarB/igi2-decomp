"""Names (tags, typedefs, macros) already provided by include/decomp_system.h."""
import re

import msvc
from config import REPO

_TAG = re.compile(r"\b(?:struct|union|enum)\s+(?:__declspec\([^)]*\)\s*)?(\w+)")
_DEFINE = re.compile(r"^\s*#\s*define\s+(\w+)", re.M)
_IDENT_END = re.compile(r"(\w+)\s*(?:\[[^\]]*\]\s*)*$")
_FNPTR = re.compile(r"\(\s*(?:__\w+\s+|WINAPI\s+|CALLBACK\s+)*\*\s*(\w+)\s*\)")


def _typedef_names(stmt):
    """Declarator names of one `typedef ...;` statement."""
    body = stmt[len("typedef"):].rstrip(";")
    if "}" in body:
        body = body[body.rindex("}") + 1:]
    names = set(_FNPTR.findall(body))
    depth, part, parts = 0, [], []
    for ch in body:
        depth += ch in "([" and 1 or 0
        depth -= ch in ")]" and 1 or 0
        if ch == "," and depth == 0:
            parts.append("".join(part))
            part = []
        else:
            part.append(ch)
    parts.append("".join(part))
    for p in parts:
        p = re.sub(r"\([^()]*\)\s*$", "", p.strip())  # function typedef parameter list
        m = _IDENT_END.search(p.strip())
        if m:
            names.add(m.group(1))
    return names


def system_names():
    probe = REPO / "build" / "sysprobe.c"
    probe.parent.mkdir(parents=True, exist_ok=True)
    probe.write_text('#include "decomp_system.h"\n')
    r = msvc.run(["cl", "/nologo", "/E", "/d1PP", "/TC", f"/I{REPO / 'include'}", str(probe)])
    if r.returncode:
        raise RuntimeError(r.stderr[-2000:])
    text = r.stdout
    macros = set(_DEFINE.findall(text))
    code = re.sub(r"^\s*#.*$", "", text, flags=re.M)
    tags = set(_TAG.findall(code))
    typedefs = set()
    # split top-level statements on ';' while tracking brace depth
    depth, start = 0, 0
    for i, ch in enumerate(code):
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
        elif ch == ";" and depth == 0:
            stmt = " ".join(code[start:i + 1].split())
            start = i + 1
            if stmt.startswith("typedef "):
                typedefs |= _typedef_names(stmt)
    idents = set(re.findall(r"\b[A-Za-z_]\w*\b", code)) | macros
    return {"tags": tags, "typedefs": typedefs, "macros": macros, "idents": idents,
            "prototypes": _prototypes(code)}


_PROTO_NAME = re.compile(r"\b(__cdecl|__stdcall)\s+([A-Za-z_]\w*)\s*\(")


def _prototypes(code):
    """name -> plain declaration of every function the system headers declare (not define)."""
    out = {}
    depth, start = 0, 0
    for i, ch in enumerate(code):
        if ch == "{":
            if depth == 0:
                # an inline definition (today's CRT defines sprintf & co. inline): its header
                head = " ".join(code[start:i].split())
                m = _PROTO_NAME.search(head)
                if m and head.endswith(")") and not head.startswith(("typedef", "struct", "union", "enum")):
                    head = re.sub(r"__declspec\((?:[^()]|\([^()]*\))*\)\s*", "", head)
                    head = re.sub(r"^\s*(?:extern\s+|static\s+|__inline\s+|inline\s+)+", "", head)
                    out.setdefault(m.group(2), head)
            depth += 1
            start = i + 1 if depth == 1 else start
        elif ch == "}":
            depth -= 1
            start = i + 1
        elif ch == ";" and depth == 0:
            stmt = " ".join(code[start:i].split())
            start = i + 1
            m = _PROTO_NAME.search(stmt)
            if not m or stmt.startswith("typedef") or "(*" in stmt[:m.start()]:
                continue
            stmt = re.sub(r"__declspec\((?:[^()]|\([^()]*\))*\)\s*", "", stmt)
            stmt = re.sub(r"^\s*(?:extern\s+\"C\"\s*|extern\s+|static\s+|__inline\s+|inline\s+)+", "", stmt)
            out.setdefault(m.group(2), stmt)
    # Inline definitions found directly: brace counting over 10 MB of preprocessed headers can
    # drift (a brace in a literal), and the C runtime defines sprintf & co. this way.
    for m in _INLINE_DEF.finditer(code):
        head = " ".join(m.group(1).split())
        head = re.sub(r"^(?:__inline\s+|static\s+|inline\s+)+", "", head)
        out.setdefault(m.group(2), head)
    return out


_INLINE_DEF = re.compile(
    r"(?:^|[;}])\s*((?:__inline\s+|static\s+)+[A-Za-z_][\w\s\*]*?\b(?:__cdecl|__stdcall)\s+(\w+)\s*"
    r"\((?:[^;{}()]|\([^;{}()]*\))*\))\s*\{")


def system_sizes(tags):
    """sizeof for system tags, measured by compiling and running a probe (kind: struct/union)."""
    probe = REPO / "build" / "syssize.c"
    body = "\n".join(f'    printf("%s %u\\n", "{tag}", (unsigned)sizeof({kind} {tag}));'
                     for tag, kind in sorted(tags.items()))
    probe.write_text('#include "decomp_system.h"\n#include <stdio.h>\nint main(void) {\n'
                     + body + "\n    return 0;\n}\n")
    exe = REPO / "build" / "syssize.exe"
    r = msvc.run(["cl", "/nologo", "/TC", "/w", f"/I{REPO / 'include'}", f"/Fe{exe}",
                  f"/Fo{REPO / 'build' / 'syssize.obj'}", str(probe)])
    if r.returncode:
        # incomplete types (declared but never defined) cannot be measured: drop them and retry
        bad = set(re.findall(r"undefined (?:struct|union) '(\w+)'", r.stdout))
        if not bad:
            raise RuntimeError(r.stdout[-3000:])
        return system_sizes({t: k for t, k in tags.items() if t not in bad})
    out = msvc.run([str(exe)]).stdout
    return {line.split()[0]: int(line.split()[1]) for line in out.splitlines() if line.strip()}


if __name__ == "__main__":
    n = system_names()
    print({k: len(v) for k, v in n.items()})
    for probe in ("tagWNDCLASSA", "HWND__", "_GUID", "DIDEVICEOBJECTDATA", "WNDCLASSA", "HWND",
                  "LPDIRECTINPUT8A", "TRUE", "_D3DMATRIX", "IDirectSound"):
        print(probe, [k for k, v in n.items() if probe in v])
