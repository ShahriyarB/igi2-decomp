# igi2-decomp

A C reconstruction of the *IGI 2: Covert Strike* client (`igi2_1.0.exe`), generated from the retail
executable with IDA and the build PDBs, and built with MSVC for 32-bit Windows.

Nothing from the original game is in this repository: no executables, DLLs, PDBs, IDA databases or
image dumps. The tools read those from your own copy.

## Setup

1. Copy `config.example.json` to `config.local.json` and fill in the paths (retail exe, PDBs/maps,
   IDA, Visual Studio, DirectX 8.1 SDK).
2. `cd tools && uv sync`

## Pipeline

- `cd tools && uv run pipeline.py`: the full run (symbols, IDA apply, export, census)
- `uv run rebuild_functions.py`: rebuild the function set
- `uv run run.py SECS`: run the build under cdb (log in `build/run.log`)
- `uv run replay_bisect.py check|diff|bisect|fix`: deterministic replay against the retail fallback

Hand-made fixes live in `overrides/` (per-function `.c` files, `ida_types.json`, `patches.json`,
`match_reject.json`). The emitted code is in `src/`, `data/` and `include/`.

## Build

CMake with MSVC, x86, Release (`build/cmake/Release/igi2.exe`). `build/image.bin`, written by
`tools/export_data.py`, is embedded as a resource.
