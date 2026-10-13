#include <dos.h>
extern char far *d_c285;
void asm_05eb(int a0);
void asm_05f7(int a0);
void g2_3114(void) {}
/*@body*/
void g2_315d(void)
{
    char far *video = (char far *)0xa0000000L;
    register int i;

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285[i];
    outport(0x3c4, 0x0202);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285[i + 0x1f40];
    outport(0x3c4, 0x0402);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285[i + 0x3e80];
    outport(0x3c4, 0x0802);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285[i + 0x5dc0];
    asm_05f7(0);
}
