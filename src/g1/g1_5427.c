extern int d_009d;
extern int d_009f;
extern char d_6379_;
extern char far *d_637a_;
void asm_0424(char far *bitmap, int a0, int a1);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void pascal g1_5427(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x140 + 0x1540;

    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_326e(a1 + 2, a2) == 0)
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_3513(a1, a2) || g1_3513(a1 + 2, a2))
        d_6379_ = 1;
}
