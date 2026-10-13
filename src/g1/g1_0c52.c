#include <dos.h>
extern int d_771c_[];
extern int d_7722_[];
extern int d_9676_[];
extern int d_967c_[];
extern int d_c297_;
extern char d_c68c_;
extern char d_d134_;
extern char d_d13f_;
extern char d_d4c0_;
struct reading {
    int a;
    int b;
    int c;
};
void pascal g2_01f5(int mode, int far *x, int far *y);
/*@body*/
struct reading g1_0c52(register int mode)
{
    int x;
    int y;
    int xdir;
    int ydir;
    struct reading state;
    register int sample;

    x = 0;
    y = 0;
    xdir = 0;
    ydir = 0;

    g2_01f5(mode, &x, &y);
    if ((x > 500) | (y > 500)) {
        x = d_9676_[mode] + 1;
        y = d_967c_[mode] + 1;
    }

    if (d_771c_[mode] < x)
        xdir = 1;
    else if (d_9676_[mode] > x)
        xdir = -1;

    if (d_7722_[mode] < y)
        ydir = 1;
    else if (d_967c_[mode] > y)
        ydir = -1;

    switch (ydir * 3 + xdir) {
    case -4: d_c68c_ = 1; d_d13f_ = 1; d_d4c0_ = 0; d_d134_ = 0; break;
    case -3: d_c68c_ = 1; d_d13f_ = 0; d_d4c0_ = 0; d_d134_ = 0; break;
    case -2: d_c68c_ = 1; d_d13f_ = 0; d_d4c0_ = 1; d_d134_ = 0; break;
    case -1: d_c68c_ = 0; d_d13f_ = 1; d_d4c0_ = 0; d_d134_ = 0; break;
    case  0: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 0; d_d134_ = 0; break;
    case  1: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 1; d_d134_ = 0; break;
    case  2: d_c68c_ = 0; d_d13f_ = 1; d_d4c0_ = 0; d_d134_ = 1; break;
    case  3: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 0; d_d134_ = 1; break;
    case  4: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 1; d_d134_ = 1; break;
    }

    sample = inportb(0x201);
    if (mode == 1) {
        state.b = ((sample & 0x10) == 0) ? 1 : 0;
        state.c = ((sample & 0x20) == 0) ? 1 : 0;
    } else {
        state.b = ((sample & 0x40) == 0) ? 1 : 0;
        state.c = ((sample & 0x80) == 0) ? 1 : 0;
    }
    if (d_c297_ != 0) {
        sample = state.b;
        state.b = state.c;
        state.c = sample;
    }

    return state;
}
