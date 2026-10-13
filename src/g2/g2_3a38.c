#include <stdio.h>
#include <stdlib.h>
extern char d_4fe6[];
extern char far *d_cbb5[];
extern char far *d_d710;
/*@body*/
void pascal g2_3a38(char far *filename)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    d_d710 = malloc(0x2134);
    fread(d_d710, 0x1f40, 1, stream);
    fclose(stream);
    for (i = 0; i < 0x18; ++i) {
        d_cbb5[i + 0x18] = d_d710 + (((*((unsigned int far *)((char far *)d_d710 + ((((i << 1) << 1) << 1) << 1) + 0x10))) >> 1) << 1);
        d_4fe6[i] = *((unsigned char far *)((char far *)d_d710 + ((((i << 1) << 1) << 1) << 1) + 0x10));
    }
}
