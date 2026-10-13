extern int d_009d;
extern int d_009f;
extern int d_0536;
extern int d_0538;
extern int d_053a;
extern int d_053c;
extern char far *d_a0fb_;
extern int d_b3d4_;

extern void g2_1f9c(void);
extern void asm_0424(char far *bitmap, int row, int offset);

char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0b85(long value) {}
void pascal g1_0042(int a0) {}
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}

/*@body*/
void g1_5887(void)
{
    if (d_b3d4_ != 0)
        return;
    if (d_053c == 0)
        return;
    if (g1_326e(d_0536, d_0538) != 0)
        return;

    if (g1_3714(d_0536, d_0538 + 0x80) == 0)
        d_0538 += 0x80;

    if (g1_3513(d_0536, d_0538) != 0 && d_053a != 0) {
        d_b3d4_ = 1;
        g1_2a40(0x3c0, d_0536, d_0538);
        g1_0b85(1000L);
        g2_1f9c();
        g1_0042(12);
        return;
    }

    if (d_053a == 0) {
        if (g1_3558(d_0536, d_0538) != 0) {
            g1_314c(d_0536, d_0538);
            d_053a = 1;
            if (g1_3714(d_0536, d_0538 + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, d_0536, d_0538);
            }
        }
    }

    if (d_053a == 0) {
        asm_0424(d_a0fb_,
                 d_0536 - d_009d,
                 ((d_0538 - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb_ + 0x2800,
                 d_0536 - d_009d,
                 ((d_0538 - d_009f) >> 3) + 0x10);
    }
}
