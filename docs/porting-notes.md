# Notes for the SDL3 port

The port comes after the standalone historical tree (docs/roadmap.md, phase 5). Historical
source stays primary: the DOS build must keep producing the original binaries, so the port
replaces only a platform layer and never changes historical compiler inputs.

This map was produced from the reconstructed sources (research worker `luna-port`, reviewed by
the supervisor).  Function and global names are the logical ids (`g1_XXXX`, `d_XXXX`); semantic
names will come through `layout/symbols.json`.

## Evidence labels and limits

- **PROVEN** means the repository’s proof model states that a property is strictly proven. `docs/proof-model.md` says the `ASM_TEXT` contribution from `src/asm/toolbox.asm` is proven as a whole (1,082 bytes in each episode), and G2 code/data are proven at translation-unit level; G1 is incomplete. `README.md` identifies Turbo C 2.0, large model, for the historical build.
- **OBSERVED** means the behavior or constant is present in the checked-in reconstruction. It does not imply that each cited C function has been individually proven against the oracle.
- **HYPOTHESIS** marks a port design, an inferred meaning, or a behavior not closed by current source/proof.

The code below is source-grounded. The repository does not yet claim a complete natural link or a complete recovered game (`docs/proof-model.md`, “Not claimed”).

## 1. Hardware, DOS, and data dependencies

### Video: EGA/VGA memory, registers, pages, and BIOS

| Evidence | Dependency and source references |
|---|---|
| **OBSERVED** | EGA mode setup: `g1_ec3d` calls `asm_0258(0)` from `src/asm/toolbox.asm`; the routine’s argument-zero branch invokes BIOS `INT 10h` with AL=`0Dh`. BIOS mode-setting calls also appear in the remaining code under that assembly procedure. `asm_029d` invokes `INT 10h` with AX=`1000h` and parameters in BX; callers `g2_0009`, `g2_0036`, and `g2_01a9` use it for indexed color changes. `asm_05f7` calls `INT 10h`/AH=`05h` to select a display page. These are the source’s direct video BIOS calls; no direct `INT 21h` instruction appears in the C or assembly sources searched. |
| **OBSERVED** | VGA/EGA segment access: `g1_10fb` constructs `MK_FP(0xA000,0)` and `MK_FP(0xA000,0x4000)`; `g2_32b6`, `g2_340f`, `g2_3568`, `g2_36c1` also address A000:0000; `g2_315d` uses the far-pointer literal `0xA0000000L`. These routines write VRAM through the sequencer’s plane map mask. `g2_2e8c` writes text and attributes directly to B800:0000. |
| **OBSERVED** | Ports `0x3C4` and `0x3CE` are written in C and assembly. C register-writing sites include `g1_008a`, `g1_037e`, `g1_049f`, `g1_0b85`, `g1_10fb`, `g1_14af`, `g1_6afd`, `g1_e3e0`; and `g2_0286`, `g2_1058`, `g2_10f0`, `g2_11f2`, `g2_1ee1`, `g2_29a2`, `g2_2ab9`, `g2_2d58`, `g2_3114`, `g2_315d`, `g2_32b6`, `g2_340f`, `g2_3568`, `g2_36c1`, `g2_37b6`, `g2_3d8c`, `g2_4009`. The repeated sequencer writes select plane masks 1/2/4/8; `0x3CE` writes select graphics-controller state. |
| **PROVEN / OBSERVED** | The proven assembly module supplies the key renderer/page routines: `asm_02ad` copies 16 bytes per row from A400 planar source memory to the selected A000 page; `asm_0315` copies planar screen data; a retrace-wait sequence reading VGA input-status port `0x3DA` follows a `RETF` within the same assembly extent, so whether it is a separately entered routine is unresolved; `asm_0424`, `asm_04c5`, and `asm_053c` render/copy planar glyph or tile data while switching plane masks; `asm_05eb` stores the draw-page selector in assembly variable `c_0247`; `asm_05f7` changes the BIOS display page. Source also contains `page_io_wait`, which reads the CRTC base I/O address from BIOS data area `0040:0063`, waits on retrace at base+6, then writes CRTC indexes 18 and 7 (normally the `0x3D4` family for color display). The source does not show a caller for `page_io_wait`; treat it as present but not established in the active path. |
| **OBSERVED** | Page copying is also in C: `g2_315d`, `g2_32b6`, `g2_340f`, `g2_3568`, and `g2_36c1` each copy four 8,000-byte plane slices (`0x1F40` each) from loaded buffers to A000 memory, using `0x3C4` masks and `asm_05f7` around the copy. `g2_01d5` and `g1_b118` change draw/display page selections. Thus replacing only `toolbox.asm` would leave direct VRAM/register dependencies in G1/G2 C. |
| **HYPOTHESIS** | A portable renderer should initially preserve a 320×200, 16-color logical framebuffer and two logical pages, then convert indexed pixels to an SDL texture. `asm_0424` uses 40 bytes per row and G2’s plane copies use four 8,000-byte planes; these fit that interpretation. Keep the exact palette and page sequencing until screenshots/gameplay establish a safe simplification. |

