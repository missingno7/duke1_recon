extern unsigned int far *d_7729;
/*@body*/
int g1_3714(int a0, int a1, int a2)
{
    unsigned int far *p;
    unsigned int far *q;

    p = d_7729 + (a0 >> 1) + ((a1 >> 7) << 7) - 1;
    q = p;
    if (a0 & 1)
        q++;
    if (*p > 0x17ff || *q > 0x17ff)
        return 1;
    return 0;
}
