extern char d_a0fa;
extern char d_2fc5;
extern char d_2fde;
extern char d_2ff7;
extern char d_3010;
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
/*@body*/
void pascal g2_1241(register int a0)
{
    g2_3d8c(a0, 3, 2);
    g2_37b6((char far *)&d_2fc5, a0, 7);
    g2_37b6((char far *)&d_2fde, a0, 8);
    g2_37b6((char far *)&d_2ff7, a0, 9);
    g2_37b6((char far *)&d_3010, a0, 10);
    while (d_a0fa == 0x1f)
        ;
    g2_2870(a0 + 0x14, 0x0a);
}
