extern unsigned int far *d_7729_;
extern int d_b62e_;
extern int d_b632_;
extern int d_c281_;
extern int d_d136_;
extern int d_d155_;
extern int d_d4b9_;
extern int d_d4bb_;
int g1_35ee(int a0, int a1, int a2) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
/*@body*/
void g1_73d3(void)
{
    register int si;

    if (d_c281_ == 0)
        return;
    if (g1_35ee(d_b62e_ - 2, d_b62e_ + d_d136_, d_b632_ - 32) != 0) {
        if (d_d155_ == 2) {
            for (si = 0; si < (d_d136_ >> 1); si++) {
                *((d_7729_ + d_d4b9_ + si) + (d_d4bb_ << 7) - 2) =
                    *((d_7729_ + d_d4b9_ + si) + (d_d4bb_ << 7) - 130);
                if (si % 2 != 0)
                    g1_314c(d_b62e_ * 2 + si * 2, d_b632_);
                else
                    g1_2b86(1, d_b62e_ * 2 + si * 2, d_b632_);
            }
            d_c281_ = 0;
            d_d155_ = 0;
            d_d155_ = 1;
            return;
        }
        d_d155_ = 1;
        return;
    }
    if (d_d155_ == 1)
        d_d155_ = 2;
}
