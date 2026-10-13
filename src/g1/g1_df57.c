#include <stdio.h>
extern int d_040e;
/*@body*/
void g1_df57(char far *filename, void far *buffer)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    putw(d_040e, stream);
    fwrite(buffer, 0x4268, 1, stream);
    fclose(stream);
}
