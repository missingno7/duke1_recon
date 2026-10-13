extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
/*@body*/
int g1_35ee(register int a0, int a1, int a2, int a3)
{
    register int index;
    index = ((d_009b >> 4) << 7) + d_009f - a2 + 2;
    if (((d_0099 + d_009d - a0) > a0) &&
        ((d_0099 + d_009d - a0) < a1) &&
        (index > 0) &&
        (index < 0x180))
        return 1;
    return 0;
}
