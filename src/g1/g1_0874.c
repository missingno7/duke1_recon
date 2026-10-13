struct g1_0008_row { char field[7]; };
extern struct g1_0008_row d_00a1[];
extern char d_a0fa_;
void pascal g2_2870(int a0, int a1);
void pascal g1_0008(char a0, int a1, int a2) {}
/*@body*/
void pascal g1_0874(volatile int a2, volatile int a1, char far *a0)
{
    register int i = 0;

    d_a0fa_ = 0;
    for (;;) {
        g2_2870(a2 + i + 1, a1);
        if (d_a0fa_ == 0x1c) {
            a0[i] = 0;
            return;
        }
        if (d_a0fa_ == 0x0e) {
            if (i > 0)
                --i;
        } else if (i < 10) {
            if ((d_a0fa_ >= 0x10 && d_a0fa_ <= 0x19) ||
                (d_a0fa_ >= 0x2c && d_a0fa_ <= 0x32) ||
                (d_a0fa_ >= 0x1e && d_a0fa_ <= 0x26)) {
                a0[i] = d_00a1[(unsigned char)d_a0fa_].field[0];
                ++i;
                g1_0008(d_a0fa_, a2 + i, a1);
            } else if (d_a0fa_ == 0x39) {
                a0[i] = ' ';
                ++i;
            }
        }
    }
}
