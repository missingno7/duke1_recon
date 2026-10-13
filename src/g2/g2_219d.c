#include <stdio.h>
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern int d_02fa;
extern char d_0b46;
extern int d_4ed4_;
extern char d_5318_;
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
extern int d_798a_;
extern int d_a0f8_;
extern char d_a0fa_;
extern int d_c295_;
extern int d_cc82_;
extern long d_68f8_;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far* a0, int a1, int a2);
/*@body*/
void pascal g2_219d(char a0)
{
    char previous;
    FILE *stream;
    char far *filename;

    previous = d_a0fa_;
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
        while (d_a0fa_ == previous) {
        }
        d_a0fa_ = 0;
        while (d_a0fa_ == 0) {
        }
        d_5318_ = 1;
        return;
    }
    d_5318_ = 0;
    d_009d = getw(stream);
    d_009f = getw(stream);
    d_0099 = getw(stream);
    d_009b = getw(stream);
    d_02fa = getw(stream);
    d_c295_ = getw(stream);
    d_798a_ = getw(stream);
    d_a0f8_ = getw(stream);
    d_4ed4_ = getw(stream);
    d_cc82_ = getw(stream);
    d_5a11_ = getw(stream);
    d_5c6b_ = getw(stream);
    d_5554_ = getw(stream);
    d_637e_ = getw(stream);
    d_5ec8_ = getw(stream);
    d_555a_ = getw(stream);
    d_555b_ = getw(stream);
    d_68f7_ = getw(stream);
    d_555c_ = getw(stream);
    d_5553_ = getw(stream);
    d_5555_ = getw(stream);
    d_5c6a_ = getw(stream);
    if (d_0b46 == 0) {
        d_5a11_ = d_5c6b_ = d_5554_ = d_637e_ = d_5ec8_ = d_555a_ = d_555b_ = d_68f7_ = d_555c_ = d_5553_ = d_5555_ = d_5c6a_ = 0;
    }
    fscanf(stream, "%ld", &d_68f8_);
    fclose(stream);
}
