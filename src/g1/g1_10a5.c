#include <dos.h>
extern int d_c297;
extern char d_d135;
extern char d_d138;
/*@body*/
void g1_10a5(void)
{
    char sample;

    sample = inportb(0x201);
    if (d_c297 != 0) {
        d_d138 = !(sample & 0x10);
        d_d135 = !(sample & 0x20);
    } else {
        d_d138 = !(sample & 0x20);
        d_d135 = !(sample & 0x10);
    }
}

