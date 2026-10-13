#include <stdio.h>
#include <stdlib.h>
extern char d_4fe6_[];
extern char far *d_cbb5_[];
extern char far *d_d710_;
/*@body*/
void pascal g2_3a38(char far *filename)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    d_d710_ = malloc(0x2134);
    fread(d_d710_, 0x1f40, 1, stream);
    fclose(stream);
    for (i = 0; i < 0x18; ++i) {
        d_cbb5_[i + 0x18] = d_d710_ + (((*((unsigned int far *)((char far *)d_d710_ + ((((i << 1) << 1) << 1) << 1) + 0x10))) >> 1) << 1);
        d_4fe6_[i] = *((unsigned char far *)((char far *)d_d710_ + ((((i << 1) << 1) << 1) << 1) + 0x10));
    }
}
