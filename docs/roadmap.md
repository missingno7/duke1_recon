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

1. **Reconstruction** (in progress): every function proven; G1/G2 initialised data
   and BSS reproduced (`tools/tubuild.py --data`); the natural link
   (`tools/link.py`) equal to the unpacked oracle images; LZEXE 0.91 repack equal to
   the original files (rule REPACK-REPRODUCIBLE).
2. **The link becomes the proof**: `tools/validate.py` runs the full link and the
   repack for all three episodes; any change that moves one byte fails.  From here
   on, refactoring is safe and mechanical to check.
3. **Readability pass** (no change in emitted code, verified by phase 2 on every step):
   * semantic names through `layout/symbols.json` aliases (proposals with evidence
     from `build/workers/luna-names/`, reviewed by the supervisor);
   * one shared header replacing the per-function preludes and stubs (an artifact
     of proving one function at a time);
   * one source file per original translation unit, original order kept (Turbo C's
     code, literal-pool, data and BSS layout depend on it), with subsystem sections
     and comments; consistent formatting;
   * idioms that only exist to reproduce the original made explicit and named
     (e.g. the out-of-record store `(&d_726b[i].x)[2]`, label loops kept for
     register allocation, `goto kept:` notes).
4. **Standalone tree**: `BUILD.BAT` + host check script; the per-function sources and
   recipes become matching history, not the canonical source.
5. **SDL3 port** on top of the standalone tree (see `docs/porting-notes.md`): a platform
   seam that keeps the DOS build identical.

Constraints that hold throughout: no original bytes injected, no post-link
patching, no masking; original binaries and assets are never committed.
