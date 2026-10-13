/* goto kept: three gotos keep the shared timer-loop test (structured for: 979 bytes, if/do:
   1020; this form 981 = original); the default-state reset to L_064b (nested continue/break
   form: 988 bytes).  Measured by luna-g1_049f. */
#include <dos.h>
extern int d_0095;
extern int d_02fb;
extern char d_530e_;
extern char d_a0fa_;
extern char d_cc81_;
extern char d_d135_;
extern char d_d56b_;
void g2_3114(void);
void pascal g2_01a9(int a0);
void g2_32b6(void);
void pascal g2_0036(int a0);
void g2_3fe1(void);
void g2_02f4(void);
void g2_315d(void);
int pascal g2_3d1e(int a0);
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_38be(int a0);
void pascal g2_1d40(int a0);
void pascal g2_2870(int a0, int a1);
void g2_0e19(void);
void g2_062c(void);
void g2_0491(void);
void g1_006f(int a0) {}
void pascal g1_008a(int a0) {}
/*@body*/
int pascal g1_049f(register int a0)
{
    unsigned long ticks;
    unsigned char button1;
    unsigned char button2;

    ticks = 0;
    button1 = inportb(0x201) & 0x10;
    button2 = inportb(0x201) & 0x20;
    if (d_d56b_ == 0) {
        button1 = 1;
        button2 = 1;
    }
    g2_3114();

    for (;;) {
        g2_01a9(20);
        g2_32b6();
        g2_0036(20);
        ticks = 0;
        d_a0fa_ = 0;
        while (d_a0fa_ == 0 && button1 != 0 && button2 != 0) {
            if (d_d56b_ != 0) {
                button1 = inportb(0x201) & 0x10;
                button2 = inportb(0x201) & 0x20;
            }
            if (d_02fb % 2 != 0) {
                ++ticks;
                if (ticks == 0x16e360UL) {
                    d_a0fa_ = 0;
                    return 5;
                }
                if (ticks == 0xf4240UL) {
                    g2_01a9(20);
                    g2_3fe1();
                    g2_02f4();
                    g2_0036(20);
                }
                if (ticks == 0x7a120UL) {
                    g2_01a9(20);
                    g2_315d();
                    g2_0036(20);
                }
            }
        }

        if ((d_a0fa_ == 0x10 || d_a0fa_ == 1) && ticks < 0x7a120UL) {
            while (d_a0fa_ == 0x10) {
            }
            if (g2_3d1e(7) != 0)
                return 0;
        }
        ticks = 0;
        outport(0x3ce, 0x105);
        for (;;) {
            while (button1 == 0 || button2 == 0) {
                if (d_d56b_ != 0) {
                    button1 = inportb(0x201) & 0x10;
                    button2 = inportb(0x201) & 0x20;
                }
            }
            ticks = 0;
            g2_3d8c(a0, 2, 8);
            outport(0x3ce, 5);
            g2_38be(a0);
            g2_0036(15);
            L_064b:
            d_a0fa_ = 0;
            goto L_067b;

            L_0652:
            ++ticks;
            if (ticks <= 0xbbaee0UL)
                goto L_067b;
            d_a0fa_ = 0;
            g2_01a9(20);
            return 5;

            L_067b:
            if (d_d56b_ != 0) {
                button1 = inportb(0x201) & 0x10;
                button2 = inportb(0x201) & 0x20;
            }
            if (d_a0fa_ == 0 && button1 != 0 && button2 != 0)
                goto L_0652;
            if (d_a0fa_ == 0x1f || d_a0fa_ == 0x39 || d_a0fa_ == 0x1c)
                return 1;
            if (button1 == 0 || button2 == 0) {
                while (button1 == 0 || button2 == 0) {
                    if (d_d56b_ != 0) {
                        button1 = inportb(0x201) & 0x10;
                        button2 = inportb(0x201) & 0x20;
                    }
                }
                if (d_cc81_ == 0 && d_d56b_ != 0)
                    g1_006f(a0);
                if (d_cc81_ == 0)
                    continue;
                g2_01a9(20);
                return 1;
            }

            if (d_a0fa_ == 0xc0 && d_d135_ != 0 && d_0095 != 0)
                return 4;
            if (d_a0fa_ == 0x2e) {
                while (d_a0fa_ == 0x2e) {
                }
                g2_01a9(15);
                g2_315d();
                g2_0036(15);
                d_a0fa_ = 0;
                while (d_a0fa_ == 0) {
                }
            } else if (d_a0fa_ == 0x23) {
                g2_1d40(a0);
                while (d_a0fa_ == 0x23) {
                }
                g2_2870(a0 + 0x18, 20);
            } else if (d_a0fa_ == 0x2f) {
                if (d_530e_ != 0) {
                    g2_0e19();
                } else {
                    return 2;
                }
            } else if (d_a0fa_ == 0x13) {
                return 3;
            } else if (d_a0fa_ == 0x19) {
                return 5;
            } else if (d_a0fa_ == 0x17) {
                g2_01a9(15);
                g2_062c();
            } else if (d_a0fa_ == 1 || d_a0fa_ == 0x10) {
                while (d_a0fa_ == 0x10) {
                }
                if (g2_3d1e(7) != 0)
                    return 0;
            } else if (d_a0fa_ == 0x22) {
                g1_008a(a0);
            } else if (d_a0fa_ == 0x14) {
                break;
            } else if (d_a0fa_ == 0x18) {
                g2_01a9(15);
                g2_3fe1();
                g2_02f4();
                g2_2870(0x27, 0x18);
                g2_3114();
                g2_0491();
                g2_2870(0x27, 0x18);
            } else {
                goto L_064b;
            }
            g2_01a9(15);
            g2_32b6();
        }
    }
}
