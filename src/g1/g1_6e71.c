struct g1_6e71_record { int state, x, y; };
extern struct g1_6e71_record d_d261[];
extern int d_009d;
extern int d_009f;
extern int d_05be;
extern int d_06e9;
extern int d_06eb;
extern char d_6379;
extern char far *d_637a;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_0042(int a0) {}
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void g1_6e71(void)
{
    register int i;
    struct g1_6e71_record far *p;

    d_06e9 += 0xa0;
    d_06eb -= 0xa0;
    if (d_06eb == -0xa0)
        d_06eb = 0x1e0;
    if (d_06e9 == 0x280)
        d_06e9 = 0;

    for (i = 0; i < d_05be; ++i) {
        p = &d_d261[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;

        if (p->state == 1) {
            p->y -= 8;
            asm_0424(d_637a + d_06e9 + 0x5500,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x - 2, p->y) == 0 ||
                g1_3714(p->x, p->y) != 0)
                p->state = 2;
        } else if (p->state == 2) {
            p->y += 8;
            asm_0424(d_637a + d_06eb + 0x5500,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x - 2, p->y + 0x80) == 0 ||
                g1_3714(p->x, p->y + 0x80) != 0)
                p->state = 1;
        } else if (p->state == 3) {
            p->y -= 8;
            asm_0424(d_637a + d_06e9 + 0x5780,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x + 2, p->y) == 0 ||
                g1_3714(p->x, p->y) != 0)
                p->state = 4;
        } else if (p->state == 4) {
            p->y += 8;
            asm_0424(d_637a + d_06eb + 0x5780,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x + 2, p->y + 0x80) == 0 ||
                g1_3714(p->x, p->y + 0x80) != 0)
                p->state = 3;
        }

        if (g1_3558(p->x, p->y) != 0) {
            g1_2b86(1, p->x, p->y);
            g1_2e64(p->x, p->y - 0x40);
            g1_0b85(0x64L);
            g1_0042(0x12);
            p->state = 0;
        }
        if (p->state != 0 && g1_3513(p->x, p->y) != 0)
            d_6379 = 1;
    }
}
