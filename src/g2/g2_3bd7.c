extern void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *p, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_3bd7(void)
{
    g2_3d8c(0, 9, 2);
#if EPISODE == 1
    g2_37b6("So you're the pitiful   ", 1, 0x13);
    g2_37b6("hero they sent to stop  ", 1, 0x14);
    g2_37b6("me.  I, Dr. Proton, will", 1, 0x15);
    g2_37b6("soon rule the world!    ", 1, 0x16);
#elif EPISODE == 2
    g2_37b6("So Duke, you managed to ", 1, 0x13);
    g2_37b6("find my secret moonbase.", 1, 0x14);
    g2_37b6("My Techbots will soon", 1, 0x15);
    g2_37b6("be the end of you.", 1, 0x16);
#else
    g2_37b6("Now that I've warped to ", 1, 0x13);
    g2_37b6("Earth's future, Duke the", 1, 0x14);
    g2_37b6("Fluke cannot stop me.", 1, 0x15);
#endif
    g2_2870(0x18, 0x16);
}
