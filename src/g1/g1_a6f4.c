extern int d_5000_;
extern int d_5316_;
extern unsigned int far *d_7729_;
extern int d_d574_;
extern int d_d577_;
void pascal g1_2b86(register int a0, int a1, int a2) {}
/*@body*/
void g1_a6f4(void)
{
    if (d_5316_ == 0) return;
    if (d_5000_ == 0) return;
    g1_2b86(3, d_d574_ + 2, d_d577_);
    if (*(d_7729_ + d_d577_ + (d_d574_ >> 1)) == 0x2fe0U) {
        d_5316_ = 0;
        d_5000_ = 0;
    } else {
        *(d_7729_ + d_d577_ + (d_d574_ >> 1)) = 0x2fe0U;
    }
    d_d574_ += 2;
}



