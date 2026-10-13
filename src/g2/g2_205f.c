#include <stdio.h>
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
/*@body*/
void g2_205f(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    fputc(d_02f4, stream);
    fputc(d_02f5, stream);
    fputc(d_02f6, stream);
    fputc(d_02f7, stream);
    fputc(d_02f8, stream);
    fputc(d_02f9, stream);
    fclose(stream);
}
