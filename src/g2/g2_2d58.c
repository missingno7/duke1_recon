#include <dos.h>
extern char d_6e0a;
void asm_05eb(int page);
void asm_02ad(int source, int offset);
/*@body*/
void pascal g2_2d58(int a0)
{
    register int si;
    register int di;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    if (a0 == 2)
        asm_05eb(d_6e0a);
    else
        asm_05eb(0);

    for (si = 0; si < 10; si++) {
        for (di = a0; di < a0 + 26; di += 2)
            asm_02ad(0x3220, si * 640 + di + 640);
    }

    asm_02ad(0x3240, a0 + 640);
    asm_02ad(0x3260, a0 + 664);
    asm_02ad(0x3280, a0 + 0x1900);
    asm_02ad(0x32a0, a0 + 0x1918);

    for (si = 0x500; si < 0x16a8; si += 640) {
        asm_02ad(0x32c0, si + a0);
        asm_02ad(0x32e0, si + a0 + 24);
    }

    for (si = 0x282; si < 0x298; si += 2) {
        asm_02ad(0x3300, si + a0);
        asm_02ad(0x3320, si + a0 + 0x1680);
    }
}

