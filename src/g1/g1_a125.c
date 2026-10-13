extern int d_0099;
extern int d_009d;
extern int d_009f;
extern char d_0644;
extern char d_68f7_;
extern int d_c279_;
extern int d_c27b_;
extern int d_c28b_;
extern int d_c28d_;
extern int d_c686_;
extern int d_c688_;
extern int d_c68a_;
extern char d_c68c_;
extern char d_d138_;
extern int d_d13b_;
extern char d_d13f_;
extern char d_d4c0_;
void g2_18b8(void);
void pascal g1_9bb5(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
/*@body*/
void g1_a125(void)
{
    if (d_c688_ == 0)
        return;

    if (d_d13b_ == 1) {
        d_d13b_ = 0;
        d_009d = d_c279_ - d_0099 + 2;
        d_009f = d_c28b_ + 0xfd00;
        d_0644 = 1;
        d_c68c_ = 0;
        d_c686_ = 8;
        d_c68a_ = 0;
    }

    if (d_d13b_ > 1)
        --d_d13b_;

    if (d_c68a_ > 0)
        {
            g1_9bb5(d_c68a_ % 4, d_c27b_, d_c28d_);
            --d_c68a_;
        }
    else
        g1_9bb5(d_d13b_ % 4, d_c27b_, d_c28d_);

    if (d_68f7_ != 0 && g1_3513(d_c27b_ + 2, d_c28d_)) {
        d_68f7_ = 0;
        g2_18b8();
    }

    if (!g1_3513(d_c27b_ + 2, d_c28d_))
        return;

    if (d_c68c_ != 0 && d_d13b_ == 0 && d_d13f_ == 0 &&
        d_d4c0_ == 0 && d_d138_ == 0) {
        d_d13b_ = 8;
        g1_0042(7);
    }
}

