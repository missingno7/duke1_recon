void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_37b6(char far *a0, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void g2_44a5(void)
{
    g2_3d8c(10, 9, 2);
#if EPISODE == 1 || EPISODE == 2
    g2_37b6("I won it all!!!!!!!", 0xb, 0x13);
    g2_37b6("         ", 0xb, 0x14);
    g2_37b6("", 0xb, 0x15);
#else
    g2_37b6("Finally, Earth is free", 0xb, 0x13);
    g2_37b6("from Dr. Proton and", 0xb, 0x14);
    g2_37b6("his Techbot menace.", 0xb, 0x15);
    g2_37b6("", 0xb, 0x16);
#endif
    g2_2870(0x22, 0x16);
}


