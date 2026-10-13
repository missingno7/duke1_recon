#include <dos.h>
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
extern int d_039d;
extern char d_0643;
extern int d_4ed2_;
extern int d_5002_;
extern void interrupt far (*d_5556_)(void);
extern char d_771b_;
extern char d_7728_;
extern char d_772d_;
extern char d_a0fa_;
extern char d_a67d_;
extern char d_a8d9_;
extern char d_c683_;
extern char d_c68c_;
extern char d_cc81_;
extern char d_d134_;
extern char d_d135_;
extern char d_d138_;
extern int d_d139_;
extern int d_d13b_;
extern char d_d13f_;
extern char d_d148_;
extern char d_d4c0_;
/*@body*/
void interrupt g1_15f4(void)
{
    d_a0fa_ = inportb(0x60);

    if (d_5002_ == 0 && d_4ed2_ == 0 && d_cc81_ == 0 &&
        d_c683_ == 0 && d_d139_ == 0 && d_d13b_ == 0) {
        if (d_a0fa_ == d_02f4) d_c68c_ = 1;
        if (d_a0fa_ == (d_02f4 | 0x80)) d_c68c_ = 0;
        if (d_a0fa_ == d_02f5) d_d134_ = 1;
        if (d_a0fa_ == (d_02f5 | 0x80)) d_d134_ = 0;
        if (d_a0fa_ == d_02f6) d_d13f_ = 1;
        if (d_a0fa_ == (d_02f6 | 0x80)) d_d13f_ = 0;
        if (d_a0fa_ == d_02f7) d_d4c0_ = 1;
        if (d_a0fa_ == (d_02f7 | 0x80)) d_d4c0_ = 0;
        if (d_a0fa_ == d_02f9) d_d138_ = 1;
        if (d_a0fa_ == (d_02f9 | 0x80)) d_d138_ = 0;
        if (d_a0fa_ == d_02f8) d_d135_ = 1;
        if (d_a0fa_ == (d_02f8 | 0x80)) d_d135_ = 0;
    }

    if (d_a0fa_ == 0x33) d_0643 = 1;
    if (d_a0fa_ == 0xb3) d_0643 = 0;
    if (d_a0fa_ == 0x34) d_d148_ = 1;
    if (d_a0fa_ == 0xb4) d_d148_ = 0;
    if (d_a0fa_ == 0x0e) d_a67d_ = 1;
    if (d_a0fa_ == 0x8e) d_a67d_ = 0;
    if (d_a0fa_ == 0x51) d_a8d9_ = 1;
    if (d_a0fa_ == 0xd1) d_a8d9_ = 0;
    if (d_a0fa_ == 0x22) d_7728_ = 1;
    if (d_a0fa_ == 0xa2) d_7728_ = 0;
    if (d_a0fa_ == 0x18) d_772d_ = 1;
    if (d_a0fa_ == 0x98) d_772d_ = 0;
    if (d_a0fa_ == 0x20) d_771b_ = 1;
    if (d_a0fa_ == 0xa0) d_771b_ = 0;

    if (d_039d != 0)
        d_5556_();

    outportb(0x61, inportb(0x61) | 0x80);
    outportb(0x61, inportb(0x61) & 0x7f);
    outportb(0x20, 0x20);
}
