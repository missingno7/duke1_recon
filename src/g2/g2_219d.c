#include <stdio.h>
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern int d_02fa;
extern char d_0b46;
extern int d_4ed4;
extern char d_5318;
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
extern int d_798a;
extern int d_a0f8;
extern char d_a0fa;
extern int d_c295;
extern int d_cc82;
extern long d_68f8;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far* a0, int a1, int a2);
/*@body*/
void pascal g2_219d(int a0)
{
    char previous;
    FILE *stream;
    char far *filename;

    previous = d_a0fa;
#if EPISODE == 1
    filename = "saved .dn1";
#elif EPISODE == 2
    filename = "saved .dn2";
#else
    filename = "saved .dn3";
#endif
    filename[5] = a0;
    stream = fopen(filename, "rb");
    if (stream == 0) {
        g2_3d8c(7, 2, 1);
        g2_37b6("     Game not found!!", 7, 5);
        fclose(stream);
        while (d_a0fa == previous) {
        }
        d_a0fa = 0;
        while (d_a0fa == 0) {
        }
        d_5318 = 1;
        return;
    }
    d_5318 = 0;
    d_009d = getw(stream);
    d_009f = getw(stream);
    d_0099 = getw(stream);
    d_009b = getw(stream);
    d_02fa = getw(stream);
    d_c295 = getw(stream);
    d_798a = getw(stream);
    d_a0f8 = getw(stream);
    d_4ed4 = getw(stream);
    d_cc82 = getw(stream);
    d_5a11 = getw(stream);
    d_5c6b = getw(stream);
    d_5554 = getw(stream);
    d_637e = getw(stream);
    d_5ec8 = getw(stream);
    d_555a = getw(stream);
    d_555b = getw(stream);
    d_68f7 = getw(stream);
    d_555c = getw(stream);
    d_5553 = getw(stream);
    d_5555 = getw(stream);
    d_5c6a = getw(stream);
    if (d_0b46 == 0) {
        d_5a11 = d_5c6b = d_5554 = d_637e = d_5ec8 = d_555a = d_555b = d_68f7 = d_555c = d_5553 = d_5555 = d_5c6a = 0;
    }
    fscanf(stream, "%ld", &d_68f8);
    fclose(stream);
}
