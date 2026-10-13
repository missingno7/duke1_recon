struct G1_4D42_RECORD { int f0, f1, f2, f3, f4, f5; };
extern int d_009d;
extern int d_009f;
extern int d_0650[];
extern char d_6379;
extern char far *d_637a;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
#define G1_4D42_ROW(i) (*((struct G1_4D42_RECORD *)&d_0650[(i) * 6]))
/*@body*/
void pascal g1_4d42(int a2, int p1, register int a0)
{
    register int a1 = p1;
    if (d_0650[a2 * 6] > 0 && g1_326e(a1, a0 - 256) == 0)
        asm_0424(d_637a + d_0650[a2 * 6] + 0x5a0,
                 a1 - d_009d,
                 ((a0 - d_009f) >> 3) - 16);

    if (d_0650[a2 * 6] > 0 && g1_326e(a1 + 2, a0 - 256) == 0)
        asm_0424(d_637a + G1_4D42_ROW(a2).f1 + 0x5a0,
                 a1 - d_009d + 2,
                 ((a0 - d_009f) >> 3) - 16);

    if (g1_326e(a1, a0 - 128) == 0)
        asm_0424(d_637a + G1_4D42_ROW(a2).f2 + 0x5a0,
                 a1 - d_009d,
                 (a0 - d_009f) >> 3);

    if (g1_326e(a1 + 2, a0 - 128) == 0)
        asm_0424(d_637a + G1_4D42_ROW(a2).f3 + 0x5a0,
                 a1 - d_009d + 2,
                 (a0 - d_009f) >> 3);

    if (g1_326e(a1, a0) == 0)
        asm_0424(d_637a + G1_4D42_ROW(a2).f4 + 0x5a0,
                 a1 - d_009d,
                 ((a0 - d_009f) >> 3) + 16);

    if (g1_326e(a1 + 2, a0) == 0)
        asm_0424(d_637a + G1_4D42_ROW(a2).f5 + 0x5a0,
                 a1 - d_009d + 2,
                 ((a0 - d_009f) >> 3) + 16);

    if (g1_3513(a1 + 1, a0) != 0 || g1_3513(a1 + 1, a0 - 128) != 0)
        d_6379 = 1;
}
