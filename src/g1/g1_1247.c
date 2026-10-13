extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern unsigned int far *d_7729_;
/*@body*/
char g1_1247(void)
{
    unsigned int far *p0;
    unsigned int far *p2;
    unsigned int far *p1;

    p0 = d_7729_ + ((d_0099 + d_009d - 3) >> 1) + d_009f + (((d_009b - 16) >> 4) << 7);
    p1 = p0;
    p2 = p0 - 128;
    if ((d_009b >> 3) & 1)
        p1 += 128;
    if (p0[0] > 0x17ffU)
        return 0;
    if (p2[0] > 0x17ffU)
        return 0;
    if (p1[0] > 0x17ffU)
        return 0;
    return 1;
}
