#include <stdio.h>
extern int d_4ed0;
/*@body*/
void pascal g1_e89d(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    if (stream == NULL) {
        d_4ed0 = 0;
    } else {
        d_4ed0 = getw(stream);
    }
    fclose(stream);
}
