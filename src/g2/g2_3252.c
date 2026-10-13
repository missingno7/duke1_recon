#include <stdio.h>
#include <stdlib.h>
extern char far *d_b638_;
/*@body*/
void pascal g2_3252(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_b638_ = malloc(0x7d01);
    if (d_b638_ != 0) {
        fread(d_b638_, 0x7d00, 1, stream);
    }
    fclose(stream);
}
