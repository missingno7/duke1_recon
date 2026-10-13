#include <dos.h>
extern char far *d_c28f;
void asm_05eb(int a0);
void asm_05f7(int a0);
void g2_3114(void) {}
/*@body*/
void g2_36c1(void)
{
    char far *vram;
    register int si;

    vram = MK_FP(0xa000, 0);
    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f[si];
    outport(0x3c4, 0x0202);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f[si + 0x1f40];
    outport(0x3c4, 0x0402);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f[si + 0x3e80];
    outport(0x3c4, 0x0802);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f[si + 0x5dc0];
    asm_05f7(0);
}
