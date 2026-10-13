struct t_d1cf { int used, x, y; };
extern struct t_d1cf d_d1cf[];
extern int d_009d;
extern int d_009f;
extern int d_0520;
extern char far *d_a0fb;
char pascal g1_326e(int a0, int a1);
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_2eb1(void)
{
    register int i;
    struct t_d1cf far *p;

    for (i = 0; i < d_0520; i++) {
        p = &d_d1cf[i];
        if (p->used != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                asm_0424(d_a0fb + p->used * 0xa0 + 0x14a0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                p->used++;
                if (p->used == 6)
                    p->used = 0;
            } else {
                p->used = 0;
            }
        }
    }
}
