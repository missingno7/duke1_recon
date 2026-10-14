# Enhanced port: plan (branch `enhanced`)

Goal: optional enhancements on top of the SDL3 port — widescreen, smooth camera,
interpolated motion, scalers, stereo sound — while `src/` stays the original program
(byte-identical DOS build) and the authentic port stays available.  Everything lives in
`port/`; every enhancement is an option, off by default until it is solid.

## Feasibility

**Verdict: feasible without touching `src/`.**  The enabling fact is that the game draws
gameplay through very few routines, which the port already implements:

| What | How the game draws it | Seam |
|---|---|---|
| map tiles | `draw_animated_level_strip`: 14 x 10 tiles of 16 px from `level_tile_map`, backdrop where the tile is 0 or 0x20 | `blit_bitmap_to_video_page` (toolbox) |
| actors, player, shots, effects | `blit_planar_sprite_rows(source, x, y)`, 223 call sites | toolbox |
| water | `copy_planar_video_region` | toolbox |
| frame end | page flip: `select_draw_page` + `show_video_page` once per game frame | toolbox |
| HUD, dialogs, texts | border bitmaps and glyphs into the page | toolbox + EGA page |

So the port can record each gameplay frame as a list of draw commands (sprite source,
screen position) plus the scroll position, convert them to world coordinates, and render
the frame itself — at any resolution, camera position and time — instead of showing the
emulated EGA page.  The EGA emulation keeps running underneath; it remains the output for
menus and full-screen pictures and the source of the HUD and dialog overlays.

Measured facts that shape the plan:

* The game logic runs at about **16 frames/s** (9 ticks of the 144 Hz timer per frame).
* The camera moves in **8-pixel steps horizontally and 16-pixel steps vertically**; actors
  move in 8-pixel steps (x is kept in half tiles).  Interpolation therefore makes a large
  visible difference.
* The playfield is 224 x 160 pixels at (16, 16); the HUD is the panel on the right
  (x >= 240).  The map is 128 x 90 tiles.
* **Widescreen catch:** the view test `is_world_position_outside_view` is used 125 times
  to skip drawing but about 50 times for behaviour (enemies move and fire only when
  visible, shots vanish when they leave the view, boxes fall only when visible).  A wider
  view either shows those actors frozen, or widens the area in which they act, which
  changes the gameplay.  Both are offered (below).

## Architecture: a complete native presentation

The enhanced renderer never shows the emulated EGA page.  Everything the game draws becomes
native items, and every picture - level, HUD, frame, dialogs, texts, menus, title pictures - is
composed from them.

* **Scene (game thread, `port/scene.c`).**  Each toolbox primitive (16x16 bitmaps: map tiles,
  backdrop, frame, dialog borders; masked sprites; glyphs; the water copy) and every write that
  bypasses the toolbox (the full-screen pictures, noticed by write accounting in the emulated
  EGA) becomes an item on the video page it was drawn to.  An item keeps its position, size,
  kind, its space - WORLD (level, with a level position), BACKDROP (screen-fixed cells behind
  the level) or SCREEN (everything else) - and its own pixels, read back from the emulated page
  right after the primitive ran, so items are exact by construction whatever register tricks
  the original used.  A per-page ownership map drops items that later drawing hid completely,
  so a page's list is exactly what it shows; the game's own clears (tile blits) empty it.
* **Presenter (main thread, `port/present.c`).**  Takes a snapshot of the displayed page
  whenever it changed and composes it into a canvas of palette indices, converted with the live
  palette (fades work):
  - at 320 wide: the items in drawing order at their positions - the original page exactly;
  - wider, without a level view (title, menus, pictures): the 320x200 picture centred;
  - wider, in the level: the backdrop as a stable screen-fixed layer across the width, the map
    tiles of the wide view straight from the level map (animated tiles included), level sprites
    at their level positions, dialogs and texts centred on the original view, the right column
    (frame bar + HUD) at the right edge, the top and bottom bars rebuilt from their own tiles
    (the plain tile repeated, the corner pieces kept, the "PRESS F1 FOR HELP" plate centred).
* **Dialogs need nothing special:** what the game draws on the shown page while it waits for a
  key is shown at once, in every layout.
* **Anchor test:** at 320 wide the composed picture must equal the emulated page on every frame
  - menus, dialogs, title screens and gameplay alike.

## Settings: `duke1.json`

One flat JSON object in the game folder, written with every key and its default on first
start; unknown keys are ignored, missing keys take the default, a broken file is reported
and replaced.  The episode screen has a "Port settings" entry that edits the same values in
a dialog drawn with the game's own routines (like the episode dialog).

