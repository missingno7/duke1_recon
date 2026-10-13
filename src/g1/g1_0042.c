#include <dos.h>
extern char d_4fce[];
extern char d_530b;
extern char d_531b;
extern char d_a8d8;
extern char d_d579;
/*@body*/
void pascal g1_0042(int a0)
{
    disable();
    if (d_4fce[a0] >= d_d579) {
        d_d579 = d_4fce[a0];
        d_530b = 1;
        d_531b = a0;
        d_a8d8 = 0;
    }
    enable();
}
