/* Dr. Proton taunt shown at the end of a level; text differs per episode. */
void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_37b6(char far *s, int x, int y) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_4334(void)
{
    g2_3d8c(0, 9, 2);
#if EPISODE == 1
    g2_37b6("You may have defeated me", 1, 0x13);
    g2_37b6("on Earth, but on the    ", 1, 0x14);
    g2_37b6("Moon I can make plans   ", 1, 0x15);
    g2_37b6("for my ulimate attack!  ", 1, 0x16);
#elif EPISODE == 2
    g2_37b6("Duke, your lucky ways   ", 1, 0x13);
    g2_37b6("annoy me.  I see now    ", 1, 0x14);
    g2_37b6("how best to be rid of", 1, 0x15);
    g2_37b6("of your pesky presence.", 1, 0x16);
#else
    g2_37b6("You will never get me,  ", 1, 0x13);
    g2_37b6("Duke!  Watch your self", 1, 0x14);
    g2_37b6("you here!.", 1, 0x15);
#endif
    g2_2870(0x18, 0x16);
}
