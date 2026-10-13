extern char d_0098;
extern char d_03a3;
extern int d_040c;
extern char d_0b46;
extern char d_530e_;
extern char d_5553_;
extern char d_5554_;
extern char d_5555_;
extern char d_555a_;
extern char d_555b_;
extern char d_555c_;
extern char d_5a11_;
extern char d_5c6a_;
extern char d_5c6b_;
extern char d_5ec8_;
extern char d_637e_;
extern char d_68f7_;
extern char d_a0fa_;
extern char d_c278_;
extern char d_c683_;
extern char d_cc81_;
void g2_3114(void);
void pascal g2_0009(int a0);
void pascal g2_01a9(int a0);
void g2_340f(void);
void pascal g2_0036(int a0);
void g2_3bd7(void);
void g2_3568(void);
void g2_3c38(void);
int pascal g1_049f(int a0) { return 0; }
unsigned char pascal g1_0126(int a0) { return 0; }
void g1_fc9c(void) {}
void pascal g1_0042(int a0) {}
/*@body*/
void pascal g1_fd15(void)
{
    register int state;

    for (;;) {
        g2_3114();
        state = g1_049f(7);

        d_5a11_ = 0;
        d_5c6b_ = 0;
        d_5554_ = 0;
        d_637e_ = 0;
        d_5ec8_ = 0;
        d_555a_ = 0;
        d_555c_ = 0;
        d_5553_ = 0;
        d_555b_ = 0;
        d_68f7_ = 0;
        d_5555_ = 0;
        d_5c6a_ = 0;

        if (state == 1) {
            d_c683_ = 0;
            d_c278_ = 1;
            d_040c = 0;
            d_0098 = 1;
            d_03a3 = 0;
            g2_01a9(0x14);
            g2_340f();
            g2_0036(0x14);
            if (d_cc81_ == 0) {
                while ((d_a0fa_ & 0x80) == 0) {
                }
            }
            g2_3bd7();
            g2_01a9(0x14);
            g2_3568();
            g2_0036(0x14);
            if (d_cc81_ == 0) {
                while ((d_a0fa_ & 0x80) == 0) {
                }
            }
            g2_3c38();
            d_530e_ = 0;
            g2_0009(0x14);
            if (d_0b46 == 1) {
                d_5a11_ = 1;
                d_5c6b_ = 1;
                d_5554_ = 1;
                d_637e_ = 1;
                d_5ec8_ = 1;
                d_555a_ = 1;
                d_555c_ = 1;
                d_5553_ = 1;
                d_555b_ = 1;
                d_68f7_ = 1;
                d_5555_ = 1;
                d_5c6a_ = 1;
            }
            g1_0042(0x1a);
            return;
        }

        if (state == 2) {
            if (d_c278_ == 0)
                continue;
            d_c683_ = 1;
            d_0098 = 0;
            d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 3 && g1_0126(7) != 0) {
            d_03a3 = 1;
            d_c683_ = 0;
            d_0098 = 0;
            if (d_0b46 == 1) {
                d_5a11_ = 1;
                d_5c6b_ = 1;
                d_5554_ = 1;
                d_637e_ = 1;
                d_5ec8_ = 1;
                d_555a_ = 1;
                d_555c_ = 1;
                d_5553_ = 1;
                d_555b_ = 1;
                d_68f7_ = 1;
                d_5555_ = 1;
                d_5c6a_ = 1;
            }
            return;
        }

        if (state == 4) {
            d_c683_ = 0;
            d_c278_ = 1;
            d_040c = 0;
            d_0098 = 2;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 5) {
            if (d_c278_ == 0)
                continue;
            d_c683_ = 2;
            d_0098 = 0;
            d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 0) {
            g2_01a9(0x14);
            g1_fc9c();
            continue;
        }
    }
}
