# How the reconstruction is made

The C in `src/` is not written by hand. It is generated from the retail executable
(`igi2_1.0.exe`, no SafeDisc) by IDA's decompiler, steered by the symbols in the original build PDBs,
then rewritten by text rules until MSVC compiles it and the result behaves like the original.
Hand-written fixes live in `overrides/` so regenerating never loses them.

## Inputs

| config key | what it is |
| --- | --- |
| `retail_exe` | the retail client, the code that gets decompiled |
| `final_pdb`, `final_map` | the client's *Final* build (2003-01-06), retail configuration: names, types, source layout |
| `client_pdb`, `client_map` | a Release build with debug parameters and fields: a fallback only |
| `ds12_exe`, `ds12_pdb`, `ds12_map` | Dedicated Server 1.2: an exe with its own PDB, used to check function matching |
| `game_dir` | the installed game, where the rebuilt exe runs |
| `ida_dir`, `vs_dir`, `dx8_sdk` | IDA (idalib), Visual Studio, the DirectX 8.1 SDK |

All of them go in `config.local.json` (see `config.example.json`). The IDA steps run under a system
Python that has the `idapro` package; the rest run in the uv environment of `tools/`.

## Steps

`tools/pipeline/rebuild_functions.py` builds the function set once (and again when matching
improves): it creates the functions IDA missed where the Final PDB predicts them, fingerprints every
function and matches PDB functions to retail addresses (`symbols/match.json`).

`tools/pipeline/pipeline.py` then rebuilds everything downstream of those boundaries:

1. **types**: `gen_types.py` turns the Final PDB's types into `include/generated/igi2_types.h`.
2. **apply**: `ida_apply.py` puts names, types, globals and calling conventions onto a fresh copy
   of the functions-only IDB. Skipped when none of its inputs changed.
3. **export**: `export.py` decompiles every function into `src/<original path>.c`, laid out like
   Innerloop's source tree (`b/1/appmain.c`, `j/0/weapons/gun.c`, ...), in parallel shards. Two
   more rounds let the decompiled signatures settle so call sites agree with definitions.
4. **data**: `export_data.py` writes the globals (`include/generated/igi2_globals.h`,
   `data/data_init.c`, `build/image.bin`) and runs `rewrite.py`; `ida_fallback.py` writes the
   retail fallback's tables (`data/fallback_*.c`).
5. **census**: `census.py` compiles all of `src/` and buckets the errors, so a fix goes to the rule
   that clears the most.

## How the exe works

- **The retail image at its own addresses.** The exe is linked at `/BASE:0x10000 /FIXED`; an
  uninitialized section covers 0x400000 and up, and `data/data_init.c` copies the retail sections
  there at startup. Globals are macros onto that copy, so raw addresses, loop bounds and pointer
  comparisons in the decompiled code keep their retail values; only code pointers are fixed up.
  The exe's own code must stay below 0x400000.
- **Retail fallback** (`runtime/fallback.c`, `IGI2_FALLBACK=<functions>`): chosen functions run as
  the original machine code, the rest as our C. `IGI2_FALLBACK=all` is the retail baseline.
- **Replay** (`runtime/replay.c`, `IGI2_REPLAY`): a script drives the game one tick per frame,
  deterministically, and logs the player every frame. `runtime/replay_host.c` lets it run unattended
  in the background with audio muted.
- **Guard heap** (`-DIGI2_GUARD_HEAP=ON`): every allocation ends at an inaccessible page.

## Finding a bug

- `tools/debug/run.py SECS`: run under cdb; a crash prints the event, registers and stack.
- `tools/debug/replay_bisect.py check|diff|bisect|fix`: compare a replay against the retail
  baseline and halve the set of C functions until the one that differs is left.
- `tools/debug/replay_fields.py`: compare the whole player struct frame by frame, to name the
  field (and so the code) that first differs.
- `tools/debug/ida_decompile.py`, `ida_disasm.py`: look at one function; `override_start.py` copies
  its decompiled text into `overrides/` to start a hand fix.

## Traps found on the way

Each of these is handled by a rule in the tools; they are the reason most rules exist.

- **LTCG register arguments.** The retail build used whole-program optimization, so many functions
  take arguments in registers the PDB does not mention. `ida_abi.py` records what the decompiler
  deduces, and the export adds extra register and trailing stack arguments the PDB leaves out.
- **x87 floating point.** Floats return in `st0`; `sqrt`/`sin`/`cos`/`tan`/`atan2` are inline
  instructions (the original never calls the CRT for them); float constants are printed as exact
  bits; the FPU status byte after compares needs its own rule. The exe builds with `/arch:IA32`.
- **Constants that look like addresses.** IDA takes constants in the retail BSS range for
  addresses; the export puts them back as numbers.
- **16-byte alignment.** Every game function starts on a 16-byte boundary; an unaligned "function"
  is junk or CRT code.
- **COM calls** must be cast `__stdcall`, or the stack is off by the arguments after every call.
- **Stack purges.** Where IDA balances the stack wrongly after a call, the callee gets its real type
  and the function is reanalyzed, or explicit stack points are set.
- **Stale IDBs.** A killed export leaves its database unpacked, and IDA then opens that instead of
  the fresh copy; the pipeline deletes the shard folder before each export.
- **Decompiler output MSVC misreads**, such as `(T)(*(X (*)[1])...)`, inlined `strcpy` that loses
  `- src`, unsigned division by negative constants and signed `_DWORD` operations: each has a
  rewrite rule in `rewrite.py`.
- **Size-only matches can be wrong**: `overrides/match_reject.json` rejects them, and
  address-keyed entries in `overrides/ida_types.json` pin the right types.
