typedef struct Record {
    int f[4];
} Record;
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_0720;
extern int d_5319;
extern int d_5548;
extern char d_554f;
extern char d_5550;
extern char d_5551;
extern char d_5552;
extern char d_5a11;
extern char d_5c6a;
extern unsigned int far *d_7729;
extern char far *d_a0fb;
extern char d_c68c;
extern Record d_d157[];
extern Record d_b9de[];
void g2_0e98(void);
void asm_0424(char far *a0, int a1, int a2);
void g2_1b19(void);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void g1_bb9f(void) {}
void pascal g1_0042(int a0) {}
void pascal g1_0b85(long a0) {}
/*@body*/
void g1_bdd9(void)
{
    register int i;
    register int j;
    Record far *p;

    if (d_0437 == 0)
        ++d_0720;
    if (d_0720 == 0x140)
        d_0720 = 0;

    for (j = 0; j < d_5548; ++j) {
        p = &d_d157[j];
        if (g1_326e(p->f[1], p->f[2]))
            continue;

        if (d_5a11 != 0 && g1_3513(p->f[1], p->f[2])) {
            d_5a11 = 0;
            g2_0e98();
        }
        if (g1_3513(p->f[1], p->f[2]) != 0 &&
            d_c68c != 0 && p->f[0] != 0) {
            if ((d_554f != 0 && p->f[0] == 0x140) ||
                (d_5550 != 0 && p->f[0] == 0x1e0) ||
                (d_5551 != 0 && p->f[0] == 0x280) ||
                (d_5552 != 0 && p->f[0] == 0x320)) {
                for (i = 0; i < d_5319; ++i) {
                    if (d_b9de[i].f[0] != p->f[0] - 0xa0)
                        continue;
                    d_b9de[i].f[3] = 1;
                    *(d_7729 + d_b9de[i].f[2] + (d_b9de[i].f[1] >> 1) - 1) =
                        *(d_7729 + d_b9de[i].f[2] + (d_b9de[i].f[1] >> 1) - 2);
                }

                switch (p->f[0] - 0xa0) {
                case 0xa0:
                    d_554f = 0;
                    break;
                case 0x140:
                    d_5550 = 0;
                    break;
                case 0x1e0:
                    d_5551 = 0;
                    break;
                case 0x280:
                    d_5552 = 0;
                    break;
                }
                g1_bb9f();
                p->f[0] = 0;
                g1_0042(0x1f);
                g1_0b85(1000L);
                continue;
            }
            if (d_5c6a != 0)
                g2_1b19();
        }
        if (p->f[0] == 0) {
            asm_0424(d_a0fb + 0x5460 + p->f[3],
                     p->f[1] - d_009d,
                     ((p->f[2] - d_009f) >> 3) + 0x10);
        } else if (d_0720 % 2 != 0) {
            asm_0424(d_a0fb + 0x5500,
                     p->f[1] - d_009d,
                     ((p->f[2] - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb + 0x5460 + p->f[0],
                     p->f[1] - d_009d,
                     ((p->f[2] - d_009f) >> 3) + 0x10);
        }
    }
}









