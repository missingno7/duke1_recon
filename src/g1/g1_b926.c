extern int d_009d;
extern int d_009f;
extern char far *d_637a_;
extern int d_d146_;
char pascal g1_326e(int a0, int a1) {}
void asm_0424(char far *bitmap, int a0, int a1);
/*@body*/
void pascal g1_b926(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x140 + 0xa140;
    if (g1_326e(a1, a2 - 0x80) == 0) {
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1 + 2, a2 - 0x80) == 0) {
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 + 2 - d_009d,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1, a2) == 0) {
        asm_0424(d_637a_ + 0xa000,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
    if (g1_326e(a1 + 2, a2) == 0) {
        asm_0424(d_637a_ + 0xa0a0,
                 a1 + 2 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    } else {
        d_d146_ = 0;
    }
}


