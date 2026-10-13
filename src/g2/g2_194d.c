struct g1_0008_row { char field[7]; };
extern struct g1_0008_row d_00a1[];
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
void pascal g2_37b6(char far* a0, int a1, int a2);
/*@body*/
void pascal g2_194d(register int a0)
{
    g2_37b6(d_00a1[(unsigned char)d_02f4].field, a0 + 0x11, 9);
    g2_37b6(d_00a1[(unsigned char)d_02f5].field, a0 + 0x11, 10);
    g2_37b6(d_00a1[(unsigned char)d_02f6].field, a0 + 0x11, 11);
    g2_37b6(d_00a1[(unsigned char)d_02f7].field, a0 + 0x11, 12);
    g2_37b6(d_00a1[(unsigned char)d_02f8].field, a0 + 0x11, 13);
    g2_37b6(d_00a1[(unsigned char)d_02f9].field, a0 + 0x11, 14);
}
