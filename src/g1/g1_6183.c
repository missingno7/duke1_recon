extern int d_009d;
extern int d_009f;
extern char far *d_637a;
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_326e(int a0, int a1) {}
/*@body*/
void pascal g1_6183(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x280 + 0x3c00;
    if (g1_326e(a1, a2 - 0x80) == 0) {
        asm_0424(d_637a + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1 + 2, a2 - 0x80) == 0) {
        asm_0424(d_637a + offset + 0xa0,
                 a1 - d_009d + 2,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1, a2) == 0) {
        asm_0424(d_637a + offset + 0x140,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
    if (g1_326e(a1 + 2, a2) == 0) {
        asm_0424(d_637a + offset + 0x1e0,
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
}

