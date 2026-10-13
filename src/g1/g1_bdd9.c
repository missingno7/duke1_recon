struct t_b9de { int offset, x, y, alternate; };
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
extern struct t_b9de d_d157[];
extern struct t_b9de d_b9de[];
void g2_0e98(void);
void asm_0424(char far *a0, int a1, int a2);
void g2_1b19(void);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_bb9f(void) {}
void pascal g1_0042(int a0) {}
void pascal g1_0b85(long a0) {}
/*@body*/
void g1_bdd9(void)
{
    register int i;
    register int j;
    struct t_b9de far *p;

    if (d_0437 == 0)
        ++d_0720;
    if (d_0720 == 0x140)
        d_0720 = 0;

    for (j = 0; j < d_5548; ++j) {
        p = &d_d157[j];
        if (g1_326e(p->x, p->y))
            continue;

        if (d_5a11 != 0 && g1_3513(p->x, p->y)) {
            d_5a11 = 0;
            g2_0e98();
        }
        if (g1_3513(p->x, p->y) != 0 &&
            d_c68c != 0 && p->offset != 0) {
            if ((d_554f != 0 && p->offset == 0x140) ||
                (d_5550 != 0 && p->offset == 0x1e0) ||
                (d_5551 != 0 && p->offset == 0x280) ||
                (d_5552 != 0 && p->offset == 0x320)) {
                for (i = 0; i < d_5319; ++i) {
                    if (d_b9de[i].offset != p->offset - 0xa0)
                        continue;
                    d_b9de[i].alternate = 1;
                    *(d_7729 + d_b9de[i].y + (d_b9de[i].x >> 1) - 1) =
                        *(d_7729 + d_b9de[i].y + (d_b9de[i].x >> 1) - 2);
                }

                switch (p->offset - 0xa0) {
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
                p->offset = 0;
                g1_0042(0x1f);
                g1_0b85(1000L);
                continue;
            }
            if (d_5c6a != 0)
                g2_1b19();
        }
        if (p->offset == 0) {
            asm_0424(d_a0fb + 0x5460 + p->alternate,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else if (d_0720 % 2 != 0) {
            asm_0424(d_a0fb + 0x5500,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb + 0x5460 + p->offset,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}









