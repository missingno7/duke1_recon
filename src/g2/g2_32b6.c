#include <dos.h>
extern char far *d_b638;
void asm_05eb(int a0);
void asm_05f7(int a0);
void g2_3114(void) {}
/*@body*/
void g2_32b6(void)
{
    char far *screen = (char far *)MK_FP(0xa000, 0);
    register int si;

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638[si];
    outport(0x3c4, 0x0202);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638[si + 0x1f40];
    outport(0x3c4, 0x0402);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638[si + 0x3e80];
    outport(0x3c4, 0x0802);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638[si + 0x5dc0];
    asm_05f7(0);
}
