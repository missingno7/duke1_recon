extern int d_009d;
extern int d_009f;
extern int d_02fd[];
extern int d_034d[];
extern int d_0437;
extern int d_06e3;
extern int d_5310_;
extern char d_6379_;
extern char far* d_637a_;
extern int d_abd2_;
extern int d_abd4_[];
extern int d_abe6_;
extern int d_b09c_[];
extern int d_b0ae_;
extern int d_b636_;
extern int d_d249_[];
void asm_0424(char far* a0, int a1, int a2);
void pascal g1_0b85(long a0) {}
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_6947(void)
{
    register int i;
    register int active;

    active = 1;
    if (d_b636_ != 0) {
        for (i = active; i < 10; ++i) {
            d_abd4_[i - 1] = d_abd4_[i];
            d_b09c_[i - 1] = d_b09c_[i];
            if (d_d249_[i] != 0)
                active = 0;
        }
        if (active != 0) {
            d_b636_ = 0;
            g1_0b85(10000L);
            d_5310_ = 1;
            return;
        }
    } else {
        return;
    }

    d_abe6_ += d_02fd[d_abd2_];
    d_b0ae_ += d_034d[d_abd2_] << 6;

    for (i = 1; i < 10; ++i) {
        if (g1_326e(d_abd4_[i], d_b09c_[i]) == 0 && d_d249_[i] != 0) {
            asm_0424(d_637a_ + d_06e3 + 0x4b00,
                     d_abd4_[i] - d_009d,
                     ((d_b09c_[i] - d_009f) >> 3) + 0x10);
            if (g1_3513(d_abd4_[i], d_b09c_[i]) != 0)
                d_6379_ = 1;
        }

        if (d_0437 != 0)
            d_06e3 += 0xa0;
        if (d_06e3 == 0x460)
            d_06e3 = 0;
        if (d_d249_[i] != 0 &&
            g1_3558(d_abd4_[i], d_b09c_[i] - 0x80) != 0) {
            g1_2b86(3, d_abd4_[i], d_b09c_[i]);
            g1_0b85(1000L);
            g1_0042(10);
            g1_314c(d_abd4_[i], d_b09c_[i] - 0x80);
            d_d249_[i] = 0;
        }
    }

    ++d_abd2_;
    if (d_abd2_ == 0x27)
        d_abd2_ = 0;
}
