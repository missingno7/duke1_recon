extern char d_a0fa_;
void pascal g2_37b6(char far *a0, int a1, int a2);    /* accepted signature */
/*@body*/
void pascal g2_1bfb(register int a0)
{
    g2_37b6("Important Keys:         ", a0 + 1, 4);
    g2_37b6("  CTRL - Jump           ", a0 + 1, 5);
    g2_37b6("  ALT  - Fire           ", a0 + 1, 6);
    g2_37b6("  Cursor Keys - Move Man", a0 + 1, 7);
    g2_37b6("  Up Cursor - Action Key", a0 + 1, 8);
    g2_37b6("                        ", a0 + 1, 9);
    g2_37b6("Change keys by choosing ", a0 + 1, 10);
    g2_37b6("option \"K\" in HELP MENU.", a0 + 1, 11);
    g2_37b6("                        ", a0 + 1, 12);
    g2_37b6("  \"S\" - Toggle Sound    ", a0 + 1, 13);
    g2_37b6("  \"H\" - Toggle Hint Mode", a0 + 1, 14);
    g2_37b6("  F10 - Restart Level   ", a0 + 1, 15);
    g2_37b6("  ESC - Quit Game       ", a0 + 1, 16);
    g2_37b6("  \"<\" - Decrease Speed  ", a0 + 1, 17);
    g2_37b6("  \">\" - Increase Speed  ", a0 + 1, 18);
    g2_37b6("                        ", a0 + 1, 19);
    g2_37b6("     Press any key.     ", a0 + 1, 20);
    while ((d_a0fa_ & 0x80) == 0)
        ;
}
