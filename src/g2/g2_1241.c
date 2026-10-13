extern char d_a0fa;
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_37b6(char far* a0, int a1, int a2);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
/*@body*/
void pascal g2_1241(register int a0)
{
    g2_3d8c(a0, 3, 2);
    g2_37b6("      Save a game.      ", a0, 7);
    g2_37b6("    Which game number   ", a0, 8);
    g2_37b6("  do you want to save?  ", a0, 9);
    g2_37b6("      Choose (1-9):     ", a0, 10);
    while (d_a0fa == 0x1f)
        ;
    g2_2870(a0 + 0x14, 0x0a);
}
