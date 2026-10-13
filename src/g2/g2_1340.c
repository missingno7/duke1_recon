#include <dos.h>
extern char d_a0fa;
extern char far *d_a0fb;
void asm_0424(char far *bitmap, int a0, int a1);
/*@body*/
void pascal g2_1340(register int a0, register int a1)
{
    char x;
    char y;

    d_a0fa = 0;
    x = inportb(0x201) & 0x10;
    y = inportb(0x201) & 0x20;
    while (d_a0fa == 0 && x != 0 && y != 0) {
        x = inportb(0x201) & 0x10;
        y = inportb(0x201) & 0x20;
        asm_0424(d_a0fb + 0x3520, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb + 0x35c0, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb + 0x3660, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb + 0x3700, a0, a1 * 8);
        delay(5);
    }
    asm_0424(d_a0fb + 0x37a0, a0, a1 * 8);
}
