#include <stdio.h>
#include <stdlib.h>
extern char far *d_c285_;
/*@body*/
void pascal g2_30b0(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_c285_ = malloc(0x7d01);
    if (d_c285_)
        fread(d_c285_, 0x7d00, 1, stream);
    fclose(stream);
}
