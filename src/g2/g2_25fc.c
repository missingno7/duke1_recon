#include <dos.h>
extern char d_0097;
extern int d_02fb;
extern int d_0f2a;
extern char d_530b;
extern char d_531b;
extern void interrupt far (*d_a0f4)(void);
extern char d_a8d8;
extern int far *d_cbb5[];
extern char d_d579;
extern int d_d718;
/*@body*/
void interrupt g2_25fc(void)
{
    register unsigned int period;

    if (d_530b != 0) {
        d_530b = 0;
        d_0f2a = 0;
        d_a8d8 = 1;
    }

    if (d_cbb5[(unsigned char)d_531b][d_0f2a] == -1) {
        d_a8d8 = 0;
        d_d579 = 0;
        outportb(0x61, inportb(0x61) & 0xfd);
    }

    if (d_a8d8 != 0) {
        period = d_cbb5[(unsigned char)d_531b][d_0f2a];
        if (period == 0 && d_0097 != 0) {
            outportb(0x61, inportb(0x61) & 0xfc);
        } else if (d_0097 != 0) {
            outportb(0x43, 0xb6);
            outportb(0x42, period & 0x100);
            outportb(0x42, period >> 8);
            outportb(0x61, inportb(0x61) | 3);
        }
        ++d_0f2a;
    } else {
        outportb(0x61, inportb(0x61) & 0xfd);
    }

    ++d_02fb;
    ++d_d718;
    if (d_d718 == 8) {
        d_d718 = 0;
        d_a0f4();
    } else {
        outportb(0x20, 0x20);
    }
}

