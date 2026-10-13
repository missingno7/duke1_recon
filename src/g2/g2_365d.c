#include <stdio.h>
#include <stdlib.h>
extern char far *d_c28f;
/*@body*/
void pascal g2_365d(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_c28f = malloc(0x7d01);
    if (d_c28f) {
        fread(d_c28f, 0x7d00, 1, stream);
    }
    fclose(stream);
}
