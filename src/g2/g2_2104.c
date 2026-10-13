#include <stdio.h>
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
/*@body*/
void g2_2104(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    if (stream) {
        d_02f4 = fgetc(stream);
        d_02f5 = fgetc(stream);
        d_02f6 = fgetc(stream);
        d_02f7 = fgetc(stream);
        d_02f8 = fgetc(stream);
        d_02f9 = fgetc(stream);
    }
    fclose(stream);
}
