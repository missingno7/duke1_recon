#include <stdio.h>
#include <stdlib.h>
struct g2_3980_record { unsigned int f[8]; };
extern char d_4fce_[];
extern char far *d_cbb5_[];
extern char far *d_d714_;
/*@body*/
void pascal g2_3980(char far *filename)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    d_d714_ = malloc(0x2454);
    fread(d_d714_, 0x2454, 1, stream);
    fclose(stream);
    for (i = 0; i < 24; ++i) {
        d_cbb5_[i] = d_d714_ + (((struct g2_3980_record far *)(d_d714_ + ((((i << 1) << 1) << 1) << 1)))->f[8] >> 1 << 1);
        d_4fce_[i] = ((struct g2_3980_record far *)(d_d714_ + ((((i << 1) << 1) << 1) << 1)))->f[9];
    }
}
