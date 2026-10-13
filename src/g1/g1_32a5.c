struct t_5320 { int f[15]; };
extern struct t_5320 d_5320_[];
extern int d_009d;
extern int d_009f;
extern int d_043e;
extern int d_0440[];
extern int d_0442[];
extern int d_0476[];
extern int d_0478[];
extern int d_04ac[];
extern int d_04ae[];
extern int d_04e2[];
extern int d_04e4[];
extern char far *d_a0fb_;
char pascal g1_326e(int a0, int a1) { return 0; }
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_32a5(void)
{
    register int i;
    struct t_5320 far *p;

    for (i = 0; i < d_043e; ++i) {
        p = &d_5320_[i];
        if (p->f[0] != 0) {
            if (p->f[0] != 0) {
                p->f[1] += d_0440[p->f[0]];
                p->f[2] += d_0442[p->f[0]];
                p->f[3] += d_0476[p->f[0]];
                p->f[4] += d_0478[p->f[0]];
                p->f[5] += d_04ac[p->f[0]];
                p->f[6] += d_04ae[p->f[0]];
                p->f[7] += d_04e2[p->f[0]];
                p->f[8] += d_04e4[p->f[0]];

                if (g1_326e(p->f[1], p->f[2]) == 0 &&
                    g1_326e(p->f[1], p->f[2] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[9],
                             p->f[1] - d_009d,
                             ((p->f[2] - d_009f) >> 3) + 0x10);
                }
                if (g1_326e(p->f[3], p->f[4]) == 0 &&
                    g1_326e(p->f[3], p->f[4] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[10],
                             p->f[3] - d_009d,
                             ((p->f[4] - d_009f) >> 3) + 0x10);
                }
                if (g1_326e(p->f[5], p->f[6]) == 0 &&
                    g1_326e(p->f[5], p->f[6] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[11],
                             p->f[5] - d_009d,
                             ((p->f[6] - d_009f) >> 3) + 0x10);
                }
                if (g1_326e(p->f[7], p->f[8]) == 0 &&
                    g1_326e(p->f[7], p->f[8] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[12],
                             p->f[7] - d_009d,
                             ((p->f[8] - d_009f) >> 3) + 0x10);
                }
                p->f[0] += 2;
                if (p->f[0] == 0x17)
                    p->f[0] = 0;
            }
        }
    }
}
