#ifndef DUKE_PORT_INTERNAL_H
#define DUKE_PORT_INTERNAL_H

#include "platform.h"
#include <SDL3/SDL.h>
#include <stdatomic.h>
#include <stdint.h>

#define PC_TRACE_PORTS 1u
#define PC_TRACE_VECTORS 2u
#define PC_TRACE_FILES 4u

extern unsigned pc_trace_flags;
extern char pc_data_directory[4096];
extern _Atomic uint32_t pc_pit0_divisor;

/* pc_speaker.c */
int  pc_speaker_init(void);
void pc_speaker_shutdown(void);
void pc_speaker_set_divisor(uint32_t divisor);
void pc_speaker_set_gate(uint8_t port61);
void pc_speaker_set_volume(int percent);
void platform_apply_window_settings(void);
void pc_speaker_set_stereo(int on);
void pc_speaker_set_next_pan(float pan);
void pc_speaker_begin_sound(void);
void pc_speaker_note_game_tick(int tick_counter);
void pc_speaker_note_view_test(int world_x, int scroll_x, int tick_counter);
float pc_speaker_view_pan(int tick_counter);
extern SDL_Mutex *pc_irq_mutex;
extern SDL_Condition *pc_irq_condition;
extern unsigned pc_interrupts_disabled;
extern unsigned pc_active_interrupts;
extern SDL_ThreadID pc_game_thread_id;

void pc_trace(unsigned category, const char *format, ...);
void pc_deliver_vector(int vector);
int pc_interrupt_init(void);
void pc_interrupt_start_timer(void);
void pc_interrupt_shutdown(void);
void pc_keyboard_scancode(uint8_t scan_code);
int pc_is_game_thread(void);
void pc_set_quit_hint(void);

#endif
