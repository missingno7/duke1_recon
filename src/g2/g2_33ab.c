#include <stdio.h>
#include <stdlib.h>
extern char far *d_c27d;
/*@body*/
void pascal g2_33ab(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    d_c27d = malloc(0x7d01);
    if (d_c27d != 0) {
        fread(d_c27d, 0x7d00, 1, stream);
    }
    fclose(stream);
}