There is no explicit VGA DAC port sequence at `0x3C8/0x3C9` in the searched C/ASM. Palette transitions use BIOS `INT 10h` via `asm_029d` and delays in `g2_0009`, `g2_0036`, `g2_01a9` (**OBSERVED**). Do not mistake the `0x3CE` register writes for palette programming.

### Keyboard, joystick, timer, and speaker

| Evidence | Dependency and source references |
|---|---|
| **OBSERVED** | Keyboard IRQ: `g1_ec3d` saves vector 9 with `getvect(9)` and installs `g1_15f4` with `setvect(9,...)`; `g1_fc9c` restores the saved vector. `g1_15f4` reads scan codes from port `0x60`, stores the latest in `d_a0fa`, updates held-key flags from make/break codes, acknowledges the keyboard via port `0x61`, and sends PIC EOI to port `0x20`. When `d_039d` is set it calls the previous vector. `g2_276f` waits out the `0xE0` extended-key prefix. Main/menu code often reads the shared `d_a0fa` directly. |
| **OBSERVED** | Joystick game port `0x201`: axis timing is measured by `g2_01f5` (write current port byte, then count while axis bits 1/2 or 4/8 stay set, capped at 500); `g1_0c52` maps the resulting coordinates and reads button bits; `g1_1053`/`g1_10a5` read buttons; `g1_049f` and `g1_e947` poll buttons during menu/demo waits; `g2_1340`, `g2_25cd`, and `g2_2870` also poll the port. Button masks include `0x10`, `0x20`, `0x40`, `0x80`. |
| **OBSERVED** | PIT channel 0: `g2_1e97` writes command `0x36` to `0x43`, divisor bytes `0x51`, `0x20` to `0x40`, saves vector 8, and installs `g2_25fc`. The ISR increments `d_02fb` once per interrupt and chains the prior BIOS timer handler every eight interrupts using `d_d718`. `g2_1319` restores the vector and reprograms channel 0 with zero bytes on exit. `g1_e92e(n)` resets `d_02fb` and busy-waits until it reaches `n`. |
| **OBSERVED** | PC speaker sound uses PIT channel 2 and port `0x61`: `g2_25fc` consumes signed-word periods from arrays pointed to by `d_cbb5`, stops at `-1`, writes mode `0xB6` to port `0x43`, period bytes to `0x42`, and toggles speaker gate bits at `0x61`. `g1_0042(priority)` updates the queued sound selection under `disable/enable`; the ISR starts it on a later interrupt. `g2_1058` toggles sound enable state `d_0097` and silences the speaker when disabled. `g2_3980`/`g2_3a38` load the data later indexed by the sound ISR (the sound-table interpretation is supported by the consumers). |
| **HYPOTHESIS** | Given a conventional PC PIT input clock, divisor `0x2051` implies roughly 144 timer interrupts per second, with the BIOS tick forwarded roughly every eighth IRQ. The source proves the programmed divisor and divide-by-eight logic, not a measured wall-clock rate. `delay(n)` calls are separate DOS delays and should not silently be reinterpreted as frame counts. |

### DOS/runtime services, 16-bit memory model, and files

