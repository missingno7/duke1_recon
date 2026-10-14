#include "pc_internal.h"
#include <stdio.h>
#include <string.h>

_Atomic uint32_t pc_pit0_divisor = 65536u;

static uint8_t keyboard_data_latch;
static uint8_t speaker_control = 0x0c;
static uint8_t game_port_latch = 0xf0;
static uint8_t pit0_low_byte;
static unsigned pit0_write_phase;
static unsigned pit0_access_mode = 3;
static uint8_t pit2_low_byte;
static unsigned pit2_write_phase;
static unsigned pit2_access_mode = 3;
static uint8_t pit_control;
static uint8_t text_video_memory[80u * 25u * 2u];

static int is_vga_port(uint16_t port) {
    return (port >= 0x3b0 && port <= 0x3df);
}

uint8_t pc_inportb(uint16_t port) {
    uint8_t value = 0xff;
    if (is_vga_port(port)) {
        value = vga_port_read(port);
    } else {
        switch (port) {
        case 0x40:
        case 0x41:
        case 0x42:
            value = 0;
            break;
        case 0x60:
            value = keyboard_data_latch;
            break;
        case 0x61:
            value = speaker_control;
            break;
        case 0x201:
            /* No joystick is attached: all four button inputs idle high and the
               four axis timing lines have already returned low. */
            value = 0xf0;
            break;
        default:
            value = 0xff;
            break;
        }
    }
    pc_trace(PC_TRACE_PORTS, "IN  %04X -> %02X", (unsigned)port, (unsigned)value);
    return value;
}

uint16_t pc_inport(uint16_t port) {
    uint16_t value = (uint16_t)pc_inportb(port);
    value |= (uint16_t)((uint16_t)pc_inportb((uint16_t)(port + 1)) << 8);
    return value;
}

void pc_outportb(uint16_t port, uint8_t value) {
    pc_trace(PC_TRACE_PORTS, "OUT %04X <- %02X", (unsigned)port, (unsigned)value);
    if (is_vga_port(port)) {
        vga_port_write(port, value);
        return;
    }
    switch (port) {
    case 0x20:
        /* PIC EOI: the host interrupt has already returned. */
        break;
    case 0x40:
        if (pit0_access_mode == 1) {
            atomic_store(&pc_pit0_divisor, value ? value : 256u);
        } else if (pit0_access_mode == 2) {
            atomic_store(&pc_pit0_divisor, value ? ((uint32_t)value << 8) : 65536u);
        } else if (pit0_write_phase == 0) {
            pit0_low_byte = value;
            pit0_write_phase = 1;
        } else {
            uint32_t divisor = (uint32_t)pit0_low_byte | ((uint32_t)value << 8);
            atomic_store(&pc_pit0_divisor, divisor ? divisor : 65536u);
            pit0_write_phase = 0;
        }
        break;
    case 0x42:
        if (pit2_access_mode == 1) {
            pit2_low_byte = value;
            pit2_write_phase = 0;
        } else if (pit2_access_mode == 2) {
            pit2_write_phase = 0;
        } else if (pit2_write_phase == 0) {
            pit2_low_byte = value;
            pit2_write_phase = 1;
        } else {
            pit2_write_phase = 0;
        }
        break;
    case 0x43:
        pit_control = value;
        if ((value & 0xc0u) == 0) {
            pit0_access_mode = (value >> 4) & 3u;
            pit0_write_phase = 0;
        } else if ((value & 0xc0u) == 0x80u) {
            pit2_access_mode = (value >> 4) & 3u;
            pit2_write_phase = 0;
        }
        break;
    case 0x60:
        keyboard_data_latch = value;
        break;
    case 0x61:
        speaker_control = value;
        break;
    case 0x201:
        game_port_latch = value;
        (void)game_port_latch;
        break;
    default:
        break;
    }
}

void pc_outport(uint16_t port, uint16_t value) {
    pc_outportb(port, (uint8_t)value);
    pc_outportb((uint16_t)(port + 1), (uint8_t)(value >> 8));
}

void *pc_mk_fp(uint16_t segment, uint16_t offset) {
    if (segment == 0xb800) {
        if (offset >= sizeof(text_video_memory)) return text_video_memory;
        return &text_video_memory[offset];
    }
    if (segment == 0xa000) {
        fprintf(stderr, "Unsupported direct A000: video pointer reached the platform core; add a port/override for this function.\n");
        fflush(stderr);
        abort();
    }
    fprintf(stderr, "Unsupported real-mode pointer %04X:%04X.\n", (unsigned)segment, (unsigned)offset);
    fflush(stderr);
    abort();
}

