struct g1_376f_record { int state, x, y; };
extern struct g1_376f_record d_669f_[];
extern int d_009d;
extern int d_009f;
extern int d_043c;
extern char far *d_a0fb_;
char pascal g1_326e(int a0, int a1) {}
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(register int a0, int a1, int a2) {}
void asm_0424(char far *bitmap, int a0, int a1);
/*@body*/
void g1_376f(void)
{
    register int i;
    struct g1_376f_record far *p;

    for (i = 0; i < d_043c; ++i) {
        p = &d_669f_[i];
        if (p->state != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x80;
                if (g1_3558(p->x, p->y) != 0) {
                    p->state = 0;
                    g1_314c(p->x, p->y);
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(500L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                } else if (g1_326e(p->x, p->y) == 0) {
                    asm_0424(d_a0fb_,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                }
            }
        }
    }
}


