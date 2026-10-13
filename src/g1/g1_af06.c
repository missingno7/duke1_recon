extern int d_009d;
extern int d_009f;
extern char far *d_637a;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
/*@body*/
void pascal g1_af06(int a2, int a1, int a0)
{
    register int row;
    register int col;

    col = a1;
    row = a2 * 0x140;
    row += 0x9600;
    if (g1_326e(a1, a0 - 0x80) == 0)
        asm_0424(d_637a + row, col - d_009d, (a0 - d_009f) >> 3);
    if (g1_326e(col, a0) == 0)
        asm_0424(d_637a + row + 0xa0, col - d_009d, ((a0 - d_009f) >> 3) + 0x10);
}
