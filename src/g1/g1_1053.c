/* Joystick buttons from game port 0x201: 1 = button A, 2 = button B, 0 = none. */
#include <dos.h>
/*@body*/
int g1_1053(void)
{
    register int v = inportb(0x201);

    if (!(v & 0x10))
        return 1;
    if (!(v & 0x20))
        return 2;
    return 0;
}
