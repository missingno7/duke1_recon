/* Wait for a key or joystick button, cycling a 4-frame animation at (x, y). */
#include <dos.h>
extern char d_a0fa;
extern char far *d_a0fb;
extern char d_d56b;
void asm_0424(char far *bitmap, int a0, int a1);
void delay(unsigned int milliseconds);
void g1_1076(void);
/*@body*/
void pascal g2_2870(register int a0, register int a1)
{
    char x = 1;
    char y = 1;

    d_a0fa = 0;
    if (d_d56b != 0) {
        g1_1076();
        x = inportb(0x201) & 0x10;
        y = inportb(0x201) & 0x20;
    }
    while (d_a0fa == 0 && x != 0 && y != 0) {
        if (d_d56b != 0) {
            x = inportb(0x201) & 0x10;
            y = inportb(0x201) & 0x20;
        }
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





