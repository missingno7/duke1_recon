#include <dos.h>
#include <stdio.h>
extern char far *d_7986_;
extern char far *d_cc7d_;
/*@body*/
void pascal g1_10fb(char far *filename, register int offset, int count)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    if (filename[0] != 0) {
        d_7986_ = MK_FP(0xa000, 0);
        d_cc7d_ = MK_FP(0xa000, 0x4000);
        count /= 4;
        fgetc(stream);
        fgetc(stream);
        fgetc(stream);
        for (i = 0; i < count; ++i) {
            fgetc(stream);
            outport(0x3c4, 0x0102);
            *(d_cc7d_ + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0202);
            *(d_cc7d_ + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0402);
            *(d_cc7d_ + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0802);
            *(d_cc7d_ + i + offset) = fgetc(stream);
        }
        fclose(stream);
    }
}




