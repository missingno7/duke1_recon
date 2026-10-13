extern int d_009d;
extern int d_009f;
extern char d_6379_;
extern char far *d_637a_;
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void pascal g1_b292(int a0, register int a1, register int a2)
{
    if (a0 < 2) {
        if (g1_326e(a1, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xa8c0,
                     a1 - d_009d,
                     (a2 - d_009f) >> 3);
        if (g1_326e(a1 + 2, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xa960,
                     a1 + 2 - d_009d,
                     (a2 - d_009f) >> 3);
    } else {
        if (g1_326e(a1, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xac80,
                     a1 - d_009d,
                     (a2 - d_009f) >> 3);
        if (g1_326e(a1 + 2, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xad20,
                     a1 + 2 - d_009d,
                     (a2 - d_009f) >> 3);
    }

    switch (a0) {
    case 0:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xaa00,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xaaa0,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    case 1:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xab40,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xabe0,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    case 2:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xadc0,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xae60,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    case 3:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xaf00,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xafa0,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    }

    if (g1_3513(a1, a2) != 0)
        d_6379_ = 1;
}
