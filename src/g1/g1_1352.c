extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern char d_0439;
extern char d_043b;
extern char d_0611;
extern char d_0644;
extern unsigned int far *d_7729;
extern int d_a0f8;
extern char d_d576;
void pascal g1_0042(int a0) {}
/*@body*/
char g1_1352(void)
{
    unsigned int far *p1;
    unsigned int far *p2;

    p1 = d_7729 + ((d_0099 + d_009d - 2) >> 1) + d_009f
        + (((d_009b - 40) >> 4) << 7);
    p2 = p1;

    if ((d_0099 + d_009d) & 1)
        ++p2;

    if (*p1 >= 0x2ee0 || *p2 >= 0x2ee0 ||
        (*p1 >= 0x1b80 && *p1 <= 0x1ca0) ||
        (*p2 >= 0x1b80 && *p2 <= 0x1ca0)) {
        if (d_d576 != 0)
            return 0;
        if (d_0611 != 0)
            return 0;
        if (d_0439 == 0)
            d_043b = 0;
        if (d_a0f8 != 0) {
            d_0439 = 1;
            d_0644 = 1;
            g1_0042(0x1b);
        }
        else {
            g1_0042(0x26);
        }
        return 0;
    }

    d_0439 = 0;
    if (*p1 > 0x17ff || *p2 > 0x17ff) {
        if (d_0439 == 0)
            g1_0042(0x26);
        return 0;
    }
    return 1;
}

