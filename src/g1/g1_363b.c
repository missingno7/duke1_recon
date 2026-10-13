#include <stdlib.h>
#undef abs
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
/*@body*/
int g1_363b(int a0, int a1)
{
    register int v = d_009b;

    v >>= 4;
    v <<= 7;
    v += d_009f;
    v -= a1;
    v++;
    v++;

    if (abs(d_0099 + d_009d - a0) == 0 && v > 0 && v < 384)
        return 1;
    return 0;
}


