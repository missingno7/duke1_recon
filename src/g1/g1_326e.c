extern int d_009d;
extern int d_009f;
/*@body*/
char pascal g1_326e(int a0, int a1)
{
    if (a0 >= d_009d &&
        d_009d + 29 > a0 &&
        d_009f - 64 <= a1 &&
        d_009f + 1280 > a1)
        return 0;
    return 1;
}
