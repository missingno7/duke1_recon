#include <dos.h>
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern unsigned int far* d_7729_;
void asm_02ad(int a0, int a1);
/*@body*/
void g1_14af(void)
{
    register int si;
    register int di;
    unsigned int far *p;
    int offset;

    si = 0x282 - (d_009d & 1);
    di = 0;
    p = d_7729_ + (d_009d >> 1) + d_009f;
    offset = 0x4000;
    outport(0x3ce, 0x105);
    d_0437 += 0x20;
    if (d_0437 == 0x80)
        d_0437 = 0;
    do {
        if (d_009d & 1) {
            if (*p == 0 || p[1] == 0)
                asm_02ad(offset, si + 1);
            else if (*p == 0x20 || p[1] == 0x20)
                asm_02ad(offset + 0x4100, si + 1);
        } else {
            if (*p == 0)
                asm_02ad(offset, si);
            else if (*p == 0x20)
                asm_02ad(offset + 0x4100, si);
        }
        if (*p > 0x20) {
            if (*p < 0x5e0)
                asm_02ad(*p + d_0437, si);
            else
                asm_02ad(*p, si);
        }
        ++p;
        si += 2;
        if (++di == 14) {
            si += 0x264;
            p += 0x72;
            di = 0;
        } else {
            offset += 0x20;
        }
    } while (si < 0x191c);
    outport(0x3ce, 5);
}





