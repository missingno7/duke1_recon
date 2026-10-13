#include <dos.h>
extern char d_0b46;
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
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *a0, int a1, int a2);
void pascal g2_2870(int a0, int a1);
/*@body*/
void pascal g2_10f0(register int a0)
{
    g2_3d8c(a0, 3, 2);
    outport(0x3ce, 5);
    while (d_a0fa_ == 0x23)
        ;
    g2_37b6("       Hint toggle ", a0, 7);
    d_0b46 = !d_0b46;
    if (d_0b46) {
        g2_37b6("     Hint mode is ON", a0, 9);
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
    } else {
        g2_37b6("     Hint mode is OFF", a0, 9);
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
    }
    g2_2870(a0 + 0x18, 0x0a);
    while (d_a0fa_ == 0x23)
        ;
}



