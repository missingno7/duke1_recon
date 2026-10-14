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