**OBSERVED:** C includes Turbo headers `dos.h`, `conio.h`, `alloc.h`, and uses `inport[b]`, `outport[b]`, `disable/enable`, `getvect/setvect`, `delay`, `textmode(3)`, `coreleft`, `__exit`, `malloc`, `FILE` and stdio. `g1_e83e` rejects startup below `0x57E40` bytes reported by `coreleft`. `g1_fc9c` restores text mode and keyboard/timer vectors before `__exit`. Standard file calls are DOS-runtime dependencies even though first-party source does not issue `INT 21h` itself. Direct `INT 21h` use is **not observed**; the CL.LIB/runtime path behind stdio is a DOS dependency (**HYPOTHESIS**, inferred from the target runtime).

**OBSERVED:** Turbo C large model/far data is pervasive: `char far *`, `void far *`, `unsigned int far *`, far function/vector pointers, arrays of far pointers, `MK_FP`, and the far literal `0xA0000000L`. Examples include buffers allocated in `g1_e00d`, VRAM in `g1_10fb`/G2 image functions, records in `g1_c287`, and sound data in `g2_25fc`. Segment arithmetic and far-pointer comparisons/indexing are part of behavior, not cosmetic type annotations.

### Files named by source and the byte layouts actually used

Names below are literal source families. `X` means `.dn1`, `.dn2`, or `.dn3`; per-episode capitalization differs in `g1_e00d`, `g1_ec3d`, and the G2 prefix table. A DOS-compatible portable file resolver must account for this on case-sensitive filesystems (**HYPOTHESIS**).

| Evidence | Source names and observed read/write contract |
|---|---|
| **OBSERVED** | `g1_e00d` loads `border.dnX`, `font1.dnX`, `font2.dnX`, `numbers.dnX`, `object0.dnX`–`object2.dnX`, `man0.dnX`–`man3.dnX`, `back0.dnX`–`back3.dnX`, `solid0.dnX`–`solid3.dnX`, and `anim0.dnX`–`anim5.dnX`. `g1_295e` skips three bytes, then reads a raw payload: font1/font2 `0x7D0` bytes each; numbers/object0–2 `0x1F40` each; man0–3 and anim0–5 `0x1E00` each. Destinations are visible in `g1_e00d`. No decompression or validation is performed by `g1_295e`. |
| **OBSERVED** | The same initializer calls `g1_10fb` for `border`, `back0`–`back3`, and `solid0`–`solid3`, each with count `0x1E00`; `g1_e3e0` calls it for `drop` resources with count `0x5140` and VRAM offsets `0x4000` / `0x8100`. `g1_10fb` skips three header bytes, loops `count/4` times, discards one byte, then reads four bytes into four selected VGA planes. If the full loop has data, it consumes `3 + 5*(count/4)` bytes: `0x2583` for count `0x1E00`, `0x6593` for count `0x5140`. Treat these as observed access lengths, not verified complete file lengths; `fopen`/EOF are not checked. |
| **OBSERVED** | `src/g2/data/prefix.c` supplies drop names: DN1 `drop0`, `drop1`, `drop2`, `drop3`, `drop5`, `drop7`, `drop9`, `drop11`, `drop13`; DN2 `drop1`, `drop2`, `drop3`, `drop5`, `drop8`, `drop9`, `drop11`, `drop13`; DN3 `drop0`, `drop1`, `drop2`, `drop3`, `drop5`, `drop6`, `drop9`, `drop10`, `drop12`, `drop13`. Names are `.dnX`; the 22-entry table contains repeats. |
| **OBSERVED** | Startup `g1_ec3d` names `KEYS.DN1` / `KEYS.dn2` / `KEYS.DN3` (six bytes read/written by `g2_2104`/`g2_205f`); `SPEED.DN1` / `SPEED.dn2` / `SPEED.DN3` (one `getw`/`putw`, two bytes, `g1_e89d`/`g1_e8ed`); and `duke1.dnX`, `duke1-b.dnX`, `dn.dnX`, `end.dnX`, `badguy.dnX`, `duke.dnX`, `credits.dnX`. |
| **OBSERVED** | `g2_3980` reads `duke1.dnX`: `0x2454` bytes into a `0x2454` allocation, then derives 24 far pointers and priority bytes. `g2_3a38` reads `duke1-b.dnX`: `0x1F40` bytes into a `0x2134` allocation, then derives 24 pointers/bytes. These tables feed the timer sound path; exact semantic record layout should be checked before replacing its parser. |
| **OBSERVED** | `g2_3252`, `g2_365d`, `g2_33ab`, `g2_3504`, `g2_30b0` read respectively `dn.dnX`, `end.dnX`, `badguy.dnX`, `duke.dnX`, `credits.dnX`, exactly `0x7D00` bytes each; `g2_32b6`, `g2_36c1`, `g2_340f`, `g2_3568`, `g2_315d` copy these as four `0x1F40`-byte planes. |
| **OBSERVED / HYPOTHESIS** | `g1_e655` passes `d_03a4[d_02fa]` to `g1_e3e0`; `g1_de26` reads `0x2D00` two-byte elements (`0x5A00` bytes) into the level word array `d_7729`. The definition/initializer for `d_03a4` is absent from the checked-in source, so the level-map filenames cannot be enumerated from these sources. A 16-bit tile/map-word interpretation is observed; exact map schema is not. |
| **OBSERVED** | `USERDEMO.DN1` / `USERDEMO.dn2` / `USERDEMO.dn3` and `MY_DEMO.DN1` / `MY_DEMO.dn2` / `MY_DEMO.DN3`: `g1_de71`/`g1_dee9` read a `getw` word followed by `0x4268` (17,000) bytes; `g1_df57`/`g1_dfb2` write the same shape. The buffers allocated by `g1_e00d` are `0x4650` bytes. |
| **OBSERVED** | `saved<slot>.dnX` is formed by replacing character 5 in literal `"saved .dnX"` (`g1_0151`, `g2_219d`). Save/load is 22 successive `putw`/`getw` values (44 bytes under the DOS 16-bit ABI), followed by `d_68f8` as decimal `%ld` plus newline / parsed by `%ld`. Fixed total size is not established because the decimal text length varies. |
| **OBSERVED** | `HIGHS.DN1` / `HIGHS.dn2` / `HIGHS.dn3`: `g2_1e1b` writes ten score/name pairs as `%lu`, `%s\n`; `g2_24b1` reads ten pairs with `%lu` then `%[^\n]s`. This is a text format with variable-width numbers/names, not a fixed binary record. |

