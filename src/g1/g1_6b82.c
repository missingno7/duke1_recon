struct g1_6b82_record { int state, x, y; };
extern struct g1_6b82_record d_5a12[];
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_05bc;
extern int d_06e7;
extern char d_5554;
extern char far *d_637a;
extern char far *d_a0fb;
void g2_1534(void);
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void g1_0acc(void) {}
void pascal g1_0042(int a0) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
/*@body*/
void g1_6b82(void)
{
    register int i;
    struct g1_6b82_record far *p;

    if (d_0437 == 0)
        d_06e7 += 0xa0;

    if (d_06e7 == 0x280) {
        d_06e7 = 0;
        i = 0;
    } else {
        i = 0;
    }

    for (; i < d_05bc; ++i) {
        p = &d_5a12[i];

        if (p->state >= 3 && g1_326e(p->x, p->y))
            p->state = 0;

        if (p->state == 0)
            continue;

        if (g1_326e(p->x, p->y))
            continue;

        if (p->state >= 3 && g1_326e(p->x, p->y)) {
            p->state = 0;
            continue;
        }

        if (!g1_3714(p->x, p->y + 0x80) && p->state < 3)
            p->y += 0x80;

        if (p->state >= 3) {
            if (d_0437 != 0)
                p->y -= 0x40;
            if (g1_3714(p->x, p->y - 0x40)) {
                g1_2b86(1, p->x, p->y);
                p->state = 0;
                continue;
            }
            if (g1_3513(p->x, p->y)) {
                p->state = 0;
                g1_0b85(1000L);
                g1_2a40(0x3c0, p->x, p->y);
                g1_0042(0x10);
                continue;
            }
        }

        if (g1_3558(p->x, p->y)) {
            if (p->state == 1) {
                g1_314c(p->x, p->y);
                p->state = 2;
                if (!g1_3714(p->x, p->y + 0x80)) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
            } else if (p->state == 2) {
                p->state = 3;
                g1_0042(2);
            }
        }

        if (g1_3513(p->x, p->y) && p->state == 2) {
            p->state = 0;
            g1_0b85(200L);
            g1_2a40(0x140, p->x, p->y);
            g1_0acc();
            g1_0042(1);
            if (d_5554 != 0) {
                g2_1534();
                d_5554 = 0;
            }
        }

        if (p->state == 1)
            asm_0424(d_a0fb + 0x3f20,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (p->state == 2)
            asm_0424(d_637a + d_06e7 + 0x5000,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (p->state >= 3)
            asm_0424(d_637a + d_06e7 + 0x5280,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
    }
}









