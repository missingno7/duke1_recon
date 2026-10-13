struct g1_0008_row { char field[7]; };
extern struct g1_0008_row d_00a1[];
void pascal g2_37b6(char far* a0, int a1, int a2);
/*@body*/
void pascal g1_0008(char a0, int a1, int a2)
{
    char text[2];

    text[0] = d_00a1[(unsigned char)a0].field[0];
    text[1] = 0;
    g2_37b6(text, a1, a2);
}
