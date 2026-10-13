#include <dos.h>
extern char d_0097;
extern char d_a0fa_;
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
/*@body*/
void pascal g2_1058(register int a0)
{
    g2_3d8c(a0, 3, 2);
    outport(0x3ce, 5);
    while (d_a0fa_ == 0x1f)
        ;
    g2_37b6("       Sound toggle", a0, 7);
    if (d_0097 = !d_0097) {
        g2_37b6("     The sound is ON", a0, 9);
    } else {
        g2_37b6("     The sound is OFF", a0, 9);
        outportb(0x61, inportb(0x61) & 0xfd);
    }
    delay(300);
    g2_2870(a0 + 0x18, 0x0a);
    while (d_a0fa_ == 0x1f)
        ;
}


