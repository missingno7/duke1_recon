# Notes for a later SDL3 port

The port is out of scope for the bootstrap. Historical source stays primary; a
modern branch should reuse recovered gameplay C unchanged where possible and
replace only the platform layer. Avoid any abstraction in `src/` that would
change historical code generation.

Plan:

* One SDL3 executable, episode chosen at run time. Historical builds differ by
  `EPISODE` (file extensions `.DN1/.DN2/.DN3`, text, G2 code differences);
  the port turns compile-time `EPISODE` into a run-time value only in a port
  layer, not in historical source.
* Replace the assembly region (EGA latch blitting, page flipping, palette), the
  interrupt handlers and port I/O with SDL equivalents.

Hardware and DOS behaviour identified so far (to be extended as functions are
recovered):

| Area | Evidence | Function(s) |
|---|---|---|
| Keyboard | `void interrupt` handler reading port 0x60, installed with `setvect(9, ...)`; 0xE0 extended prefix handling | ISR at `g1_15f4`; `g2_276f` |
| Second interrupt handler | `void interrupt` in G2, purpose not yet identified | `g2_25fc` |
| Timer ticks | busy-wait on a counter incremented elsewhere | `g1_e92e` (`d_02fb`) |
| Joystick | buttons from game port 0x201 | `g1_1053` |
| EGA | sequencer/graphics controller writes via `outport(0x3C4/0x3CE, ...)`; page selection through asm routines | `g2_37b6` (apparently text drawing), `g2_01d5` → `asm_05eb`/`asm_05f7` |
| Sound (apparent) | priority comparison and state update under cli/sti, called from 66 sites | `g1_0042` |
| Files | CL.LIB stdio (`fopen`, `fread`, `fscanf`, ...) on `*.DN?` data files | various |

Pointer assumptions: large model, far data pointers; arrays of structs in
DGROUP are addressed through ES:BX built from DS. DGROUP holds ~20 KB of
initialised data and ~35 KB of BSS.

## Assembly routines (ASM_TEXT, identical in all episodes)

Identified by census only (not reconstructed); first-pass notes from a quick scan of their I/O, to be verified:

| Routine | Size | Observed behaviour | Callers |
|---|---:|---|---|
| `asm_0258` | 69 | video BIOS `int 10h` dispatch (mode setting) | `g1_ec3d` |
| `asm_029d` | 16 | `int 10h` call | `g2_0009`, `g2_0036` |
| `asm_02ad` | 104 | no port I/O or BIOS call seen in a quick scan; role not yet read | `g1_14af`, `g1_ecf4` |
| `asm_0315` | 271 | port reads (`in al,dx`) near its end; role not yet read | `g1_6afd` |
| `asm_0424` | 161 | EGA sequencer/graphics writes (`out dx,al/ax`), tile blit | `g1_0a0e`, `g1_0adc` |
| `asm_04c5` | 119 | EGA writes, used for text/glyph drawing | `g2_37b6`, `g2_385b` |
| `asm_053c` | 175 | EGA writes | `g2_2789` |
| `asm_05eb` | 12 | page selection (called with 0/1) | many |
| `asm_05f7` | 12 | `int 10h` display page | many |

The external Duke1Decomp notes attribute this region to the ProGraphx EGA/VGA
Toolbox; that is a hypothesis here until the region is reassembled with TASM 1.0.
