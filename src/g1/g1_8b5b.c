struct record {
    int state;
    int x;
    int y;
};

extern struct record d_c691_[];
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern int d_05d8;
extern int d_531c_;
extern char d_6379_;
extern char far *d_a0fb_;

void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_0042(int a0) {}
int g1_3513(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}

/*@body*/
void g1_8b5b(void)
{
    struct record far *p;
    register int i;

    d_531c_ = 1;
    for (i = 0; i < d_05d8; ++i) {
        p = &d_c691_[i];
        if (p->state == 0)
            continue;
        d_531c_ = 0;
        if (g1_326e(p->x, p->y) && g1_326e(p->x, p->y)) {
            if (p->state > 15) {
                p->state = 0;
                continue;
            } else {
                continue;
            }
        } else {
            if (p->state > 1) {
                if (g1_3714(p->x + 1, p->y + 0x80)) {
                    g1_314c(p->x + 1, p->y);
                    g1_2e64(p->x + 1, p->y);
                    p->state = 0;
                    continue;
                }
                ++p->state;
            }
            if (p->state < 2) {
                if (p->x - 1 <= d_0099 + d_009d &&
                    p->x + 3 >= d_0099 + d_009d &&
                    ((d_009b >> 4) << 7) + d_009f - p->y < 0x400 &&
                    ((d_009b >> 4) << 7) + d_009f - p->y > 0)
                    p->state = 2;
            }
            if (p->state == 16)
                g1_0042(0x20);
            if (p->state > 15) {
                p->y += 0x60;
                if (g1_3513(p->x, p->y) || g1_3513(p->x + 2, p->y))
                    d_6379_ = 1;
                if (g1_3558(p->x, p->y - 0x40) ||
                    g1_3558(p->x + 2, p->y - 0x40)) {
                    g1_314c(p->x + 1, p->y);
                    g1_2e64(p->x + 1, p->y);
                    g1_2b86(1, p->x + 1, p->y);
                    g1_0b85(0x1f4L);
                    g1_2a40(0x280, p->x + 1, p->y);
                    p->state = 0;
                    continue;
                }
            }
        }
        if (p->state == 1 || p->state >= 15) {
            if (!g1_326e(p->x, p->y))
                asm_0424(d_a0fb_ + 0x33e0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (!g1_326e(p->x + 2, p->y))
                asm_0424(d_a0fb_ + 0x3480,
                         p->x - d_009d + 2,
                         ((p->y - d_009f) >> 3) + 0x10);
        }
        if (p->state >= 15)
            continue;
        if (!g1_326e(p->x, p->y))
            asm_0424(d_a0fb_ + 0x33e0,
                     p->x - d_009d,
                     (p->state % 2) + ((p->y - d_009f) >> 3) + 0x10);
        if (g1_326e(p->x + 2, p->y))
            continue;
        asm_0424(d_a0fb_ + 0x3480,
                 p->x - d_009d + 2,
                 (p->state % 2) + ((p->y - d_009f) >> 3) + 0x10);
    }
}
