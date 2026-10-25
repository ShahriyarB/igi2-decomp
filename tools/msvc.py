"""Run MSVC x86 tools (cl, link, lib) with the vcvars32 environment captured once."""
import json
import os
import shutil
import subprocess

from config import REPO, load_config

_CACHE = REPO / "build" / "msvc_env.json"


def _vcvars():
    root = load_config().get("vs_dir", r"D:\.files\.vs\2026")
    return os.path.join(root, "VC", "Auxiliary", "Build", "vcvars32.bat")


def environment():
    if _CACHE.exists():
        return json.loads(_CACHE.read_text())
    out = subprocess.run(f'cmd /s /c ""{_vcvars()}" >nul && set"', capture_output=True, text=True,
                         shell=True, check=True).stdout
    env = dict(line.split("=", 1) for line in out.splitlines() if "=" in line)
    _CACHE.parent.mkdir(parents=True, exist_ok=True)
    _CACHE.write_text(json.dumps(env))
    return env


def run(args, cwd=None, check=False):
    """Run an MSVC tool; returns CompletedProcess with text output."""
    env = environment()
    path = next(v for k, v in env.items() if k.lower() == "path")
    # CreateProcess searches the parent's PATH, not the child environment's
    exe = shutil.which(args[0], path=path) or args[0]
    return subprocess.run([exe, *args[1:]], env=env, cwd=cwd, capture_output=True, text=True,
                          errors="replace", check=check)
