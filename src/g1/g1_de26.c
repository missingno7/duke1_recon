#include <stdio.h>
extern unsigned int far *d_7729_;
/*@body*/
void g1_de26(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    fread(d_7729_, 0x2d00, 2, stream);
    fclose(stream);
}
