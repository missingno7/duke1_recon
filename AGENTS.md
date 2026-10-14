# Working in this repository

`src/` is the game and the only copy of it.  `port/` runs it on SDL3.  Read `README.md`
first; `docs/turbo-c.md` before changing code in `src/`.

## Rules

1. **`src/` stays the original program.**  After any change to `src/`, `python
   tools/build.py` must print EQUAL for dn1, dn2 and dn3.  Use `tools/rename.py` for
   renames (it keeps uninitialised globals on their hash-neutral storage names).  No inline
   assembly, no byte emission, nothing that manufactures equality.
2. **Port behaviour goes into `port/`** (platform code, `port/override/`,
   `tools/port_gen.py`), never into `src/`.  Fix a port difference where the DOS semantics
   live (see `docs/sdl3-port.md`, "DOS semantics the port must reproduce").
3. **The game files are not ours.**  `assets/` (the original executables, graphics,
   levels, the user's settings and saves) is ignored by git; never commit, copy into
   tracked paths, or redistribute any of it or anything derived from it (unpacked images,
   rendered sprites, captures).  Work on copies under `build/`.
4. **`src/` files keep CRLF line endings** (Turbo C 2.0 needs them); `.gitattributes`
   stops git from rewriting them.
5. Before committing: `python tools/validate.py` (originals present, DOS build EQUAL, port
   builds, EGA self-test passes).

## Tools

| Tool | Purpose |
|---|---|
| `tools/build.py` | build DN1/DN2/DN3.EXE from `src/` and compare with the originals |
| `tools/validate.py` | everything that must hold before a commit |
| `tools/oracle.py` | check the original executables in `assets/` against `config/oracle.lock.json` |
| `tools/rename.py` | rename functions, globals, structs, fields, parameters; replace descriptions |
| `tools/port_gen.py` | translate `src/` per episode for the port (run by CMake) |
| `tools/dosref.py`, `tools/portcompare.py` | run the original in DOSBox-X with a key script; compare with the port |
| `tcc.py`, `toolchain.py`, `repack.py`, `lz91.py`, `mz.py`, `common.py` | the pinned toolchain, LZEXE, EXE format; used by the above |
