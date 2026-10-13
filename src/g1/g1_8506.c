struct g1_8506_record { int state, x, y; };
extern struct g1_8506_record d_7cac_[];
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_05d0;
extern int d_06f3;
extern char far *d_a0fb_;
void asm_0424(char far *a0, int a1, int a2);
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
char pascal g1_326e(int a0, int a1) { return 0; }
void pascal g1_2e64(int a0, int a1) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_8506(void)
{
    register int i;
    struct g1_8506_record far *p;

    for (i = 0; i < d_05d0; i++) {
        p = &d_7cac_[i];
        if (p->state == 0)
            continue;

        if (p->state == 1) {
            if (g1_3714(p->x, p->y + 128) == 0)
                p->y += 64;
            if (g1_326e(p->x, p->y) == 0) {
                asm_0424(d_a0fb_ + 0x3e80,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                if (g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    if (g1_3714(p->x, p->y + 128) == 0) {
                        g1_0b85(0x1f4L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                    p->state = 2;
                }
            }
            continue;
        }

        if (d_0437 == 0)
            d_06f3 += 0xa0;
        if (d_06f3 == 0x1e0)
            d_06f3 = 0;

        if (g1_3714(p->x, p->y - 128) == 0)
            p->y -= 8;
        if (g1_3558(p->x, p->y - 128) != 0 || g1_3714(p->x, p->y - 128) != 0) {
            if (g1_326e(p->x, p->y - 128) == 0)
                asm_0424(d_a0fb_ + 0x2da0,
                         p->x - d_009d,
                         (p->y - d_009f) >> 3);
            p->state = 0;
            g1_2e64(p->x, p->y - 128);
            continue;
        }
        if (g1_326e(p->x, p->y - 128) == 0)
            asm_0424(d_a0fb_ + 0x2b20,
                     p->x - d_009d,
                     (p->y - d_009f) >> 3);
        if (g1_326e(p->x, p->y) == 0)
            asm_0424(d_a0fb_ + d_06f3 + 0x2bc0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (g1_3513(p->x, p->y) != 0) {
            g1_0b85(10000L);
            g1_2a40(0x780, p->x, p->y - 128);
            g1_0042(3);
            p->state = 0;
        }
    }
}





