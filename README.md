# igi2-decomp

A C reconstruction of the *IGI 2: Covert Strike* client (`igi2_1.0.exe`), generated from the retail
executable with IDA and the build PDBs, and built with MSVC for 32-bit Windows.

Nothing from the original game is in this repository: no executables, DLLs, PDBs, IDA databases or
image dumps. The tools read those from your own copy.

## Layout

| folder | contents |
| --- | --- |
| `src/` | the decompiled game, laid out like the original source tree (generated: do not edit) |
| `data/` | globals at their retail addresses and the retail fallback's tables (generated) |
| `include/` | hand-written headers; `include/generated/` holds the types, prototypes and globals |
| `overrides/` | hand fixes: per-function `.c` files, `ida_types.json`, `patches.json`, `match_reject.json` |
| `runtime/` | hand-written C the exe needs: retail fallback, replay, guard heap, FPU setup, library stand-ins |
| `res/` | the resource script that embeds the retail image |
| `tools/pipeline/` | the scripts that make `src/`, `data/` and `include/generated/` |
| `tools/debug/` | running, replaying, bisecting and inspecting |
| `docs/` | [how it is made](docs/pipeline.md) |

## Setup

1. Copy `config.example.json` to `config.local.json` and fill in the paths (retail exe, PDBs/maps,
   IDA, Visual Studio, DirectX 8.1 SDK).
2. `cd tools && uv sync`

## Pipeline

From `tools/`:

- `uv run pipeline/rebuild_functions.py`: rebuild the function set and the matches
- `uv run pipeline/pipeline.py [types|apply|export|data|census ...]`: everything downstream of it
- `uv run debug/run.py SECS`: run the build under cdb (log in `build/run.log`)
- `uv run debug/replay_bisect.py check|diff|bisect|fix`: deterministic replay against the retail fallback

## Build

```
cmake -B build/cmake -A Win32
cmake --build build/cmake --config Release
```

The exe is `build/cmake/Release/igi2.exe`. `build/image.bin`, written by
`tools/pipeline/export_data.py`, is embedded as a resource. Configuring also writes `.clangd` for
the IDE.

## Thanks

- The [Neonix Modding Team](https://discord.gg/GdXMbbVUcE). The IGI 2 PDBs and map files that
  this project's symbols come from were published in their IGI-NeonixResearch repository, along with their
  research on the game.
