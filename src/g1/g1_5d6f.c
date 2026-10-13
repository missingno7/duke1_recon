struct g1_5d6f_record { int active, x, y, state; };
extern struct g1_5d6f_record d_ab32[];
extern int d_009d;
extern int d_009f;
extern int d_05b4;
extern char far *d_a0fb;
extern int d_c295;
void asm_0424(char far *bitmap, int x, int y);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void g1_0adc(void) {}
void pascal g1_0042(int a0) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_5d6f(void)
{
    register int i;
    struct g1_5d6f_record far *p;

    for (i = 0; i < d_05b4; ++i) {
        p = &d_ab32[i];
        if (p->active != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x80;
                if (g1_3513(p->x, p->y) != 0 && p->state != 0) {
                    p->active = 0;
                    if (d_c295 < 4) {
                        ++d_c295;
                        g1_0adc();
                    }
                    g1_0042(0xc);
                    g1_0b85(1000L);
                    g1_2a40(0x3c0, p->x, p->y);
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
                    asm_0424(d_a0fb,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                } else {
                    asm_0424(d_a0fb + 0x1ae0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                }
            }
        }
    }
}
