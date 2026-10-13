extern char d_a0fa;      /* accepted type */
extern char d_3564[];
extern char d_357e[];
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
/*@body*/
void pascal g2_1bb0(register int a0)
{
    g2_3d8c(a0, 2, 2);
    g2_37b6((char far *)&d_3564, a0, 6);
    g2_37b6((char far *)&d_357e, a0, 7);
    do {
    } while (d_a0fa == 0x1f);
    g2_2870(a0 + 0x18, 7);
}