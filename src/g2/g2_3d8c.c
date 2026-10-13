/* Apparently draws a framed box from border tiles (asm_02ad) at column a2, row a1
   (pascal; parameters are listed in declaration order a2, a1, a0). */
#include <dos.h>
extern char d_6e0a_;
void asm_05eb(int page);
void asm_02ad(int source, int offset);
/*@body*/
void pascal g2_3d8c(int a2, int a1, int a0)
{
    register int si;
    register int di;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    if (a2 == 2)
        asm_05eb(d_6e0a_);
    else
        asm_05eb(0);

    for (si = 0; a0 * 16 * 40 > si; si += 640) {
        asm_02ad(0x32c0, a1 * 16 * 40 + (si + a2));
        asm_02ad(0x32e0, a1 * 16 * 40 + (si + a2) + 24);
    }
    for (di = 2; di < 23; di += 2)
        for (si = 0; a0 * 16 * 40 > si; si += 640)
            asm_02ad(0x3220, a1 * 16 * 40 + a2 + di + si);

    asm_02ad(0x3240, a1 * 16 * 40 + a2);
    asm_02ad(0x3260, a1 * 16 * 40 + a2 + 24);
    asm_02ad(0x3280, (a1 * 16 * 40 + a2) + a0 * 16 * 40);
    asm_02ad(0x32a0, (a1 * 16 * 40 + a2) + a0 * 16 * 40 + 24);

    for (di = 0; di < 22; di += 2) {
        asm_02ad(0x3300, a1 * 16 * 40 + (di + a2) + 2);
        asm_02ad(0x3320, (a0 * 16 * 40 + di + a2) + a1 * 16 * 40 + 2);
    }
}
