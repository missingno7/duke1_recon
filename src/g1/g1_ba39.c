#include <dos.h>

extern int d_0099;
extern int d_009d;
extern char d_02fa;
extern int d_071a;
extern int d_071c;
extern int d_071e;
extern int d_5314_;
extern char d_a0fa_;
extern int d_c276_;
extern int d_c289_;
extern int d_c681_;
extern char d_c68c_;
extern char d_cc81_;
extern int d_d146_;

void g1_b118(void) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void pascal g1_b926(int a0, int a1, int a2) {}

/*@body*/
void g1_ba39(void)
{
    register int si;

    if (d_c681_ == 0 || d_02fa == 0)
        return;

    ++d_071a;
    if (d_071a == 3)
        d_071a = 0;
    ++d_071c;

    if (d_071e != 0) {
        g1_b118();
        d_071e = 0;
        if (d_cc81_ == 0) {
            enable();
            while ((d_a0fa_ & 0x80) == 0) {
            }
            disable();
        }
    }

    if (d_071c == 0x7d)
        d_071c = 0;

    if (d_d146_ == 0 && d_5314_ == 0) {
        if (g1_3513(d_c276_ - 6, d_c289_) != 0) {
            g1_0042(0x1d);
            d_d146_ = 1;
            d_5314_ = 1;
            d_071e = 1;
        } else if (g1_3513(d_c276_ + 8, d_c289_) != 0) {
            g1_0042(0x1d);
            d_d146_ = 1;
            d_5314_ = 1;
            d_071e = 1;
        }
    }

    if (d_c68c_ != 0 &&
        (g1_3513(d_c276_, d_c289_) != 0 ||
         g1_3513(d_c276_ + 2, d_c289_) != 0)) {
        d_d146_ = 1;
        g1_0042(0x1d);
        d_071e = 1;
        d_5314_ = 1;
    }

    if (d_d146_ == 0) {
        g1_b926(d_071a, d_c276_, d_c289_);
    } else if (d_0099 + d_009d < d_c276_ - 1) {
        g1_b926(3, d_c276_, d_c289_);
    } else if (d_0099 + d_009d > d_c276_ + 3) {
        g1_b926(5, d_c276_, d_c289_);
    } else {
        g1_b926(4, d_c276_, d_c289_);
    }
}
