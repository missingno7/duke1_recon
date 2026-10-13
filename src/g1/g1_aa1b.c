extern int d_009d;
extern int d_009f;
extern char far *d_637a;
char pascal g1_326e(int a0, int a1) {}
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void pascal g1_aa1b(int a0, register int a1, int a2)
{
    register int offset;

    if (a0 <= 2)
        offset = a0 * 0x140 + 0x4740;
    else
        offset = (a0 - 3) * 0x140 + 0x8e80;

    if (g1_326e(a1, a2 - 0x80) == 0)
        asm_0424(d_637a + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);

    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a + offset + 0xa0,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
}
