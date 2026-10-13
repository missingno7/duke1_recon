extern void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *p, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_3c38(void)
{
    g2_3d8c(10, 9, 2);
#if EPISODE == 1
    g2_37b6("You're wrong, Proton    ", 11, 0x13);
    g2_37b6("breath.  I'll be done   ", 11, 0x14);
    g2_37b6("with you and still have ", 11, 0x15);
    g2_37b6("time to watch Oprah!    ", 11, 0x16);
#elif EPISODE == 2
    g2_37b6("Your Techbots were", 11, 0x13);
    g2_37b6("beaten on Earth and I'll", 11, 0x14);
    g2_37b6("defeat them here. Your", 11, 0x15);
    g2_37b6("terror will soon end.", 11, 0x16);
#else
    g2_37b6("I need to find Dr.", 11, 0x13);
    g2_37b6("Proton's time machine", 11, 0x14);
    g2_37b6("or Earth is doomed!", 11, 0x15);
#endif
    g2_2870(0x22, 0x16);
}
