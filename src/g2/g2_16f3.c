#include <dos.h>
extern int d_02fb;
extern char d_a0fa_;
extern char d_d134_;
extern char d_d4c0_;
void pascal g1_0042(int a0);
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *a0, int a1, int a2);
void pascal g2_2870(int a0, int a1);
void g2_01d5(void) {}
/*@body*/
void g2_16f3(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Press the UP", 3, 7);
    g2_37b6("ARROW to open the DOOR.", 3, 8);
    g2_37b6("                        ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}
