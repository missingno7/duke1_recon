# The original executables

The oracle: Duke Nukem ("Duke Nukum") v2.0, episodes 1–3, as shipped.  The files are
never committed; `config/oracle.lock.json` holds their identity, and
`python tools/oracle.py` checks a copy in `assets/` against it.

| Episode | File SHA-256 | Size | Unpacked image | Relocations | Entry |
|---|---|---:|---:|---:|---|
| DN1.EXE | `7e31ad9f…87cc5f` | 54,688 | 118,010 | 1,581 | CS:IP 0000:0000, SS:SP 255E:00E6 |
| DN2.EXE | `b155c58e…15910a` | 54,595 | 118,290 | 1,584 | CS:IP 0000:0000, SS:SP 2570:00E6 |
| DN3.EXE | `7966ca89…81b802` | 54,439 | 117,830 | 1,586 | CS:IP 0000:0000, SS:SP 2553:00E6 |

All three are packed with LZEXE 0.91.  `tools/lz91.py` decodes them (the unpacked image is
what `tools/build.py` compares the linked program with); re-packing the linked program
with the original LZEXE 0.91 reproduces the shipped files byte for byte, which
`tools/build.py` also checks.  `DNHINT.EXE`, a separate hint program in the same
distribution, is not part of this source.

## What the executables are made of

| Part | DN1 offset | Size | Source |
|---|---|---:|---|
| start-up | 0x00000 | 457 | Turbo C 2.0 `C0L.OBJ` (large model) |
| toolbox | 0x001C9 | 1,082 | `src/TOOLBOX.ASM`, identical in all episodes |
| runtime, near part | 0x00603 | 885 | `CL.LIB` modules (SETARGV … SCOPY) |
| first unit | 0x00978 | 65,393 | `src/GAME1.C` (segment `GAME1_TEXT`), the same shape in all episodes |
| second unit | 0x108E9 | 18,053 / 18,116 / 18,146 | `src/GAME2.C`, most episode differences |
| runtime, far part | 0x14F6E | 11,964 | `CL.LIB` modules (IOERROR … UNGETC), 2–5 bytes of TLINK alignment fill |
| data | 0x17E30 / 0x17E70 / 0x17E90 | | initialised 20,170 / 20,386 / 19,894 bytes; uninitialised 35,042 bytes in all |

The first unit sits at the 64 KB segment limit.  The episodes differ mostly in file-name
extensions (`.DN1`, `.DN2`, `.DN3`) and texts, and in a few functions of the second unit.
