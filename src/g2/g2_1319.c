#include <dos.h>
extern void interrupt far (*d_a0f4)(void);
/*@body*/
void g2_1319(void)
{
    outportb(0x43, 0x36);
    outportb(0x40, 0);
    outportb(0x40, 0);
    setvect(8, d_a0f4);
    outportb(0x61, inportb(0x61) & 0xfd);
}
