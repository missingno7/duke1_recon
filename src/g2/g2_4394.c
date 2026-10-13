void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_37b6(char far *a0, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_4394(void)
{
    g2_3d8c(10, 9, 2);
#if EPISODE == 1
    g2_37b6("Proton, you coward!  You", 0x0b, 0x13);
    g2_37b6("can run but you can't   ", 0x0b, 0x14);
    g2_37b6("hide!                   ", 0x0b, 0x15);
    g2_37b6("                        ", 0x0b, 0x16);
#elif EPISODE == 2
    g2_37b6("There's IS no place to", 0x0b, 0x13);
    g2_37b6("hide from me.  Running", 0x0b, 0x14);
    g2_37b6("back to Earth will not", 0x0b, 0x15);
    g2_37b6("save you.", 0x0b, 0x16);
#else
    g2_37b6("You'll not get away", 0x0b, 0x13);
    g2_37b6("butthead!", 0x0b, 0x14);
    g2_37b6("", 0x0b, 0x15);
#endif
    g2_2870(0x22, 0x16);
}
