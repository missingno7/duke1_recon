#include "pc_internal.h"
#include <string.h>

#define PC_VECTOR_COUNT 256
#define PC_KEY_QUEUE 64

SDL_Mutex *pc_irq_mutex;
SDL_Condition *pc_irq_condition;
unsigned pc_interrupts_disabled;
unsigned pc_active_interrupts;
SDL_ThreadID pc_game_thread_id;

static pc_isr vectors[PC_VECTOR_COUNT];
static uint32_t delivery_counts[PC_VECTOR_COUNT];
static SDL_Thread *timer_thread;
static SDL_AtomicInt timer_running;
static uint8_t pending_keys[PC_KEY_QUEUE];
static unsigned pending_read;
static unsigned pending_write;
static _Thread_local unsigned inside_interrupt;

static void pc_noop_isr(void) {}

int pc_interrupt_init(void) {
    pc_irq_mutex = SDL_CreateMutex();
    pc_irq_condition = SDL_CreateCondition();
    if (!pc_irq_mutex || !pc_irq_condition) return 0;
    memset(vectors, 0, sizeof(vectors));
    memset(delivery_counts, 0, sizeof(delivery_counts));
    pc_interrupts_disabled = 0;
    pc_active_interrupts = 0;
    pending_read = pending_write = 0;
    SDL_SetAtomicInt(&timer_running, 1);
    return 1;
}

pc_isr pc_getvect(int vector) {
    pc_isr result = pc_noop_isr;
    if (vector < 0 || vector >= PC_VECTOR_COUNT) return result;
    if (pc_irq_mutex) SDL_LockMutex(pc_irq_mutex);
    if (vectors[vector]) result = vectors[vector];
    if (pc_irq_mutex) SDL_UnlockMutex(pc_irq_mutex);
    return result;
}

void pc_setvect(int vector, pc_isr handler) {
    if (vector < 0 || vector >= PC_VECTOR_COUNT) return;
    if (pc_irq_mutex) SDL_LockMutex(pc_irq_mutex);
    vectors[vector] = handler;
    delivery_counts[vector] = 0;
    if (pc_irq_mutex) SDL_UnlockMutex(pc_irq_mutex);
    pc_trace(PC_TRACE_VECTORS, "vector %d <- %s", vector, handler ? "handler" : "default");
}

static int invoke_vector(int vector) {
    pc_isr handler = pc_noop_isr;
    uint32_t delivery_count;
    if (vector < 0 || vector >= PC_VECTOR_COUNT || !pc_irq_mutex) return 0;
    SDL_LockMutex(pc_irq_mutex);
    if (pc_interrupts_disabled != 0) {
        SDL_UnlockMutex(pc_irq_mutex);
        return 0;
    }
    if (vectors[vector]) handler = vectors[vector];
    ++pc_active_interrupts;
    delivery_count = ++delivery_counts[vector];
    SDL_UnlockMutex(pc_irq_mutex);

    if (delivery_count <= 5) pc_trace(PC_TRACE_VECTORS, "vector %d delivered (%u)", vector, delivery_count);

    ++inside_interrupt;
    handler();
    --inside_interrupt;

    SDL_LockMutex(pc_irq_mutex);
    if (pc_active_interrupts) --pc_active_interrupts;
    SDL_BroadcastCondition(pc_irq_condition);
    SDL_UnlockMutex(pc_irq_mutex);
    return 1;
}

static void dispatch_pending_keys(void) {
    for (;;) {
        uint8_t code;
        SDL_LockMutex(pc_irq_mutex);
        if (pc_interrupts_disabled || pending_read == pending_write) {
            SDL_UnlockMutex(pc_irq_mutex);
            return;
        }
        code = pending_keys[pending_read];
        pending_read = (pending_read + 1) % PC_KEY_QUEUE;
        SDL_UnlockMutex(pc_irq_mutex);
        pc_outportb(0x60, code);
        if (!invoke_vector(9)) {
            SDL_LockMutex(pc_irq_mutex);
            pending_read = (pending_read + PC_KEY_QUEUE - 1) % PC_KEY_QUEUE;
            pending_keys[pending_read] = code;
            SDL_UnlockMutex(pc_irq_mutex);
            return;
        }
    }
}

