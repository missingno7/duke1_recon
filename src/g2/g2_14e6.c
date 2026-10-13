extern char d_a0fa_;      /* accepted type */
extern char d_d134_;      /* accepted type */
extern char d_d4c0_;      /* accepted type */
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
/*@body*/
void g2_14e6(void)
{
    do {
    } while (d_a0fa_ == 0x44);
    g2_3d8c(2, 1, 1);
    g2_37b6("Are you sure you want to", 3, 3);
    g2_37b6("RESTART the level(Y/N)? ", 3, 4);
    g2_2870(0x1a, 4);
    d_d4c0_ = 0;
    d_d134_ = 0;
}
