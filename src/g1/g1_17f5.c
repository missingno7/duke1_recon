#include <dos.h>
extern char d_0644;
extern int d_4ed2_;
extern int d_5002_;
extern char far *d_5ec4_;
extern char d_d4bf_;
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void g1_17f5(int a0, int a1, int a2, int a3)
{
    register int offset;

    offset = a0 * 4 * 0xa0;
    if (d_4ed2_ >= 4)
        return;
    if (d_5002_ != 0)
        return;
    if (d_d4bf_ > 0)
        --d_d4bf_;
    if (a2 >= 0x20 && d_d4bf_ % 2 == 0) {
        asm_0424((d_5ec4_+ offset), a1 - 1, a2 - 0x10);
        asm_0424((d_5ec4_+ offset + 0xa0), a1 + 1, a2 - 0x10);
    }
    if (a2 >= 0x10) {
        if (d_d4bf_ % 2 == 0) {
            asm_0424((d_5ec4_+ offset + 0x140), a1 - 1, a2);
            asm_0424((d_5ec4_+ offset + 0x1e0), a1 + 1, a2);
        }
    } else {
        d_0644 = 1;
    }
}


