#include <dos.h>
extern char d_a0fa;
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
/*@body*/
void pascal g2_11f2(register int a0)
{
    g2_3d8c(a0, 3, 1);
    outport(0x3ce, 5);
    g2_37b6("       Game PAUSED. ", a0, 7);
    while (d_a0fa == 0x19) {
    }
    g2_2870(a0 + 0x18, 8);
}
