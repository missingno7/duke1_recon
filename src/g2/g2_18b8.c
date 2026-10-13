extern int d_02fb;      /* accepted type */
extern char d_a0fa;      /* accepted type */
extern char d_d134;      /* accepted type */
extern char d_d4c0;      /* accepted type */
extern char d_33ab;
extern char d_33c4;
extern char d_33dd;
extern char d_33f6;
void pascal g1_0042(int a0);    /* accepted signature */
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
void g2_01d5(void) {}    /* accepted signature; stub for push cs; call near */
/*@body*/
void g2_18b8(void)
{
    d_a0fa = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6((char far *)&d_33ab, 3, 7);
    g2_37b6((char far *)&d_33c4, 3, 8);
    g2_37b6((char far *)&d_33dd, 3, 9);
    g2_37b6((char far *)&d_33f6, 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0 = 0;
        d_d134 = 0;
    } while (d_a0fa != 0x1c);
    d_a0fa = 0;
    d_02fb = 0;
    g2_01d5();
}
