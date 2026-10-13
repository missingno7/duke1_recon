struct g1_899e_record { int state, x; unsigned int y; };
extern struct g1_899e_record d_7063_[];
extern int d_009d;
extern int d_009f;
extern int d_05d6;
extern int d_06f5;
extern int d_4ed4_;
extern char d_5ec8_;
extern char far *d_a0fb_;
void g2_165e(void);
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void g1_0a0e(void) {}
void pascal g1_0042(int a0) {}
/*@body*/
void g1_899e(void)
{
    register unsigned int si;
    struct g1_899e_record far *p;

    d_06f5 += 0xa0;
    if (d_06f5 == 0x5a0)
        d_06f5 = 0;

    for (si = 0; si < d_05d6; ++si) {
        p = &d_7063_[si];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;

        if (p->state == 1) {
            if (g1_3558(p->x, p->y) != 0) {
                g1_314c(p->x, p->y);
                p->state = 2;
                if (g1_3714(p->x, p->y + 0x80) == 0) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
            }
        }

        if (p->state == 2 && g1_3513(p->x, p->y) != 0) {
            p->state = 0;
            d_4ed4_ = 9;
            g1_0b85(1000L);
            g1_2a40(0x3c0, p->x, p->y);
            g1_0a0e();
            g1_0042(4);
            if (d_5ec8_ != 0) {
                d_5ec8_ = 0;
                g2_165e();
            }
            continue;
        }

        if (p->state == 1) {
            asm_0424(d_a0fb_,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb_ + d_06f5 + 0x2e40,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}
