extern int d_009d;
extern int d_009f;
extern int d_0530;
extern int d_0532;
extern int d_0534;
extern char far *d_a0fb_;
extern int d_cc82_;

void pascal g2_1ffa(char far *bitmap);
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0b85(long value) {}
void pascal g1_0042(int a0) {}
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_573d(void)
{
    if (d_cc82_ != 0)
        return;

    if (g1_326e(d_0530, d_0532) != 0)
        return;

    if (g1_3714(d_0530, d_0532 + 0x80) == 0)
        d_0532 += 0x80;

    if (g1_3513(d_0530, d_0532) != 0 && d_0534 != 0) {
        d_cc82_ = 1;
        g1_2a40(0x3c0, d_0530, d_0532);
        g1_0b85(1000L);
        g1_0042(12);
        g2_1ffa(d_a0fb_ + 0x2760);
        return;
    }

    if (d_0534 == 0) {
        if (g1_3558(d_0530, d_0532) != 0) {
            g1_314c(d_0530, d_0532);
            d_0534 = 1;
            if (g1_3714(d_0530, d_0532 + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, d_0530, d_0532);
            }
        }
    }

    if (d_0534 == 0) {
        asm_0424(d_a0fb_,
                 d_0530 - d_009d,
                 ((d_0532 - d_009f) >> 3) + 0x10);
        return;
    }

    asm_0424(d_a0fb_ + 0x2760,
             d_0530 - d_009d,
             ((d_0532 - d_009f) >> 3) + 0x10);
}

