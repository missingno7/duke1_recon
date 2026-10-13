extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_5000_;
extern int d_5149_;
extern int d_52db_;
extern int d_5307_;
extern char d_555c_;
extern char far *d_a0fb_;
extern char d_c68c_;
extern int d_cc82_;
extern int d_d13d_;
extern int d_d140_;
void asm_0424(char far *bitmap, int row, int offset);
void g2_178a(void);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void pascal g1_1b8a(int a0, int a1, int a2) {}
/*@body*/
void g1_a53a(void)
{
    if (d_5307_ == 0)
        return;

    if (g1_326e(d_d13d_ - 2, d_d140_) == 0) {
        asm_0424(d_a0fb_ + 0x4880,
                 d_d13d_ - d_009d - 2,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    }

    if (g1_326e(d_d13d_ + 2, d_d140_) == 0) {
        asm_0424(d_a0fb_ + 0x4920,
                 d_d13d_ - d_009d + 2,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    }

    if (g1_326e(d_d13d_, d_d140_) != 0) {
        d_52db_ = 0;
        return;
    }

    if (g1_3513(d_d13d_, d_d140_) != 0 && d_555c_ != 0) {
        d_555c_ = 0;
        g2_178a();
    }

    if (g1_3513(d_d13d_, d_d140_) != 0) {
        if (d_c68c_ != 0 && d_5149_ == 0) {
            if (d_cc82_ != 0) {
                d_5149_ = 1;
                d_5000_ = 1;
                g1_0042(5);
            } else {
                d_52db_ = 1;
            }
        }
    }

    if (d_5149_ == 0 && d_0437 == 0) {
        asm_0424(d_a0fb_ + 0x4740,
                 d_d13d_ - d_009d,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb_ + 0x47e0,
                 d_d13d_ - d_009d,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    }

    if (d_52db_ != 0) {
        if (d_0437 == 0)
            g1_1b8a(1, d_d13d_ + 2, d_d140_ - 36);
        if (d_0437 == 0x40)
            g1_1b8a(2, d_d13d_ - 2, d_d140_ - 36);
    }
}