## 2. Main loop, timing, and per-frame driving

| Evidence | Source path |
|---|---|
| **OBSERVED** | `main` in `g1_ff16` calls `g1_ec3d` once, then loops forever through `g1_fd15()`, `g1_fc85()`, `g2_01a9(15)`, and `d_5318=0`. The launcher checks `argv[1]` for the `asp` prefix and may set `d_039d` from `argv[2]`. |
| **OBSERVED** | Startup `g1_ec3d` checks available DOS memory (`g1_e83e`), selects video mode/page, loads keyboard mapping, high scores and episode resources, installs IRQ 9, starts the IRQ 8/PIT service (`g2_1e97`), then reads the speed setting. Shutdown `g1_fc9c` writes settings/demo data, restores IRQ 9, restores timer hardware/vector (`g2_1319`), returns to text mode and exits. |
| **OBSERVED** | The menu/game-state loop is `g1_fd15`, which calls `g1_049f(7)` and branches on its result. `g1_049f` blocks while checking keyboard scan state `d_a0fa`, joystick buttons from `0x201`, tick count `d_02fb`, and drawing/copying menu images. `g1_e92e` is a separate busy-wait in timer ticks. Palette transitions use `g2_0009`/`g2_0036`/`g2_01a9`, which call DOS `delay`. |
| **OBSERVED** | Level entry path: `g1_e655` resets state, optionally loads a save, then calls `g1_e3e0(d_03a4[d_02fa])`. `g1_e3e0` reads the map, sets VGA state, loads selected drop assets, and calls `g1_c287(0x5A)`. `g1_c287` walks map words and registers entity/update callbacks through `g1_c243`; `g1_e3e0` then calls `g1_bb9f`. Many entity routines update coordinates/state and draw via `asm_0424`, but are spread across individual functions. |
| **OBSERVED** | `g2_25fc` is interrupt-driven, not called by the main C loop. Every timer IRQ it increments `d_02fb`, advances one sound-table entry when active, and chains the old BIOS timer routine every eighth IRQ. Rendering and keyboard state changes are likewise interleaved through page/register routines and the keyboard IRQ. |
| **HYPOTHESIS** | Current recovered code does not establish one canonical fixed-rate gameplay frame dispatcher or its exact call order. The map loader registers many callbacks, but the proof model says G1 and the complete image are still incomplete. Trace the remaining runtime call chain before assigning SDL delta-time semantics. During a port, every busy wait on `d_a0fa` or `d_02fb` must either pump SDL events or be replaced by a wait/service boundary; merely adding a delay to `main` would leave input unresponsive inside these loops. |

