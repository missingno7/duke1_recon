#include <dos.h>
extern char d_02fa;
extern char d_0436;
extern char d_06e2;
extern int d_4ed2_;
extern char d_555a_;
extern char d_c68c_;
extern char d_d138_;
extern char d_d13f_;
extern int d_d4bd_;
extern char d_d4c0_;
extern int d_d4c1_;
extern int d_d570_;
void g2_16f3(void);

int g1_3513(int a0, int a1) { return 0; }
void pascal g1_6183(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
/*@body*/
void g1_6292(void)
{
    ++d_06e2;
    if (d_06e2 == 1)
        d_06e2 = 0;

    if (d_d570_ == 0)
        return;

    if (g1_3513(d_d4bd_ + 1, d_d4c1_) ||
        g1_3513(d_d4bd_ + 1, d_d4c1_ - 128)) {
        if (d_555a_) {
            g2_16f3();
            d_555a_ = 0;
        }
    }

    if (d_4ed2_ == 0 && d_c68c_ != 0 && d_d13f_ == 0 && d_d4c0_ == 0 && d_d138_ == 0 &&
        (g1_3513(d_d4bd_ + 1, d_d4c1_) || g1_3513(d_d4bd_ + 1, d_d4c1_ - 128))) {
        d_4ed2_ = 1;
        if (d_02fa % 2 != 0)
            g1_0042(0x27);
        disable();
        d_c68c_ = 0;
        enable();
    }

    if (d_4ed2_ == 0)
        g1_6183(0, d_d4bd_, d_d4c1_);
    if (d_4ed2_ == 0)
        return;

    if (d_06e2 == 0)
        ++d_4ed2_;
    if (d_4ed2_ < 5) {
        if (d_4ed2_ == 3 && d_02fa % 2 == 0)
            g1_0042(0x13);
        g1_6183(d_4ed2_ - 1, d_d4bd_, d_d4c1_);
        return;
    }
    if (d_4ed2_ < 5)
        return;

    switch (d_4ed2_) {
    case 4:
        g1_6183(3, d_d4bd_, d_d4c1_);
        break;
    case 5:
        g1_6183(2, d_d4bd_, d_d4c1_);
        break;
    case 6:
        g1_6183(1, d_d4bd_, d_d4c1_);
        break;
    case 7:
        g1_6183(0, d_d4bd_, d_d4c1_);
        break;
    case 8:
        g1_6183(0, d_d4bd_, d_d4c1_);
        d_0436 = 1;
        break;
    }
}







