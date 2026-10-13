#include <dos.h>
/*@body*/
void pascal g2_01f5(int mode, int far *a1, int far *a2)
{
    int second;
    int mask1;
    int mask2;
    register int state;
    register int first;

    if (mode == 1) {
        mask1 = 1;
        mask2 = 2;
    } else {
        mask1 = 4;
        mask2 = 8;
    }
    *a1 = 0;
    *a2 = 0;
    disable();
    outportb(0x201, inportb(0x201));
    do {
        state = inportb(0x201);
        first = (state & mask1) != 0;
        second = (state & mask2) != 0;
        *a1 += first;
        *a2 += second;
    } while (first + second != 0 && *a1 < 500 && *a2 < 500);
    enable();
}