## 3. Port seam and risks

### Proposed seam

**HYPOTHESIS:** Keep the DOS branch byte-for-byte/source-for-source as the canonical historical build. Select an alternate platform implementation set only in the new SDL3 build. Preserve existing non-ISR C symbol signatures where practical so recovered logic can call the same interfaces; do not “port” by changing the historical compiler inputs.

| Layer | DOS implementation to retain | SDL3 implementation / likely boundary |
|---|---|---|
| Video and palette | Existing `src/asm/toolbox.asm` and C routines unchanged for the Turbo build. C-facing assembly symbols include `asm_0258`, `asm_029d`, `asm_02ad`, `asm_0315`, `asm_0424`, `asm_04c5`, `asm_053c`, `asm_05eb`, `asm_05f7`. | Provide alternate implementations for mode/palette, draw-page/display-page, planar blits, text, and retrace waits. Also isolate direct VRAM/register C sites, especially `g1_10fb`, `g1_14af`, `g1_6afd`, `g1_e3e0`, `g2_315d`, `g2_32b6`, `g2_340f`, `g2_3568`, `g2_36c1`, `g2_37b6`, `g2_2e8c`. Render through a host framebuffer/SDL texture, with a palette table and explicit logical page. |
| Input | Keep IRQ 9 handler and DOS vector setup as-is. Preserve the public behavior of `g1_1053`, `g1_0c52`, `g1_10a5`, `g2_01f5` and game-visible key state for DOS. | Translate SDL keyboard/controller events to the same game key flags and button/axis state. Add an event pump at waits/update boundaries. ISR functions `g1_15f4` and `g2_25fc` cannot be installed as hardware interrupts in SDL; keep their DOS definitions only in the DOS source set and move their game-state effects to host callbacks. |
| Timing and sound | Keep `g2_1e97`, `g2_1319`, `g2_25fc`, `g1_e92e`, and `g1_0042` with current signatures in the historical target. | Replace PIT/vector installation with an SDL performance-counter or timer service that advances compatible game ticks and feeds a queued SDL audio stream. Keep `g1_0042(priority)` as the game-facing sound request; move note playback off the DOS ISR. Use fixed-step catch-up with bounded work only after the original tick cadence is measured. |
| Resource/file I/O | Existing stdio loaders and raw DOS layouts remain available in the historical target. | Keep high-level asset/save operations where format is portable; split `g1_10fb` file parsing from VRAM upload. Add a path resolver for episode suffix/case and explicit fixed-width readers/writers for 16-bit words and 32-bit values. Preserve save/demo compatibility or define a deliberate versioned host format. |
| Game logic | Pure gameplay/math/state routines that avoid DOS headers, far pointers, hardware calls, and ABI-sensitive layout can remain identical C source. | Compile those unchanged where feasible after replacing 16-bit/far data interfaces with explicit compatibility types or adapter APIs. Separate renderer/input/timer effects from logic only in the SDL branch. |

### Risks

