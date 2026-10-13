void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_37b6(char far *p, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_4444(void)
{
    g2_3d8c(10, 9, 2);
#if EPISODE == 1
    g2_37b6("Not if I can stop you ", 0xb, 0x13);
    g2_37b6("first...              ", 0xb, 0x14);
    g2_37b6("                      ", 0xb, 0x15);
    g2_37b6("     Here I come!     ", 0xb, 0x16);
#elif EPISODE == 2
    g2_37b6("Not if I can find a way", 0xb, 0x13);
    g2_37b6("to stop you...even if", 0xb, 0x14);
    g2_37b6("I have to follow you", 0xb, 0x15);
    g2_37b6("into the future...!", 0xb, 0x16);
#else
    g2_37b6("The spelling of yours", 0xb, 0x13);
    g2_37b6("is getting better!", 0xb, 0x14);
    g2_37b6("", 0xb, 0x15);
#endif
    g2_2870(0x22, 0x16);
}

