#include <dos.h>
extern char d_4fce_[];
extern char d_530b_;
extern char d_531b_;
extern char d_a8d8_;
extern char d_d579_;
/*@body*/
void pascal g1_0042(int a0)
{
    disable();
    if (d_4fce_[a0] >= d_d579_) {
        d_d579_ = d_4fce_[a0];
        d_530b_ = 1;
        d_531b_ = a0;
        d_a8d8_ = 0;
    }
    enable();
}
