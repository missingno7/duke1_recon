#include <dos.h>
extern char d_0097;
extern int d_02fb;
extern void interrupt far (*d_a0f4_)(void);
extern char d_a8d8_;
extern char d_d579_;
extern void interrupt far g2_25fc(void);
/*@body*/
void g2_1e97(void)
{
    outportb(0x43, 0x36);
    outportb(0x40, 0x51);
    outportb(0x40, 0x20);
    disable();
    d_a8d8_ = 0;
    d_d579_ = 0;
    d_02fb = 0;
    d_0097 = 1;
    d_a0f4_ = getvect(8);
    setvect(8, g2_25fc);
    enable();
}
