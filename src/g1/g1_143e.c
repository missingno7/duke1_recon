/* goto kept: every structured return form tried (if/||, direct relational return, inverted
   compares, byte-boolean return) emits a 113-byte near match with five branch-layout
   differences; measured by luna-g1_143e, 2026-10-13. */
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern unsigned int far *d_7729;
extern unsigned char d_d576;
/*@body*/
char g1_143e(void)
{
    unsigned int far *p1;
    unsigned int far *p2;

    if (d_d576)
        goto zero_result;

    p1 = d_7729 + ((d_0099 + d_009d - 2) >> 1) + d_009f + ((d_009b >> 4) << 7);
    p2 = p1;
    if ((d_0099 + d_009d) & 1)
        p2++;

    if (*p1 > 0x17ff)
        goto zero_result;
    if (*p2 <= 0x17ff)
        goto one_result;

zero_result:
    return 0;

one_result:
    return 1;
}
