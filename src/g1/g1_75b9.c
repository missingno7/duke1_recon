extern int d_009d;
extern int d_009f;
extern char far *d_637a;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) {}
/*@body*/
void pascal g1_75b9(int row, int horizontal, int vertical)
{
    register int index = row * 0x140 + 0x6180;
    if (g1_326e(horizontal, vertical - 0x80) == 0)
        asm_0424(d_637a + index, horizontal - d_009d,
                 (vertical - d_009f) >> 3);
    if (g1_326e(horizontal, vertical) == 0)
        asm_0424(d_637a + index + 0xa0, horizontal - d_009d,
                 ((vertical - d_009f) >> 3) + 0x10);
}
