#include <dos.h>
extern char d_0b46;
extern char d_5553;
extern char d_5554;
extern char d_5555;
extern char d_555a;
extern char d_555b;
extern char d_555c;
extern char d_5a11;
extern char d_5c6a;
extern char d_5c6b;
extern char d_5ec8;
extern char d_637e;
extern char d_68f7;
extern char d_a0fa;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *a0, int a1, int a2);
void pascal g2_2870(int a0, int a1);
/*@body*/
void pascal g2_10f0(register int a0)
{
    g2_3d8c(a0, 3, 2);
    outport(0x3ce, 5);
    while (d_a0fa == 0x23)
        ;
    g2_37b6("       Hint toggle ", a0, 7);
    d_0b46 = !d_0b46;
    if (d_0b46) {
        g2_37b6("     Hint mode is ON", a0, 9);
        d_5a11 = 1;
        d_5c6b = 1;
        d_5554 = 1;
        d_637e = 1;
        d_5ec8 = 1;
        d_555a = 1;
        d_555c = 1;
        d_5553 = 1;
        d_555b = 1;
        d_68f7 = 1;
        d_5555 = 1;
        d_5c6a = 1;
    } else {
        g2_37b6("     Hint mode is OFF", a0, 9);
        d_5a11 = 0;
        d_5c6b = 0;
        d_5554 = 0;
        d_637e = 0;
        d_5ec8 = 0;
        d_555a = 0;
        d_555c = 0;
        d_5553 = 0;
        d_555b = 0;
        d_68f7 = 0;
        d_5555 = 0;
        d_5c6a = 0;
    }
    g2_2870(a0 + 0x18, 0x0a);
    while (d_a0fa == 0x23)
        ;
}



