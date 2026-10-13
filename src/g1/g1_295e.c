#include <stdio.h>
/*@body*/
void g1_295e(char far *filename, void far *buffer, unsigned int count)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    fgetc(stream);
    fgetc(stream);
    fgetc(stream);
    fread(buffer, count, 1, stream);
    fclose(stream);
}


