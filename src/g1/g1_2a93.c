struct s8 { int a, b, c, d; };
extern struct s8 d_d4c3[];
extern int d_009d;
extern int d_009f;
extern int d_0518;
extern int d_064a;
extern char far *d_a0ef;
char pascal g1_326e(int a0, int a1);
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_2a93(void)
{
    register int i;
    struct s8 far *p;

    d_064a += 0xa0;
    if (d_064a > 0xa0)
        d_064a = 0;

    for (i = 0; i < d_0518; ++i) {
        p = &d_d4c3[i];
        if (g1_326e(p->b, p->c) != 0) {
            if (p->d < 0x8c0) {
                p->a = 0;
                continue;
            }
        }
        if (p->a == 0)
            continue;

        p->c -= 8;
        if (g1_326e(p->b, p->c) == 0) {
            asm_0424(d_a0ef + p->d + d_064a,
                     p->b - d_009d,
                     ((p->c - d_009f) >> 3) + 0x10);
        }
        ++p->a;
        if (p->d < 0x8c0 && p->a == 0x28)
            p->a = 0;
        if (p->d >= 0x8c0 && p->a == 0x2bc)
            p->a = 0;
    }
}
