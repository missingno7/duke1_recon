extern int d_009d;
extern int d_009f;
extern char far *d_637a;
void asm_0424(char far *bitmap, int row, int column);
char pascal g1_326e(int x, int y) {}
void pascal g1_0042(int value) {}
/*@body*/
void pascal g1_7f4a(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x280 + 0x6e00;
    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a + offset, a1 - d_009d, ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 2, a2) == 0)
        asm_0424(d_637a + offset + 0xa0, a1 - d_009d + 2, ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 4, a2) == 0)
        asm_0424(d_637a + offset + 0x140, a1 - d_009d + 4, ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 6, a2) == 0) {
        asm_0424(d_637a + offset + 0x1e0, a1 - d_009d + 6, ((a2 - d_009f) >> 3) + 0x10);
        g1_0042(0x16);
    }
}
