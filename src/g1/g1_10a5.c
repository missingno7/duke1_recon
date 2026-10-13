#include <dos.h>
extern int d_c297_;
extern char d_d135_;
extern char d_d138_;
/*@body*/
void g1_10a5(void)
{
    char sample;

    sample = inportb(0x201);
    if (d_c297_ != 0) {
        d_d138_ = !(sample & 0x10);
        d_d135_ = !(sample & 0x20);
    } else {
        d_d138_ = !(sample & 0x20);
        d_d135_ = !(sample & 0x10);
    }
}

