extern int d_0099;
extern int d_009d;
extern int d_009f;
extern char d_0644;
extern char d_68f7_;
extern int d_c279_;
extern int d_c27b_;
extern int d_c28b_;
extern int d_c28d_;
extern int d_c684_;
extern int d_c686_;
extern int d_c68a_;
extern char d_c68c_;
extern char d_d138_;
extern int d_d139_;
extern char d_d13f_;
extern char d_d4c0_;
void g2_18b8(void);
void pascal g1_9bb5(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
/*@body*/
void g1_a032(void)
{
    if (d_c684_ != 0) {
        if (d_d139_ == 1) {
            d_d139_ = 0;
            d_009d = d_c27b_ - d_0099 + 2;
            d_009f = d_c28d_ - 0x300;
            d_0644 = 1;
            d_c68c_ = 0;
            d_c68a_ = 8;
            d_c686_ = 0;
        }

        if (d_d139_ > 1)
            --d_d139_;
        if (d_c686_ > 0) {
            g1_9bb5(d_c686_ % 4, d_c279_, d_c28b_);
            --d_c686_;
        } else {
            g1_9bb5(d_d139_ % 4, d_c279_, d_c28b_);
        }

        if (d_68f7_ != 0) {
            if (g1_3513(d_c279_ + 2, d_c28b_)) {
                d_68f7_ = 0;
                g2_18b8();
            }
        }
        if (g1_3513(d_c279_ + 2, d_c28b_)) {
            if (d_c68c_ != 0 && d_d139_ == 0 && d_d13f_ == 0 &&
                d_d4c0_ == 0 && d_d138_ == 0) {
                d_d139_ = 8;
                g1_0042(7);
            }
        }
    }
}
