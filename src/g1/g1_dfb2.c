#include <stdio.h>
extern int d_0410;
/*@body*/
void g1_dfb2(char far *filename, void far *buffer, int unused)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    putw(d_0410, stream);
    fwrite(buffer, 0x4268, 1, stream);
    fclose(stream);
}