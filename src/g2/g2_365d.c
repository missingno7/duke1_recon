#include <stdio.h>
#include <stdlib.h>
extern char far *d_c28f_;
/*@body*/
void pascal g2_365d(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_c28f_ = malloc(0x7d01);
    if (d_c28f_) {
        fread(d_c28f_, 0x7d00, 1, stream);
    }
    fclose(stream);
}
