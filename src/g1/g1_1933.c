struct g1_1933_record { int state, x, y, marker; };
extern struct g1_1933_record d_cb6d[];
extern int d_009d;
extern int d_009f;
extern int d_0646;
extern char d_530f;
extern char far *d_a0fb;
extern int d_c295;
int g1_367e(int a0, int a1);
void pascal g1_2b86(int a0, int a1, int a2);
char pascal g1_326e(int a0, int a1);
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void g1_1933(void)
{
    register int i;
    struct g1_1933_record far *p;

    d_0646 += 0xa0;
    if (d_0646 == 0x140)
        d_0646 = 0;

    for (i = 0; i < d_c295; ++i) {
        p = &d_cb6d[i];

        if (p->state == 0)
            continue;

        if (p->state == 1) {
            p->x -= 2;
            d_530f = 1;
            if (g1_367e(p->x + 1, p->y)) {
                p->state = 0;
                g1_2b86(1, p->x + 1, p->y + 0x40);
                continue;
            }
            if (!g1_326e(p->x, p->y)) {
                if (p->marker == 0)
                    asm_0424(d_a0fb + d_0646 + 0x3c0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
            } else {
                p->state = 0;
            }
            if (p->marker != 0) {
                p->marker = 0;
                asm_0424(d_a0fb + 0x1cc0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x13);
            }
        }

        if (p->state == 5) {
            p->x += 2;
            d_530f = 1;
            if (g1_367e(p->x, p->y)) {
                p->state = 0;
                g1_2b86(1, p->x - 1, p->y + 0x40);
                continue;
            }
            if (!g1_326e(p->x, p->y)) {
                if (p->marker == 0)
                    asm_0424(d_a0fb + d_0646 + 0x500,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
            } else {
                p->state = 0;
            }
            if (p->marker != 0) {
                p->marker = 0;
                asm_0424(d_a0fb + 0x1d60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x13);
            }
        }
    }
    d_530f = 0;
}
