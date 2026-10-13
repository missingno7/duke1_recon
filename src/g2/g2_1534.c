extern int d_02fb;      /* accepted type */
extern char d_a0fa_;      /* accepted type */
extern char d_d134_;      /* accepted type */
extern char d_d4c0_;      /* accepted type */
void pascal g1_0042(int a0);    /* accepted signature */
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far *a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
void g2_01d5(void) {}    /* stub: called via push cs; call near */
/*@body*/
void g2_1534(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Drink soda  ", 3, 7);
    g2_37b6("to increase your health!", 3, 8);
    g2_37b6("                        ", 3, 8);
    g2_37b6("      Press ENTER:      ", 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}
