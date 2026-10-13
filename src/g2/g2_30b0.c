#include <stdio.h>
#include <stdlib.h>
extern char far *d_c285;
/*@body*/
void pascal g2_30b0(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_c285 = malloc(0x7d01);
    if (d_c285)
        fread(d_c285, 0x7d00, 1, stream);
    fclose(stream);
}
