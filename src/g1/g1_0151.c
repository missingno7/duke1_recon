/* Save the game state to SAVEDn.DNx (n = slot character). */
#include <stdio.h>
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern char d_02fa;
extern int d_4ed4_;
extern char d_5553_;
extern char d_5554_;
extern char d_5555_;
extern char d_555a_;
extern char d_555b_;
extern char d_555c_;
extern char d_5a11_;
extern char d_5c6a_;
extern char d_5c6b_;
extern char d_5ec8_;
extern char d_637e_;
extern char d_68f7_;
extern long d_68f8_;
extern int d_798a_;
extern int d_a0f8_;
extern int d_c295_;
extern int d_cc82_;
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
    putw(d_c295_, stream);
    putw(d_798a_, stream);
    putw(d_a0f8_, stream);
    putw(d_4ed4_, stream);
    putw(d_cc82_, stream);
    putw(d_5a11_, stream);
    putw(d_5c6b_, stream);
    putw(d_5554_, stream);
    putw(d_637e_, stream);
    putw(d_5ec8_, stream);
    putw(d_555a_, stream);
    putw(d_555b_, stream);
    putw(d_68f7_, stream);
    putw(d_555c_, stream);
    putw(d_5553_, stream);
    putw(d_5555_, stream);
    putw(d_5c6a_, stream);
    fprintf(stream, "%ld\n", d_68f8_);
    fclose(stream);
}