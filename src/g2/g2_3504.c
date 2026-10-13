#include <stdio.h>
#include <stdlib.h>
extern char far *d_a0bb_;
/*@body*/
void pascal g2_3504(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    d_a0bb_ = malloc(0x7d01);
    if (d_a0bb_ != 0) {
        fread(d_a0bb_, 0x7d00, 1, stream);
    }
    fclose(stream);
}
