extern int d_0099;
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_0602;
extern int d_0604;
extern int d_0606;
extern int d_0608;
extern int d_060a;
extern int d_060c;
extern int d_060e;
extern int d_0702[];
extern int d_5002_;
extern int d_554a_;
extern int d_b630_;
extern int d_b634_;
extern int d_b9dc_;
extern int d_c283_;
extern int d_c293_;
extern char d_c68c_;
extern char d_d134_;
extern char d_d135_;
extern char d_d138_;
extern char d_d13f_;
extern int d_d142_;
extern char d_d4c0_;
extern int d_d56c_;
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_b292(int a0, int a1, int a2) {}
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_367e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_1b8a(int a0, int a1, int a2) {}
#include <dos.h>
/*@body*/
void g1_b595(void)
{
    if (d_554a_ != 0) {
        ++d_554a_;
        if (d_554a_ == 10)
            d_c293_ = 1;
        return;
    }

    d_0602 = !d_0602;
    if (d_c283_ == 0)
        return;

    if (d_d56c_ != 2) {
        if (d_d56c_ != 0) {
            if (d_0608 == 0) {
                ++d_0604;
                if (d_0604 == (d_060c >> 1)) {
                    if (d_0099 + d_009d - 2 < d_b630_)
                        g1_1b8a(1, d_b630_, d_b634_ - 32);
                    else
                        g1_1b8a(2, d_b630_ + 3, d_b634_ - 32);
                }
                if (d_0604 > d_060c) {
                    d_0604 = 0;
                    d_0606 = 0;
                    d_0608 = 1;
                    if (d_0099 + d_009d - 2 < d_b630_)
                        d_060a = 1;
                    else
                        d_060a = 0;
                }
            } else {
                d_b634_ += d_0702[d_0606];
                if (d_060a != 0) {
                    if (!g1_367e(d_b630_ - 1, d_b634_ - 64))
                        --d_b630_;
                } else {
                    if (!g1_367e(d_b630_ + 3, d_b634_ - 64))
                        ++d_b630_;
                }
                ++d_0606;
                if (d_0606 == 12) {
                    d_0608 = 0;
                    d_060c = (d_0437 >> 1) + 1;
                    d_0604 = 0;
                }
            }
            if (d_0099 + d_009d - 2 < d_b630_)
                g1_b292(d_0602, d_b630_, d_b634_);
            else
                g1_b292(d_0602 + 2, d_b630_, d_b634_);
            if (g1_3558(d_b630_ + 1, d_b634_ - 64)) {
                g1_2b86(3, d_b630_ + 2, d_b634_ - 92);
                --d_d142_;
            }
            if (d_0437 != 0 && d_d142_ < 10) {
                if (d_d142_ < 10)
                    g1_2e64(d_b630_ + 2, d_b634_ - 32);
                if (d_d142_ < 6)
                    g1_2e64(d_b630_ + 1, d_b634_ - 64);
                if (d_d142_ < 2)
                    g1_2e64(d_b630_ + 3, d_b634_ - 64);
            }
            if (d_d142_ == 1 && d_b9dc_ != 0)
                d_d56c_ = 0;
            else if (d_d142_ == 0)
                d_d56c_ = 2;
        } else {
            if (!g1_326e(d_b630_, d_b634_) && d_5002_ == 0) {
                d_5002_ = 1;
                g1_0042(40);
                disable();
                d_d135_ = d_d138_ = d_d13f_ = d_d4c0_ = d_c68c_ = d_d134_ = 0;
                enable();
            }
            if (d_5002_ > 30)
                d_c293_ = 1;
            if (d_5002_ != 0)
                ++d_5002_;
            if (d_5002_ != 0 && d_b634_ > 0x100 && d_009f > 0x100) {
                d_b634_ -= 0x80;
                d_009f -= 0x80;
                d_060e = 1;
            }
            if (d_0099 + d_009d - 2 < d_b630_)
                g1_b292(d_0602, d_b630_, d_b634_);
            else
                g1_b292(d_0602 + 2, d_b630_, d_b634_);
            return;
        }
    } else {
        d_b634_ += 32;
        if (d_0437 == 0)
            g1_314c(d_b630_ + 2, d_b634_);
        if (d_0437 == 32)
            g1_2b86(1, d_b630_ + 2, d_b634_);
        if (d_0437 == 64)
            g1_314c(d_b630_, d_b634_);
        if (d_0437 == 96)
            g1_2b86(3, d_b630_ + 2, d_b634_);
        if (d_0099 + d_009d - 2 < d_b630_)
            g1_b292(0, d_b630_, d_b634_);
        else
            g1_b292(2, d_b630_, d_b634_);
        if (g1_3714(d_b630_ + 1, d_b634_)) {
            g1_0042(41);
            d_554a_ = 1;
        }
        return;
    }
}
