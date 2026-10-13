void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *a0, int a1, int a2) {}
/*@body*/
void g2_3af3(void)
{
    g2_3d8c(7, 3, 6);
    g2_37b6("     APOGEE SOFTWARE    ", 8, 8);
    g2_37b6("       PRODUCTIONS      ", 8, 9);
    g2_37b6("          - - -         ", 8, 10);
    g2_37b6("        A game by       ", 8, 12);
    g2_37b6("      Todd Replogle     ", 8, 13);
    g2_37b6("       Version 2.0      ", 8, 15);
#if EPISODE == 3
    g2_37b6("   Copyright  (c) 1991   ", 8, 17);
#else
    g2_37b6("   Copyright  (c) 1991  ", 8, 17);
#endif
}
