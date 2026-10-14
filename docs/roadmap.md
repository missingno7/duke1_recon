# Roadmap: from matched functions to a standalone source tree

## Target state

A readable source tree that compiles and links **standalone**, with the pinned
historical toolchain and nothing else, into byte-identical DN1.EXE, DN2.EXE and
DN3.EXE:

```
duke1/                      (final layout, names indicative)
  BUILD.BAT                 tcc / tasm / tlink / lzexe, once per episode
  duke.h                    struct types, extern globals, prototypes (semantic names)
  game1.c                   translation unit 1 (original G1), original function and data order
  game2.c                   translation unit 2 (original G2: menus, text, sound, data tables)
  toolbox.asm               ProGraphx EGA/VGA Toolbox routines (TASM 1.0)
  (C0.ASM and CL.LIB come from the Turbo C 2.0 installation)
```

`BUILD.BAT` per episode: `tcc -c -ml -Z -G -O -1- -f- -K -DEPISODE=n game1.c game2.c`,
`tasm /MX toolbox.asm`, `tasm /D__LARGE__ /MX C0.ASM`,
`tlink /c /d /s c0 toolbox game1 game2, dnN.exe,, cl.lib`, `lzexe dnN.exe`.
A host script runs it under MS-DOS Player and compares the SHA-256 of the three
outputs with `layout/oracle.lock.json`.

## Phases

1. **Reconstruction** (done, 2026-10-14): every function proven; G1/G2 initialised data
   and BSS reproduced (`tools/tubuild.py --data`); the natural link
   (`tools/link.py`) equal to the unpacked oracle images; LZEXE 0.91 repack equal to
   the original files (rule REPACK-REPRODUCIBLE).
2. **The link becomes the proof** (done: `layout/link.json`): `tools/validate.py` runs the full link and the
   repack for all three episodes; any change that moves one byte fails.  From here
   on, refactoring is safe and mechanical to check.
3. **Readability pass** on `game/` (no change in emitted code, verified by the standalone
   build on every step):
   * done 2026-10-14: one shared header (`DUKE.H`) and one file per original unit;
     formatting, natural constants and comments by function range (six workers, merged
     three-way); semantic names for all functions, globals, structures and fields
     (`layout/game-names.json`, applied by `tools/rename.py`, which also re-aligns
     continuation lines and writes one-line descriptions).  Uninitialised globals keep
     hash-neutral storage names `d_XXXX_` behind `#define` names, since Turbo C orders a
     unit's `_BSS` by a hash of the name (rule BSS-ORDER);
   * done 2026-10-14: parameter and local names (six workers, maps in
     `layout/game-names.json` "params"); demo buffers typed `char far *`;
   * open: low-confidence names (`update_actor_30XX` once each actor is identified, see
     the confidence column in `build/workers/luna-names2/names.json`), subsystem section
     comments, and the matching-era forms that were tried and must stay (documented
     `goto`s in ten functions, shift chains in the sound bank loaders, the flat
     `ACTOR_TILE_OFFSETS` view, the out-of-record store in `actor_3021_records`, far
     pointer additions on video memory): each carries a comment saying why.
4. **Standalone tree** (generated and proven 2026-10-14: `game/`, `python tools/standalone.py build`,
   re-run by `tools/validate.py`): `BUILD.BAT` + host check script.  `game/` is now the source
   that is edited; `src/` + `recipes/` stay frozen as the per-function matching record.
5. **SDL3 port** on top of the standalone tree (see `docs/porting-notes.md`): a platform
   seam that keeps the DOS build identical.

Constraints that hold throughout: no original bytes injected, no post-link
patching, no masking; original binaries and assets are never committed.
