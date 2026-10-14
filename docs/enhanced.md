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

## Architecture

```
game thread (16 Hz)                        render thread (display rate, e.g. 60-240 Hz)
  src/ logic, unchanged
  toolbox calls --record--> frame N {         frame N-1 + frame N + alpha(now)
                               camera,          -> camera (smoothed), actor positions
                               tiles region,       (interpolated), tiles from the map,
                               draw commands       sprites from a decoded atlas,
                               (sprite, world      overlays from the EGA page
                               x/y, identity),  -> scaler -> window
                               overlay mask }
```

* **Identity** of a draw command (needed to interpolate): the call site (the generator
  tags each `blit_planar_sprite_rows` call with a site number) plus its occurrence number
  within the frame.  Actors are drawn in record order, so this is stable while a record
  lives; a big jump in position means a different object and snaps instead of sliding.
* **Sprites and tiles** are decoded once from the game's own buffers (sprite banks in
  memory, tiles in the emulated video memory) into an RGBA atlas, cached by source.
* **Overlays**: during gameplay everything drawn outside the tile/sprite path (HUD
  numbers, dialog boxes, hint texts, "Press any key") is taken from the EGA page through a
  mask of the pixels such calls wrote this frame.
* **Anchor test:** with every enhancement off, the native renderer must reproduce the EGA
  page pixel for pixel in gameplay.  This test runs on scripted levels in all three
  episodes and keeps the whole pipeline honest.

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

The picture is built on a logical canvas measured in game pixels: 200 lines high when
the target shape is at least 4:3 (wider canvas for wider shapes), 320 wide otherwise
(taller canvas).  `pixel_aspect` decides whether a game pixel is square or 1.2 high.
The canvas is scaled to the window (whole factors with `integer_scale`) and centred.

In the enhanced renderer the in-game frame is a nine-slice: the grey bars of the border
repeat their plain middle pixels, the corners (screws, the cable), the "PRESS F1 FOR
HELP" plate (kept centred under the playfield) and the HUD column (SCORE, HEALTH,
FIREPOWER, INVENTORY, kept at the right edge, its panel background repeated vertically)
are drawn unscaled.  The playfield fills the rest: more of the level is visible.

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
