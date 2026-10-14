/* wide_pass.h - the widescreen presentation pass (docs/enhanced.md, "The wide margins").

   The game runs and draws an actor only inside its active window (is_world_position_outside_view):
   outside it the actor is frozen.  The wide view shows more of the level than that window, so
   after each game frame the presentation pass runs the frame's actor routines once more on a
   throwaway copy of the game state, with the view tests answering "inside" only for the wide
   margins, keeps the level sprites they draw (off the page) and puts every byte back.  The game
   logic never sees the pass: a frozen actor is shown exactly as the game would draw it the
   moment it came into view.

   While the pass runs, every platform hook the game code can reach is inert: ports, the EGA,
   the speaker, CLI/STI do nothing; anything that would wait, allocate, open a file or leave
   the frame (pc_halt, pc_spin, pc_delay, pc_malloc, pc_fopen, pc_exit ...) abandons the pass. */
#ifndef WIDE_PASS_H
#define WIDE_PASS_H

#include <stddef.h>
#include <stdint.h>

extern int port_in_wide_pass;           /* game thread: the pass is running */

/* Called by the generated frame loop after the frame's own drawing (port_gen.py). */
void port_wide_presentation_pass(void (*pass)(void), unsigned char *tile_map, uint16_t tile_map_size);

/* Hooks that must not run inside the pass call this; it returns only outside the pass. */
void port_wide_pass_abandon(const char *what);

void port_wide_pass_report(void);

#endif