| Key | Values (default first) | Meaning |
|---|---|---|
| `renderer` | `"classic"`, `"enhanced"` | classic: the emulated EGA screen; enhanced: the native renderer (needed by everything below the line) |
| `fullscreen` | `false`, `true` | borderless fullscreen on the current display (Alt+Enter toggles and saves) |
| `window_width`, `window_height` | `1280`, `800` | last windowed size (saved on exit) |
| `aspect` | `"auto"`, `"4:3"`, `"16:10"`, `"16:9"`, `"21:9"`, `"32:9"` | shape of the picture: `auto` fills the window, a ratio letterboxes |
| `pixel_aspect` | `"4:3"`, `"square"` | 4:3: pixels 1.2 x taller, as on a CRT; square: 1:1 |
| `integer_scale` | `false`, `true` | only whole-number scale factors |
| `filter` | `"sharp"`, `"nearest"`, `"linear"` | sharp: nearest at the integer part, smoothed seams |
| `volume` | `80` (0-100) | speaker volume |
| `stereo` | `false`, `true` | pan speaker sounds by where they come from |
| --- | | (enhanced renderer only) |
| `widescreen` | `false`, `true` | the playfield grows to the picture shape; the HUD frame stretches |
| `wide_activity` | `false`, `true` | actors act in the whole wide view (changes gameplay) |
| `smooth_camera` | `false`, `true` | continuous camera instead of 8/16-pixel steps |
| `interpolation` | `false`, `true` | actors and shots move smoothly between game frames |
| `frame_cap` | `0` | 0: the display's refresh rate; N: at most N frames per second |

## The picture and the HUD frame

Widescreen changes only the game's width.  The canvas is always 200 game pixels high; its
width follows the target shape (`aspect`, or the window with `auto`; `pixel_aspect`
decides whether a game pixel is square or 1.2 high), never narrower than 320.  The canvas
is scaled to the window (whole factors with `integer_scale`) and centred; a window
narrower than the canvas is letterboxed.

The in-game frame stretches horizontally only: the top and bottom bars repeat plain
vertical slices left and right of their fixed parts - the screws in the corners, the
cable at the top left, and the "PRESS F1 FOR HELP" plate, which stays centred under the
playfield - and the HUD column (SCORE, HEALTH, FIREPOWER, INVENTORY) keeps its place at
the right edge.  The playfield takes the extra width: more of the level is visible.

Widescreen without changing gameplay: the port generator gives the 125 view tests that
only decide whether to *draw* a wide view, so everything the game would draw is drawn in
the margins; the 50 that decide behaviour keep the original view unless `wide_activity`
is on.  Draw calls outside the original playfield are recorded for the native renderer
and never written into the emulated page (whose off-screen memory holds the tile cache).

## Milestones

Each one is a bounded task with its own acceptance test; none changes `src/`.

1. **Frame capture + native renderer at 1x.**  Record frames in the toolbox, hand them
   to the render thread, render them natively.  Accept: pixel-equal to the EGA page in
   gameplay (anchor test) on the first level of each episode.
2. **Output pipeline and scalers.**  Internal resolution and integer scaling, aspect
   (4:3 / square pixels), filters: nearest, sharp-bilinear, Scale2x/3x, hq2x/xBR on the
   atlas, and a CRT shader later through SDL_GPU.  Accept: each scaler selectable at run
   time, no tearing.
3. **Smooth camera.**  The renderer's camera follows the player continuously (critically
   damped, clamped to the map) and is interpolated between game frames; tiles come
   straight from the map, so any sub-pixel camera position renders.  Accept: no visible
   8/16-pixel steps while walking or falling; a recorded demo looks smooth.
4. **Interpolated motion.**  Actors, shots and the player slide between their positions
   in consecutive game frames; animation frames still switch at game rate.  Accept:
   scripted runs with fast enemies show no snapping except on teleport and respawn.
5. **Widescreen.**  16:9 and 16:10 views; the HUD as a side panel or an overlay.  Two
   behaviours:
   * *authentic* (default): the game's logic is untouched; the extra margin shows the map
     and every actor as last seen (actors that were never on screen are drawn by a
     per-kind default frame).  Gameplay is identical to the original.
   * *wide activity*: the view test is widened to the wide view, so actors in the margin
     move and act.  Gameplay changes (enemies wake earlier); labelled as such.
   Accept: both modes play the first levels of each episode without visual glitches at
   the map edges.
6. **Stereo and cleaner sound.**  Pan each speaker sound by its source position: the
   port remembers the position of the latest view test before a sound request (most
   requests follow one), the player's position for the player's own sounds, centre
   otherwise.  Band-limited synthesis (no aliasing) and an optional speaker filter.
   Accept: a WAV capture of a scripted level shows the expected pans.
7. **Options.**  Command-line flags and `duke1.ini`; an "Enhancements" dialog drawn with
   the game's own dialog routines (like the episode dialog) to toggle them at run time.

Order: 1 is the foundation for 2-5; 6 is independent and can run in parallel; 7 last.

## Risks

* Overlay detection mid-gameplay (dialogs, hint signs, transitions): handled by the
  overlay mask; the anchor test catches misses.
* Palette effects (fades, flashes) must apply to the native output too: the renderer
  uses the live palette registers.
* Special effects drawn by latch copies (water) need their own command kind.
* Identity heuristics can mismatch when records are reused in the same frame; the
  position-jump test turns that into a snap, never a wrong slide.
* Widescreen margins at the map edges: the camera clamps to the map; beyond it, black.
