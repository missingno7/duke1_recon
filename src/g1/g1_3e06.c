struct g1_3e06_record { int state, x, y; };
extern struct g1_3e06_record d_6bb2_[];
extern int d_009d;
extern int d_009f;
extern int d_01fe[];
extern int d_053e;
extern int d_4ed8_;
extern unsigned int far *d_7729_;
extern char far *d_a0fb_;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void pascal g1_0b85(long a0) {}
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
/*@body*/
void g1_3e06(void)
{
    register int i;
    struct g1_3e06_record far *p;

    d_4ed8_ = 1;
    for (i = 0; i < d_053e; ++i) {
        p = &d_6bb2_[i];
        if (p->state == 0)
            continue;

        d_4ed8_ = 0;
        if (g1_3558(p->x, p->y) != 0 && p->state == 1) {
            p->state = 2;
            g1_0042(0x1e);
            g1_0b85(200L);
        }

        if (p->state > 1 && p->state < 10) {
            if (p->state == 9) {
                *((&d_7729_[p->y] + (p->x >> 1)) + 0x7f) =
                    *((&d_7729_[p->y] + (p->x >> 1)) + 0xff);
                g1_314c(p->x, p->y + 0x80);
            }

            if (p->state == 3)
                g1_2b86(3, p->x, p->y + 0x80);

            if ((p->state & 1) != 0) {
                if (g1_326e(p->x, p->y + 0x80) == 0)
                    asm_0424(d_a0fb_ + 0xaa0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x20);
            }
            ++p->state;
        }

        if (p->state == 10) {
            p->y -= 0x80;
            if (p->y % 0x100 != 0) {
                if (g1_326e(p->x, p->y + 0x80) == 0)
                    asm_0424(d_a0fb_ + 0xa00,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x20);
                if (g1_326e(p->x, p->y + 0x100) == 0)
                    asm_0424(d_a0fb_ + 0xaa0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x30);
            }
        }

        if (g1_326e(p->x, p->y - 0x180) == 0)
            asm_0424(d_a0fb_ + 0x6e0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) - 0x20);
        if (g1_326e(p->x, p->y - 0xfe) == 0)
            asm_0424(d_a0fb_ + 0x780,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) - 0x10);
        if (g1_326e(p->x, p->y - 0x80) == 0)
            asm_0424(d_a0fb_ + 0x780,
                     p->x - d_009d,
                     (p->y - d_009f) >> 3);

        if (g1_326e(p->x, p->y) == 0)
            asm_0424(d_a0fb_ + 0x820,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (g1_326e(p->x - 2, p->y) == 0)
            asm_0424(d_a0fb_ + 0x8c0,
                     p->x - d_009d - 2,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (g1_326e(p->x + 2, p->y) == 0)
            asm_0424(d_a0fb_ + 0x960,
                     p->x - d_009d + 2,
                     ((p->y - d_009f) >> 3) + 0x10);

        if (g1_3714(p->x, p->y - 0x200) == 0)
            continue;
        if (p->state != 10)
            continue;

        g1_314c(p->x - 3, p->y - 0x200);
        g1_314c(p->x + 2, p->y - 0x180);
        g1_314c(p->x + 1, p->y - 0x180);
        g1_314c(p->x - 1, p->y - 0x100);
        g1_314c(p->x, p->y - 0x80);
        p->state = 0;
        *((&d_7729_[p->y] + (p->x >> 1)) - 0x201) =
            *((&d_7729_[p->y] + (p->x >> 1)) - 0x181);
    }
}

