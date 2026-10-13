struct g1_5f0c_record { int state, x, y, field3; };
extern struct g1_5f0c_record d_b0b4[];
extern int d_009d;
extern int d_009f;
extern int d_05b6;
extern int d_06e0;
extern char d_6379;
extern char far *d_637a;
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_326e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
int g1_3714(int a0, int a1) { return 0; }
int g1_367e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
/*@body*/
void g1_5f0c(void)
{
    register int i;
    struct g1_5f0c_record far *p;
    char status;

    d_06e0 += 0xa0;
    if (d_06e0 == 0x1e0)
        d_06e0 = 0;

    for (i = 0; i < d_05b6; i++) {
        p = &d_b0b4[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (p->state < 3) {
            if ((status = g1_3558(p->x, p->y)) != 0) {
                if (status == 1)
                    --p->x;
                if (status == 2)
                    ++p->x;
                g1_0042(0x12);
                p->state = 3;
            }
        }
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (p->state == 1) {
            if (g1_367e(p->x - 1, p->y) != 0 ||
                g1_367e(p->x - 1, p->y + 0x80) == 0) {
                p->state = 2;
            } else if (d_06e0 == 0) {
                --p->x;
            }
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a + d_06e0 + 0x3200,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        } else if (p->state == 2) {
            if (g1_367e(p->x + 2, p->y) != 0 ||
                g1_367e(p->x + 2, p->y + 0x80) == 0) {
                p->state = 1;
            } else if (d_06e0 == 0) {
                ++p->x;
            }
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a + d_06e0 + 0x3200,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        } else if (p->state >= 3) {
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a + (p->state - 3) * 0xa0 + 0x33e0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            ++p->state;
            if (p->state == 10) {
                p->state = 0;
                g1_2b86(1, p->x, p->y);
                g1_0b85(100L);
            }
        }
        if (g1_3513(p->x, p->y) != 0) {
            if (p->state > 0) {
                if (p->state < 3)
                    d_6379 = 1;
            }
        }
    }
}
