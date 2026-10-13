void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_37b6(char far *s, int x, int y) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_43f5(void)
{
    g2_3d8c(0, 9, 2);
#if EPISODE == 1
    g2_37b6("Once my forces are     ", 1, 0x13);
    g2_37b6("together, I'll be back ", 1, 0x14);
    g2_37b6("to rule Earth.         ", 1, 0x15);
#elif EPISODE == 2
    g2_37b6("But escaping to Earth's", 1, 0x13);
    g2_37b6("future will!  Then my", 1, 0x14);
    g2_37b6("Techbot army can build", 1, 0x15);
    g2_37b6("and return victorious!", 1, 0x16);
#else
    g2_37b6("Butthead, it's buthead!!", 1, 0x13);
    g2_37b6("                     ", 1, 0x14);
    g2_37b6("     ", 1, 0x15);
#endif
    g2_2870(0x18, 0x16);
}
