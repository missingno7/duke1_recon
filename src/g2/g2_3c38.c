extern void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *p, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}

#if EPISODE == 3
extern char d_dn3_420d[];
extern char d_dn3_4220[];
extern char d_dn3_4236[];
#else
extern char d_43d2[];
extern char d_43eb[];
extern char d_4404[];
extern char d_441d[];
#endif
/*@body*/
void g2_3c38(void)
{
    g2_3d8c(10, 9, 2);
#if EPISODE == 3
    g2_37b6(d_dn3_420d, 11, 0x13);
    g2_37b6(d_dn3_4220, 11, 0x14);
    g2_37b6(d_dn3_4236, 11, 0x15);
#else
    g2_37b6(d_43d2, 11, 0x13);
    g2_37b6(d_43eb, 11, 0x14);
    g2_37b6(d_4404, 11, 0x15);
    g2_37b6(d_441d, 11, 0x16);
#endif
    g2_2870(0x22, 0x16);
}