- **HYPOTHESIS — integer widths:** Turbo C `int` and `unsigned int` are 16-bit; most SDL3 host compilers use 32-bit `int`. Tile IDs, loop overflow, `%`, shifts, and counters can change behavior. Use fixed-width types at the port boundary and audit arithmetic before changing source types.
- **OBSERVED/HYPOTHESIS — far pointers and segments:** `MK_FP`, far arithmetic, pointer tables, and `0xA000`/`0xB800` aliasing cannot be represented by ordinary host pointers with equivalent semantics. Model VRAM and DOS buffers as explicit arrays/spans; preserve wrap/offset behavior where tests show it matters.
- **HYPOTHESIS — structure packing and callbacks:** entity records are read through many hand-typed structs and far pointers; host alignment may differ from Turbo packing. Define serialized/resource records with explicit 16-bit fields and assert offsets. Function-pointer tables also assume the original calling convention and address model.
- **OBSERVED/HYPOTHESIS — endianness:** `getw`/`putw` and map-word arrays are 16-bit DOS values; x86 is little-endian, while portable file parsing should encode little-endian explicitly rather than relying on host layout. Save fields currently mix word writes with decimal text.
- **OBSERVED/HYPOTHESIS — timing:** asynchronous IRQ ticks, busy waits, 5–300 ms `delay` calls, and timer-driven sound do not map directly to SDL frame callbacks. Keep simulation tick and render cadence distinct until a reference cadence is measured.
- **HYPOTHESIS — surface conventions:** EGA plane layout, VGA pages, BIOS palette indices, retrace synchronization, and the game’s apparent 320×200 viewport need screenshot comparison before compressing them into a single SDL surface. Preserve raw asset bytes for diagnostics.

## 4. Ordered minimal work plan

1. **HYPOTHESIS:** Freeze a DOS baseline and record startup/gameplay/shutdown video, sound, input, and timing traces for all three episodes. Keep the existing historical build and proof workflow untouched.
2. **HYPOTHESIS:** Define a host-side platform ABI for indexed 320×200 video, palette/page selection, key state, joystick state, timer ticks, sound requests, file paths, and quit. Map each entry to existing symbol signatures where practical; document the ISR exceptions.
3. **HYPOTHESIS:** Port the smallest vertical slice: startup/mode selection, `asm_029d` palette fades, text/glyph drawing, page copy/flip, SDL event polling, and timer service. Compare static screens and input response with DOS captures.
4. **HYPOTHESIS:** Add resource loading with explicit three-byte header handling, episode path resolution, planar-to-indexed conversion, and the exact resource read lengths listed above. Validate each decoded image before level logic.
5. **HYPOTHESIS:** Port level map loading and fixed-width record layouts; then run the gameplay callbacks under a measured fixed-step timer. Preserve original globals/callback order while replacing direct hardware effects.
6. **HYPOTHESIS:** Add SDL audio translation for `d_cbb5` note sequences and sound priority, then port saves, demos, high scores, and speed/key settings with compatibility fixtures.
7. **HYPOTHESIS:** Exercise DN1/DN2/DN3 end-to-end, compare deterministic input/playback traces and screenshots, and fix per-episode filename/data differences. Keep this work in the portable build path; any historical-source change must be separately re-proven under the repository’s supervisor workflow.

## Assembly routines (src/asm/toolbox.asm, proven as one module)

The ProGraphx EGA/VGA Toolbox module (banner string in its data header) is reconstructed and
proven as a whole; per-routine roles:

| Routine | Size | Behaviour | Callers |
|---|---:|---|---|
| `asm_0258` | 69 | video BIOS `int 10h` mode setting (AL=0Dh for argument 0), plus an unreferenced CRTC/retrace helper after its RETF | `g1_ec3d` |
| `asm_029d` | 16 | `int 10h` AX=1000h palette register | `g2_0009`, `g2_0036`, `g2_01a9` |
| `asm_02ad` | 104 | 16-byte-per-row planar copy from A400 to the selected A000 page | `g1_14af`, `g1_ecf4` |
| `asm_0315` | 271 | planar screen copy with retrace wait (port 3DAh) | `g1_6afd` |
| `asm_0424` | 161 | planar tile/sprite blit, plane masks via 3C4h/3CEh | many entity routines |
| `asm_04c5` | 119 | planar glyph/text drawing | `g2_37b6`, `g2_385b` |
| `asm_053c` | 175 | planar blit variant | `g2_2789` |
| `asm_05eb` | 12 | sets the draw page (`c_0247`) | many |
| `asm_05f7` | 12 | `int 10h` AH=05h display page | many |
