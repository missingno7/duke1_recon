#include <dos.h>
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
extern int d_039d;
extern char d_0643;
extern int d_4ed2;
extern int d_5002;
extern void interrupt far (*d_5556)(void);
extern char d_771b;
extern char d_7728;
extern char d_772d;
extern char d_a0fa;
extern char d_a67d;
extern char d_a8d9;
extern char d_c683;
extern char d_c68c;
extern char d_cc81;
extern char d_d134;
extern char d_d135;
extern char d_d138;
extern int d_d139;
extern int d_d13b;
extern char d_d13f;
extern char d_d148;
extern char d_d4c0;
/*@body*/
void interrupt g1_15f4(void)
{
    d_a0fa = inportb(0x60);

    if (d_5002 == 0 && d_4ed2 == 0 && d_cc81 == 0 &&
        d_c683 == 0 && d_d139 == 0 && d_d13b == 0) {
        if (d_a0fa == d_02f4) d_c68c = 1;
        if (d_a0fa == (d_02f4 | 0x80)) d_c68c = 0;
        if (d_a0fa == d_02f5) d_d134 = 1;
        if (d_a0fa == (d_02f5 | 0x80)) d_d134 = 0;
        if (d_a0fa == d_02f6) d_d13f = 1;
        if (d_a0fa == (d_02f6 | 0x80)) d_d13f = 0;
        if (d_a0fa == d_02f7) d_d4c0 = 1;
        if (d_a0fa == (d_02f7 | 0x80)) d_d4c0 = 0;
        if (d_a0fa == d_02f9) d_d138 = 1;
        if (d_a0fa == (d_02f9 | 0x80)) d_d138 = 0;
        if (d_a0fa == d_02f8) d_d135 = 1;
        if (d_a0fa == (d_02f8 | 0x80)) d_d135 = 0;
    }

    if (d_a0fa == 0x33) d_0643 = 1;
    if (d_a0fa == 0xb3) d_0643 = 0;
    if (d_a0fa == 0x34) d_d148 = 1;
    if (d_a0fa == 0xb4) d_d148 = 0;
    if (d_a0fa == 0x0e) d_a67d = 1;
    if (d_a0fa == 0x8e) d_a67d = 0;
    if (d_a0fa == 0x51) d_a8d9 = 1;
    if (d_a0fa == 0xd1) d_a8d9 = 0;
    if (d_a0fa == 0x22) d_7728 = 1;
    if (d_a0fa == 0xa2) d_7728 = 0;
    if (d_a0fa == 0x18) d_772d = 1;
    if (d_a0fa == 0x98) d_772d = 0;
    if (d_a0fa == 0x20) d_771b = 1;
    if (d_a0fa == 0xa0) d_771b = 0;

    if (d_039d != 0)
        d_5556();

    outportb(0x61, inportb(0x61) | 0x80);
    outportb(0x61, inportb(0x61) & 0x7f);
    outportb(0x20, 0x20);
}