void pc_deliver_vector(int vector) {
    (void)invoke_vector(vector);
}

void pc_disable(void) {
    if (!pc_irq_mutex) return;
    SDL_LockMutex(pc_irq_mutex);
    /* CLI: a flag, not a nesting count - the game pairs disable/enable loosely,
       which is harmless on the CPU because STI always re-enables. */
    pc_interrupts_disabled = 1;
    while (!inside_interrupt && pc_active_interrupts != 0) {
        SDL_WaitCondition(pc_irq_condition, pc_irq_mutex);
    }
    SDL_UnlockMutex(pc_irq_mutex);
}

void pc_enable(void) {
    int drain = 0;
    if (!pc_irq_mutex) return;
    SDL_LockMutex(pc_irq_mutex);
    pc_interrupts_disabled = 0;                      /* STI */
    drain = inside_interrupt == 0;
    SDL_BroadcastCondition(pc_irq_condition);
    SDL_UnlockMutex(pc_irq_mutex);
    if (drain) dispatch_pending_keys();
}

void pc_keyboard_scancode(uint8_t scan_code) {
    pc_outportb(0x60, scan_code);
    if (!invoke_vector(9)) {
        SDL_LockMutex(pc_irq_mutex);
        unsigned next = (pending_write + 1) % PC_KEY_QUEUE;
        if (next != pending_read) {
            pending_keys[pending_write] = scan_code;
            pending_write = next;
        }
        SDL_UnlockMutex(pc_irq_mutex);
    }
}

static int timer_worker(void *unused) {
    const uint64_t frequency = SDL_GetPerformanceFrequency();
    uint64_t next_tick = SDL_GetPerformanceCounter();
    (void)unused;
    while (SDL_GetAtomicInt(&timer_running)) {
        uint32_t divisor = atomic_load(&pc_pit0_divisor);
        if (!divisor) divisor = 65536u;
        double interval = ((double)divisor / 1193182.0) * (double)frequency;
        next_tick += (uint64_t)(interval > 1.0 ? interval : 1.0);
        for (;;) {
            uint64_t now = SDL_GetPerformanceCounter();
            if (now >= next_tick || !SDL_GetAtomicInt(&timer_running)) break;
            double remaining_ms = (double)(next_tick - now) * 1000.0 / (double)frequency;
            if (remaining_ms > 2.0) SDL_Delay((Uint32)(remaining_ms - 1.0));
            else SDL_Delay(1);
        }
        if (SDL_GetAtomicInt(&timer_running)) pc_deliver_vector(8);
        uint64_t now = SDL_GetPerformanceCounter();
        if (now > next_tick + frequency / 10u) next_tick = now;
    }
    return 0;
}

void pc_interrupt_start_timer(void) {
    if (!timer_thread && pc_irq_mutex) {
        SDL_SetAtomicInt(&timer_running, 1);
        timer_thread = SDL_CreateThread(timer_worker, "duke-pit", NULL);
        if (!timer_thread) SDL_Log("Could not start PIT timer thread: %s", SDL_GetError());
    }
}

void pc_interrupt_shutdown(void) {
    if (timer_thread) {
        SDL_SetAtomicInt(&timer_running, 0);
        SDL_WaitThread(timer_thread, NULL);
        timer_thread = NULL;
    }
    if (pc_irq_condition) SDL_DestroyCondition(pc_irq_condition);
    if (pc_irq_mutex) SDL_DestroyMutex(pc_irq_mutex);
    pc_irq_condition = NULL;
    pc_irq_mutex = NULL;
}
