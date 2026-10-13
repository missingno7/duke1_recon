extern int d_009d;
extern int d_009f;
extern int d_053c;
extern int d_05cc;
extern int d_06fe;
extern char d_5553_;
extern char d_5555_;
extern int d_7f04_;
extern int d_9d96_;
extern int d_a0b9_;
extern char far *d_a0fb_;
extern int d_b3d4_;
extern char d_c68c_;
struct t_726b { int x, y; };
extern struct t_726b d_726b_[];
char pascal g1_326e(int a0, int a1) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void asm_0424(char far *bitmap, int row, int offset);
void g2_1821(void);
void g2_3b79(void);
void g2_1a82(void);
/*@body*/
void g1_a3e7(void)
{
    register int i;

    if (d_7f04_ == -1)
        return;
    if (g1_326e(d_9d96_, d_a0b9_) != 0)
        return;

    if (d_7f04_ == 0) {
        asm_0424(d_a0fb_ + 0x46a0,
                 d_9d96_ - d_009d,
                 ((d_a0b9_ - d_009f) >> 3) + 0x10);
        return;
    }

    d_06fe += 0xa0;
    if (d_06fe == 0x500)
        d_06fe = 0;

    asm_0424(d_a0fb_ + d_06fe + 0x41a0,
             d_9d96_ - d_009d,
             ((d_a0b9_ - d_009f) >> 3) + 0x10);

    if (g1_3513(d_9d96_, d_a0b9_) != 0 && d_5553_ != 0) {
        d_5553_ = 0;
        g2_1821();
    }

    if (g1_3513(d_9d96_, d_a0b9_) != 0 && d_b3d4_ != 0 && d_c68c_ != 0) {
        for (i = 0; i < d_05cc; ++i)
            (&d_726b_[i].x)[2] = 0;      /* the original clears the NEXT record's x */

        d_7f04_ = 0;
        g2_3b79();
        g1_0042(0x1f);
        d_053c = 0;
        d_b3d4_ = 0;
    }

    if (g1_3513(d_9d96_, d_a0b9_) != 0 &&
        d_b3d4_ == 0 && d_c68c_ != 0 &&
        d_7f04_ != 0 && d_5555_ != 0)
        g2_1a82();
}
