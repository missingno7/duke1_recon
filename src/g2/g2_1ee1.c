#include <dos.h>
extern char d_376c;
void pascal g2_2d58(int a0);
void pascal g2_37b6(char far *a0, int a1, int a2);
void pascal g2_2870(int a0, int a1);
void pascal g2_1bfb(int a0) {}
/*@body*/
void pascal g2_1ee1(int a0)
{
    g2_2d58(a0);
    outport(0x3ce, 5);
    g2_37b6(&d_376c, a0, 3);
    g2_1bfb(a0);
    g2_2870(0x1a, 0x14);
}


