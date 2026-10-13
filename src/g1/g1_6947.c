extern int d_009d;
extern int d_009f;
extern int d_02fd[];
extern int d_034d[];
extern int d_0437;
extern int d_06e3;
extern int d_5310;
extern char d_6379;
extern char far* d_637a;
extern int d_abd2;
extern int d_abd4[];
extern int d_abe6;
extern int d_b09c[];
extern int d_b0ae;
extern int d_b636;
extern int d_d249[];
void asm_0424(char far* a0, int a1, int a2);
void pascal g1_0b85(long a0) {}
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_6947(void)
{
    register int i;
    register int active;

    active = 1;
    if (d_b636 != 0) {
        for (i = active; i < 10; ++i) {
            d_abd4[i - 1] = d_abd4[i];
            d_b09c[i - 1] = d_b09c[i];
            if (d_d249[i] != 0)
                active = 0;
        }
        if (active != 0) {
            d_b636 = 0;
            g1_0b85(10000L);
            d_5310 = 1;
            return;
        }
    } else {
        return;
    }

    d_abe6 += d_02fd[d_abd2];
    d_b0ae += d_034d[d_abd2] << 6;

    for (i = 1; i < 10; ++i) {
        if (g1_326e(d_abd4[i], d_b09c[i]) == 0 && d_d249[i] != 0) {
            asm_0424(d_637a + d_06e3 + 0x4b00,
                     d_abd4[i] - d_009d,
                     ((d_b09c[i] - d_009f) >> 3) + 0x10);
            if (g1_3513(d_abd4[i], d_b09c[i]) != 0)
                d_6379 = 1;
        }

        if (d_0437 != 0)
            d_06e3 += 0xa0;
        if (d_06e3 == 0x460)
            d_06e3 = 0;
        if (d_d249[i] != 0 &&
            g1_3558(d_abd4[i], d_b09c[i] - 0x80) != 0) {
            g1_2b86(3, d_abd4[i], d_b09c[i]);
            g1_0b85(1000L);
            g1_0042(10);
            g1_314c(d_abd4[i], d_b09c[i] - 0x80);
            d_d249[i] = 0;
        }
    }

    ++d_abd2;
    if (d_abd2 == 0x27)
        d_abd2 = 0;
}
