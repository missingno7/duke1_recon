#include <dos.h>
void asm_05eb(int a0);
void asm_02ad(int a0, int a1);
void g2_29a2(void) {}    /* near-call stub */
/*@body*/
void g2_2ab9(void)
{
    register int si;
    register int di;

    di = 0;
    outport(0x3ce, 0x0105);
    g2_29a2();
    do {
        ++di;
        asm_05eb(di - 1);
        asm_02ad(0x3080, 0);
        asm_02ad(0x30a0, 0x001c);
        asm_02ad(0x30c0, 0x1b9c);
        asm_02ad(0x30e0, 0x1b80);
        asm_02ad(0x3100, 0x001e);
        asm_02ad(0x3100, 0x0020);
        asm_02ad(0x3100, 0x0022);
        asm_02ad(0x3100, 0x0024);
        asm_02ad(0x3120, 0x0026);
        asm_02ad(0x3160, 0x1ba6);
        for (si = 0x0280; si < 0x1b80; si += 0x0280)
            asm_02ad(0x3140, si + 0x0026);
        asm_02ad(0x3100, 0x141e);
        asm_02ad(0x3100, 0x0c9e);
        asm_02ad(0x3100, 0x1420);
        asm_02ad(0x3100, 0x0ca0);
        asm_02ad(0x3100, 0x1422);
        asm_02ad(0x3100, 0x0ca2);
        asm_02ad(0x3100, 0x1424);
        asm_02ad(0x3100, 0x0ca4);
        asm_02ad(0x31e0, 0x1426);
        asm_02ad(0x31e0, 0x0ca6);
        asm_02ad(0x3100, 0x1b9e);
        asm_02ad(0x3100, 0x1ba0);
        asm_02ad(0x3100, 0x1ba2);
        asm_02ad(0x3100, 0x1ba4);
        asm_02ad(0x3100, 0x065e);
        asm_02ad(0x3480, 0x0660);
        asm_02ad(0x34a0, 0x0662);
        asm_02ad(0x3100, 0x0664);
        asm_02ad(0x34c0, 0x0020);
        asm_02ad(0x34e0, 0x0022);
        asm_02ad(0x33c0, 0x141f);
        asm_02ad(0x33e0, 0x1421);
        asm_02ad(0x3400, 0x1423);
        asm_02ad(0x3420, 0x0c9f);
        asm_02ad(0x3440, 0x0ca1);
        asm_02ad(0x3460, 0x0ca3);
        asm_02ad(0x31e0, 0x0666);
    } while (di == 1);
}
