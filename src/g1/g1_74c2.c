struct g1_74c2_record { int x; int y; int used; };
extern struct g1_74c2_record d_b3d6[];
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_05c2;
extern int d_06ed;
extern char d_6379;
extern char far *d_a0fb;
extern char pascal g1_326e(int a0, int a1);
extern int g1_3513(int a0, int a1);
extern void pascal g1_0042(int a0) {}
void asm_0424(char far *bitmap, int x, int y);
char pascal g1_326e(int a0, int a1) {}
int g1_3513(int a0, int a1) {}
/*@body*/
void g1_74c2(void)
{
    register int i;
    struct g1_74c2_record far *p;

    d_06ed += 0xa0;
    if (d_06ed == 0x280)
        d_06ed = 0;

    for (i = 0; i < d_05c2; ++i) {
        p = &d_b3d6[i];
        if (p->used != 0 && g1_326e(p->x, p->y) == 0) {
            if (g1_3513(p->x, p->y) != 0) {
                asm_0424(d_a0fb + d_06ed + 0x21c0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                d_6379 = 1;
            } else {
                asm_0424(d_a0fb + d_06ed + 0x1f40,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
            if (d_0437 == 0)
                g1_0042(0x15);
        }
    }
}
