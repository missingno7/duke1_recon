struct t_c8eb { int used, value1, value2; };
extern struct t_c8eb d_c8eb[];
extern int d_009d;
extern int d_009f;
extern int d_051e;
extern char far *d_a0fb;
char pascal g1_326e(int a0, int a1);
void asm_0424(char far *bitmap, int a0, int a1);
/*@body*/
void g1_2f4c(void)
{
    register int i;
    struct t_c8eb far *p;

    for (i = 0; i < d_051e; ++i) {
        p = &d_c8eb[i];
        if (p->used != 0) {
            if (g1_326e(p->value1, p->value2) == 0) {
                asm_0424(d_a0fb + p->used * 0xa0 + 0xb40,
                         p->value1 - d_009d,
                         ((p->value2 - d_009f) >> 3) + 0x10);
                ++p->used;
                if (p->used != 6)
                    continue;
            }
            p->used = 0;
        }
    }
}
