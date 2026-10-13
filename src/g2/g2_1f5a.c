#include <dos.h>
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
/*@body*/
void pascal g2_1f5a(int a0)
{
    g2_3d8c(a0, 3, 7);
    outport(0x3ce, 5);
    g2_37b6("      Joystick mode", a0, 7);
    delay(100);
}
