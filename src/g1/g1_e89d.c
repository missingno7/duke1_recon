#include <stdio.h>
extern int d_4ed0_;
/*@body*/
void pascal g1_e89d(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    if (stream == NULL) {
        d_4ed0_ = 0;
    } else {
        d_4ed0_ = getw(stream);
    }
    fclose(stream);
}
