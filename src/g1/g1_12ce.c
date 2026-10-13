extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern unsigned int far *d_7729_;
/*@body*/
unsigned char g1_12ce(void)
{
    unsigned int far *p;
    unsigned int far *r;
    unsigned int far *q;

    p = d_7729_ + ((d_009d + d_0099) >> 1) + d_009f
        + (((d_009b - 16) >> 4) << 7);
    q = p;
    r = p - 128;
    if ((d_009b >> 3) & 1)
        q += 128;
    if (*p > 0x17ff || *r > 0x17ff || *q > 0x17ff)
        return 0;
    return 1;
}
