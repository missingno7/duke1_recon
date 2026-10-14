/* Port writes for the self-tests: straight to the emulated VGA, as pc_io.c routes them. */
#include <stdint.h>

int vga_port_write(uint16_t port, uint8_t value);

void test_outport(uint16_t port, uint16_t value)
{
    vga_port_write(port, (uint8_t)value);
    vga_port_write((uint16_t)(port + 1u), (uint8_t)(value >> 8));
}
