#include <stdio.h>
#include <stdlib.h>
extern char far *d_a0bb;
/*@body*/
void pascal g2_3504(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    d_a0bb = malloc(0x7d01);
    if (d_a0bb != 0) {
        fread(d_a0bb, 0x7d00, 1, stream);
    }
    fclose(stream);
}
