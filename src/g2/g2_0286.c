#include <dos.h>
void asm_05eb(int a0);
void asm_05f7(int a0);
void asm_02ad(int a0, int a1);
/*@body*/
void pascal g2_0286(int a0)
{
    register int si;
    register int di;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    asm_05eb(0);
    asm_05f7(0);
    for (di = 0; di < 25; di++) {
        for (si = 0; si < 20; si++) {
            asm_02ad(a0, si * 2 + di * 640);
        }
    }
}

