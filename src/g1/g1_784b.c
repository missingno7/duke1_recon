struct g1_784b_record { int active, x, y, state; };
extern struct g1_784b_record d_9d99_[];
extern int d_009d;
extern int d_009f;
extern int d_05c6;
extern char far *d_a0fb_;
void asm_0424(char far *bitmap, int x, int y);
char pascal g1_326e(int a0, int a1) {}
int g1_3714(int a0, int a1) {}
int g1_3513(int a0, int a1) {}
void pascal g1_2a40(register int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
void pascal g1_0042(int a0) {}
char pascal g1_3558(int a0, register int a1) {}
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_784b(void)
{
    register int i;
    struct g1_784b_record far *p;

    for (i = 0; i < d_05c6; i++) {
        p = &d_9d99_[i];
        if (p->active != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x80;
                if (g1_3513(p->x, p->y) != 0 && p->state != 0) {
                    p->active = 0;
                    g1_2a40(0, p->x, p->y);
                    g1_0b85(100L);
                    g1_0042(0x10);
                    continue;
                }
                if (p->state == 0 && g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    p->state = 1;
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(500L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                }
                if (p->state == 0) {
                    asm_0424(d_a0fb_ + 0x3e80,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                } else {
                    asm_0424(d_a0fb_ + 0x2440,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                }
            }
        }
    }
}
