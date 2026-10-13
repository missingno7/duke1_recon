#include <dos.h>
extern char far *d_a0bb;
void asm_05eb(int page);
void asm_05f7(int page);
void g2_3114(void) {}
/*@body*/
void g2_3568(void)
{
    register int i;
    char far *video = (char far *)MK_FP(0xa000, 0);

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb[i];
    }
    outport(0x3c4, 0x0202);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb[i + 8000];
    }
    outport(0x3c4, 0x0402);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb[i + 16000];
    }
    outport(0x3c4, 0x0802);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb[i + 24000];
    }
    asm_05f7(0);
}
