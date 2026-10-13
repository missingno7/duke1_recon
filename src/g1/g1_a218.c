struct g1_a218_record { int state, x, y; };
extern struct g1_a218_record d_ae44[];
extern int d_009d;
extern int d_009f;
extern int d_05e0;
extern int d_05e2[];
extern char d_6379;
extern char far *d_637a;
char pascal g1_326e(int a0, int a1) {}
void pascal g1_0042(int a0) {}
int g1_3513(int a0, int a1) {}
char pascal g1_3558(int a0, int a1) {}
void asm_0424(char far *bitmap, int a0, int a1);
/*@body*/
void g1_a218(void)
{
    register int i;
    struct g1_a218_record far *p;

    for (i = 0; i < d_05e0; ++i) {
        p = &d_ae44[i];
        if (g1_326e(p->x, p->y) == 0) {
            p->y -= d_05e2[p->state + 6];
            ++p->state;
            if (p->state == 8)
                p->state = -6;
            if (p->state == -6)
                g1_0042(0x22);
            if (g1_3513(p->x, p->y))
                d_6379 = 1;
            g1_3558(p->x, p->y);
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a + 0x8b60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}
