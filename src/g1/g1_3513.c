extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern int abs(int);
/*@body*/
int g1_3513(int a0, int a1, int a2)
{
    register int v = d_009b;

    v >>= 4;
    v <<= 7;
    v += d_009f;
    v -= a1;
    v++;
    v++;

    if (abs(d_0099 + d_009d - a0) < 2 && v > 16 && v < 384)
        return 1;
    return 0;
}
