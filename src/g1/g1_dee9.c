#include <stdio.h>
extern int d_0410;
extern char d_c278_;
/*@body*/
void g1_dee9(char far *filename, char far *buffer)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    if (stream == NULL) {
        d_c278_ = 0;
    } else {
        d_0410 = getw(stream);
        fread(buffer, 0x4268, 1, stream);
        d_c278_ = 1;
    }
    fclose(stream);
}