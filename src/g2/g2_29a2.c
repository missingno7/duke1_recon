#include <dos.h>
void asm_02ad(int a0, int a1);
/*@body*/
void g2_29a2(void)
{
    register int si;

    si = 0x280;
    outport(0x3ce, 0x105);
    do {
        asm_02ad(0x3000, si);
        asm_02ad(0x3020, si + 0x1c);
        si += 0x280;
    } while (si < 0x1b80);
    si = 2;
    do {
        asm_02ad(0x3040, si);
        asm_02ad(0x3060, si + 0x1b80);
        si += 2;
    } while (si < 0x1c);
    asm_02ad(0x31c0, 0x141c);
    asm_02ad(0x31c0, 0x065c);
    asm_02ad(0x31c0, 0x0c9c);
    asm_02ad(0x3080, 0);
    asm_02ad(0x30a0, 0x001c);
    asm_02ad(0x30c0, 0x1b9c);
    asm_02ad(0x30e0, 0x1b80);
    asm_02ad(0x3340, 0x1b8b);
    asm_02ad(0x3360, 0x1b8d);
    asm_02ad(0x3380, 0x1b8f);
    asm_02ad(0x33a0, 0x1b91);
}
