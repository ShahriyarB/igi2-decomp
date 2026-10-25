"""Import libraries for DLLs the game ships but no SDK provides (Miles Sound System: mss32.dll).

mss32.dll exports its stdcall functions under their decorated names (_AIL_startup@0). An import
library made from a .def file imports the name it is given minus that underscore, which the DLL
does not have; one made by linking a stub DLL with the same exports imports them exactly as the
real DLL names them. So this writes a stub with one empty function per export (argument bytes
from the decoration), links it, and keeps only its import library.

usage: uv run make_importlibs.py   -> third_party/lib/mss32.lib
"""
import re
import tempfile
from pathlib import Path

import msvc
from config import REPO, load_config


def main():
    game = load_config()["game_dir"]
    out = REPO / "third_party" / "lib"
    out.mkdir(parents=True, exist_ok=True)
    for dll in ("mss32",):
        r = msvc.run(["dumpbin", "/nologo", "/exports", f"{game}/{dll}.dll"])
        names = re.findall(r"^\s+\d+\s+[0-9A-F]+\s+[0-9A-F]{8}\s+(\S+)", r.stdout, re.M)
        stub = [f"/* stub of {dll}.dll: same export names, empty bodies */"]
        for n in names:
            m = re.fullmatch(r"_(\w+)@(\d+)", n)
            if m:  # stdcall: the compiler decorates the stub's export the same way
                params = ", ".join(f"int a{k}" for k in range(int(m.group(2)) // 4)) or "void"
                stub.append(f"__declspec(dllexport) int __stdcall {m.group(1)}({params}) {{ return 0; }}")
            elif re.fullmatch(r"[A-Za-z]\w*", n):  # cdecl: exported undecorated
                stub.append(f"__declspec(dllexport) int __cdecl {n}(void) {{ return 0; }}")
        with tempfile.TemporaryDirectory() as tmp:
            src = Path(tmp) / f"{dll}_stub.c"
            src.write_text("\n".join(stub) + "\n")
            r = msvc.run(["cl", "/nologo", "/LD", "/O1", str(src), "/link", "/NOENTRY", "/NODEFAULTLIB",
                          f"/OUT:{Path(tmp) / (dll + '.dll')}", f"/IMPLIB:{out / (dll + '.lib')}"], cwd=tmp)
            if r.returncode:
                raise SystemExit(r.stdout[-2000:])
        print(f"{dll}: {len(names)} exports -> {dll}.lib")
        check_api(names)


def check_api(exports):
    """include/mss_api.h: every declared function's parameters add up to its export's byte count."""
    nbytes = {m.group(1): int(m.group(2)) for m in map(re.compile(r"^_(\w+)@(\d+)$").match, exports) if m}
    header = (REPO / "include" / "mss_api.h").read_text()
    bad = 0
    for name, params in re.findall(r"__stdcall (AIL_\w+)\(([^)]*)\);", header):
        count = 0 if params.strip() == "void" else params.count(",") + 1
        if nbytes.get(name) != 4 * count:
            print(f"  mss_api.h: {name} takes {4 * count} bytes, the DLL export {nbytes.get(name)}")
            bad += 1
    print(f"mss_api.h: {'all declarations agree with the DLL' if not bad else f'{bad} mismatches'}")


if __name__ == "__main__":
    main()
