/* Exact-width platform and capture hooks visible to generated episode code. */
#ifndef DUKE_GAME_HOOKS_H
#define DUKE_GAME_HOOKS_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PC_SOUND_SOURCE_CENTRE INT16_MIN

typedef void (*pc_isr)(void);

uint8_t pc_inportb(uint16_t port);
uint16_t pc_inport(uint16_t port);
void pc_outportb(uint16_t port, uint8_t value);
void pc_outport(uint16_t port, uint16_t value);
pc_isr pc_getvect(int16_t vector);
void pc_setvect(int16_t vector, pc_isr handler);
void pc_disable(void);
void pc_enable(void);
void pc_spin(void);
void pc_halt(void);
void *pc_mk_fp(uint16_t segment, uint16_t offset);
void *pc_malloc(uint16_t size);
void pc_free(void *block);
void pc_delay(uint16_t milliseconds);
uint32_t pc_coreleft(void);
void pc_textmode(int16_t mode);
void pc_exit(int16_t status);
FILE *pc_fopen(const char *name, const char *mode);
int16_t pc_getw(FILE *stream);
int16_t pc_putw(int16_t word, FILE *stream);
char *pc_ltoa(int32_t value, char *buffer, int16_t base);
char *pc_ultoa(uint32_t value, char *buffer, int16_t base);

void capture_begin_gameplay_frame(int16_t scroll_x, int16_t map_y_offset);
void capture_publish_intermediate_gameplay_frame(int16_t drawing_page);
void pc_capture_set_modal_capture_active(int16_t active);
void capture_snapshot_wide_tiles(const uint16_t *tile_map, int16_t map_y_offset,
                                 uint16_t animation_phase);
void capture_end_tile_strip(void);
int16_t pc_capture_is_world_position_outside_wide_view(int16_t world_x, int16_t world_y,
                                                       int16_t original_result);
int16_t pc_capture_is_world_position_outside_wide_if_active(int16_t world_x, int16_t world_y,
                                                             int16_t original_result);
int16_t blit_planar_sprite_rows_at(uint32_t site, char *src, int16_t x, int16_t y);
void vga_cpu_write(uint16_t offset, uint8_t value);
void platform_show_port_settings_dialog(int16_t episode);
void pc_speaker_set_source_world_x(int16_t world_x, int16_t scroll_x);
void pc_speaker_begin_sound(void);
void port_wide_presentation_pass(void (*pass)(void), unsigned char *tile_map, uint16_t tile_map_size);
void port_wide_pass_routine(void);

#ifdef __cplusplus
}
#endif
#endif
