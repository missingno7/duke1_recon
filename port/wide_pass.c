/* wide_pass.c - the widescreen presentation pass (see wide_pass.h). */
#include "wide_pass.h"
#include "scene.h"

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* pc_sdl.c, pc_interrupt.c, pc_dos.c, vga.c */
int  platform_current_episode_state(unsigned char **begin, size_t *size);
void pc_hold_interrupts(int hold);
int  pc_allocation_segments(uint8_t **segments, int capacity);
uint64_t vga_state_fingerprint(void);

int port_in_wide_pass;

static jmp_buf abandon_point;
static const char *abandon_reason;
static uint64_t passes, abandoned;

void port_wide_pass_abandon(const char *what)
{
    if (!port_in_wide_pass) return;
    abandon_reason = what;
    longjmp(abandon_point, 1);
}

static void *grow(void *buffer, size_t *capacity, size_t needed)
{
    if (needed <= *capacity) return buffer;
    buffer = realloc(buffer, needed);
    *capacity = buffer ? needed : 0;
    return buffer;
}

/* DUKE1_WIDE_PASS_CHECK=1: prove that the pass leaves the game untouched beyond what it
   restores (the episode state and the level map): every allocated block and the EGA (planes,
   registers, latches) compare equal after it. */
#define CHECK_SEGMENTS 32
static int check_mode = -1;
static uint8_t *check_copy[CHECK_SEGMENTS];
static uint64_t check_failures;

static int check_save(uint8_t **segments)
{
    int count = pc_allocation_segments(segments, CHECK_SEGMENTS);
    for (int i = 0; i < count; ++i) {
        if (!check_copy[i] && !(check_copy[i] = (uint8_t *)malloc(0x10000))) return 0;
        memcpy(check_copy[i], segments[i], 0x10000);
    }
    return count;
}

static void check_compare(uint8_t **segments, int count, uint64_t vga_before)
{
    int bad = 0;
    for (int i = 0; i < count; ++i)
        if (memcmp(check_copy[i], segments[i], 0x10000)) {
            bad = 1;
            fprintf(stderr, "[wide pass] block %d changed by the pass\n", i);
        }
    if (vga_state_fingerprint() != vga_before) {
        bad = 1;
        fprintf(stderr, "[wide pass] EGA state changed by the pass\n");
    }
    if (bad && ++check_failures <= 5)
        fprintf(stderr, "[wide pass] pass %llu left a trace\n", (unsigned long long)passes);
}

static int pass_disabled;                 /* DUKE1_WIDE_PASS_OFF: for comparisons */

void port_wide_presentation_pass(void (*pass)(void), unsigned char *tile_map, uint16_t tile_map_size)
{
    static unsigned char *state_copy, *map_copy;
    static size_t state_capacity, map_capacity;
    static uint8_t *segments[CHECK_SEGMENTS];
    unsigned char *state;
    size_t state_size;
    int segment_count = 0;
    uint64_t vga_before = 0;

    if (!platform_current_episode_state(&state, &state_size)) return;
    if (check_mode < 0) {
        check_mode = getenv("DUKE1_WIDE_PASS_CHECK") != NULL;
        pass_disabled = getenv("DUKE1_WIDE_PASS_OFF") != NULL;
    }
    if (pass_disabled || !scene_wide_pass_wanted()) return;
    state_copy = (unsigned char *)grow(state_copy, &state_capacity, state_size);
    map_copy = (unsigned char *)grow(map_copy, &map_capacity, tile_map_size);
    if (!state_copy || !map_copy) return;

    pc_hold_interrupts(1);                  /* no handler may run between save and restore */
    memcpy(state_copy, state, state_size);
    memcpy(map_copy, tile_map, tile_map_size);
    if (check_mode) {
        segment_count = check_save(segments);
        vga_before = vga_state_fingerprint();
    }
    ++passes;
    scene_wide_pass_begin();
    port_in_wide_pass = 1;
    if (setjmp(abandon_point) == 0) {
        pass();
    } else if (++abandoned <= 5) {
        fprintf(stderr, "[wide pass] abandoned at %s\n", abandon_reason);
    }
    port_in_wide_pass = 0;
    scene_wide_pass_end();
    memcpy(state, state_copy, state_size);
    memcpy(tile_map, map_copy, tile_map_size);
    if (check_mode) check_compare(segments, segment_count, vga_before);
    pc_hold_interrupts(0);
}

/* The generated pass body calls this before each routine. */
void port_wide_pass_routine(void) { scene_wide_pass_routine(); }

void port_wide_pass_report(void)
{
    scene_wide_pass_report();
    if (passes)
        fprintf(stderr, "[wide pass] %llu passes, %llu abandoned%s\n", (unsigned long long)passes,
                (unsigned long long)abandoned,
                check_mode > 0 ? (check_failures ? ", CHECK FAILED" : ", every pass left no trace") : "");
}
