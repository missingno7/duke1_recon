#include <stdio.h>
extern int d_4ed0_;
/*@body*/
void pascal g1_e8ed(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    putw(d_4ed0_, stream);
    fclose(stream);
}
