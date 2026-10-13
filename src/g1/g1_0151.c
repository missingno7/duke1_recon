/* Save the game state to SAVEDn.DNx (n = slot character). */
#include <stdio.h>
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern char d_02fa;
extern int d_4ed4;
extern char d_5553;
extern char d_5554;
extern char d_5555;
extern char d_555a;
extern char d_555b;
extern char d_555c;
extern char d_5a11;
extern char d_5c6a;
extern char d_5c6b;
extern char d_5ec8;
extern char d_637e;
extern char d_68f7;
extern long d_68f8;
extern int d_798a;
extern int d_a0f8;
extern int d_c295;
extern int d_cc82;
/*@body*/
void pascal g1_0151(char a0)
{
    FILE *stream;
    char *name;
#if EPISODE == 1
    name = "saved .dn1";
#elif EPISODE == 2
    name = "saved .dn2";
#else
    name = "saved .dn3";
#endif
    name[5] = a0;
    stream = fopen(name, "wb");
    putw(d_009d, stream);
    putw(d_009f, stream);
    putw(d_0099, stream);
    putw(d_009b, stream);
    putw(d_02fa, stream);
    putw(d_c295, stream);
    putw(d_798a, stream);
    putw(d_a0f8, stream);
    putw(d_4ed4, stream);
    putw(d_cc82, stream);
    putw(d_5a11, stream);
    putw(d_5c6b, stream);
    putw(d_5554, stream);
    putw(d_637e, stream);
    putw(d_5ec8, stream);
    putw(d_555a, stream);
    putw(d_555b, stream);
    putw(d_68f7, stream);
    putw(d_555c, stream);
    putw(d_5553, stream);
    putw(d_5555, stream);
    putw(d_5c6a, stream);
    fprintf(stream, "%ld\n", d_68f8);
    fclose(stream);
}