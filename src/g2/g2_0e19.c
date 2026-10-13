extern int d_02fb;      /* accepted type */
extern char d_a0fa_;      /* accepted type */
extern char d_d134_;      /* accepted type */
extern char d_d4c0_;      /* accepted type */
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far *a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
void g2_01d5(void) {}    /* accepted signature; stub for push cs; call near */
/*@body*/
void g2_0e19(void)
{
    g2_3d8c(7, 3, 2);
    g2_37b6("This option will be     ", 8, 7);
    g2_37b6("available after you play", 8, 8);
    g2_37b6("the first level.        ", 8, 9);
    g2_37b6("      Press ENTER:      ", 8, 10);
    do {
        g2_2870(0x1f, 0x0a);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_02fb = 0;
    g2_01d5();
}
