struct s_bccb { int a, b, c; };
extern struct s_bccb d_6b58_[];
extern int d_009d;
extern int d_009f;
extern char d_554f_;
extern char d_5550_;
extern char d_5551_;
extern char d_5552_;
extern char far *d_a0fb_;
extern int d_d70e_;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) {}
int g1_3513(int a0, int a1) {}
void pascal g1_0042(int a0) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_bb9f(void) {}
/*@body*/
void g1_bccb(void)
{
    register int si;
    struct s_bccb far *p;

    for (si = 0; si < d_d70e_; si++) {
        p = &d_6b58_[si];
        if (p->a == 0)
            continue;
        if (g1_326e(p->b, p->c))
            continue;
        if (g1_3513(p->b, p->c)) {
            switch (p->a) {
            case 0x00a0:
                d_554f_ = 1;
                break;
            case 0x0140:
                d_5550_ = 1;
                break;
            case 0x01e0:
                d_5551_ = 1;
                break;
            case 0x0280:
                d_5552_ = 1;
                break;
            }
            g1_0042(9);
            g1_0b85(1000L);
            g1_2a40(0x03c0, p->b, p->c);
            g1_bb9f();
            p->a = 0;
        } else {
            asm_0424(d_a0fb_ + p->a + 0x4ce0,
                     p->b - d_009d,
                     0x10 + ((p->c - d_009f) >> 3));
        }
    }
}
