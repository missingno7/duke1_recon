extern char d_a0fa_;
extern char d_cc81_;
void pascal g1_0042(int a0);
void g2_3114(void) {}
void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_37b6(char far *a0, int a1, int a2) {}
void pascal g2_0036(int a0) {}
void pascal g2_2870(int a0, int a1) {}
void pascal g2_01a9(int a0) {}
void g2_3fe1(void) {}
void g2_02f4(void) {}
void g2_0491(void) {}
/*@body*/
void pascal g2_452b(register int a0)
{
    g2_3114();
    g1_0042(0x2c);
#if EPISODE == 1
    g2_3d8c(a0, 2, 7);
    g2_37b6("     TO BE CONTINUED     ", a0 + 1, 5);
    g2_37b6("------------------------", a0 + 1, 6);
    g2_37b6("In episode two, Duke     ", a0 + 1, 8);
    g2_37b6("rockets to the moon to   ", a0 + 1, 9);
    g2_37b6("infiltrate Dr. Proton's  ", a0 + 1, 10);
    g2_37b6("massive lunar fortress.  ", a0 + 1, 11);
    g2_37b6("                         ", a0 + 1, 12);
    g2_37b6("Continue your adventure  ", a0 + 1, 13);
    g2_37b6("in \"Mission: Moonbase\",  ", a0 + 1, 14);
    g2_37b6("where you'll encounter:  ", a0 + 1, 15);
    g2_37b6("New levels, new puzzles,", a0 + 1, 16);
    g2_37b6("new graphics, and more   ", a0 + 1, 17);
    g2_37b6("non-stop action.         ", a0 + 1, 18);
#elif EPISODE == 2
    g2_3d8c(a0, 2, 7);
    g2_37b6("     TO BE CONTINUED    ", a0 + 1, 5);
    g2_37b6("------------------------", a0 + 1, 6);
    g2_37b6("Once again you've given ", a0 + 1, 8);
    g2_37b6("Dr. Proton a major set- ", a0 + 1, 9);
    g2_37b6("back, by destroying his ", a0 + 1, 10);
    g2_37b6("lunar fortress.         ", a0 + 1, 11);
    g2_37b6("                        ", a0 + 1, 12);
    g2_37b6("Continue your adventure ", a0 + 1, 13);
    g2_37b6("in \"Trapped in the      ", a0 + 1, 14);
    g2_37b6("Future\"!  Duke must     ", a0 + 1, 15);
    g2_37b6("chase Dr. Proton into   ", a0 + 1, 16);
    g2_37b6("Earth's future to stop  ", a0 + 1, 17);
    g2_37b6("the largest threat yet! ", a0 + 1, 18);
#else
    g2_3d8c(a0, 1, 10);
    g2_37b6("    CONGRATULATIONS     ", a0 + 1, 3);
    g2_37b6("------------------------", a0 + 1, 4);
    g2_37b6(" Dr. Proton is finally  ", a0 + 1, 6);
    g2_37b6("       defeated!        ", a0 + 1, 7);
    g2_37b6("                        ", a0 + 1, 8);
    g2_37b6("Using Proton's time warp", a0 + 1, 9);
    g2_37b6(" device Duke returns to ", a0 + 1, 10);
    g2_37b6(" Earth's present and is ", a0 + 1, 11);
    g2_37b6("presented the key to the", a0 + 1, 12);
    g2_37b6(" city he saved. (Yeah.) ", a0 + 1, 13);
    g2_37b6(" Did you locate all the ", a0 + 1, 15);
    g2_37b6("  hidden rooms on each  ", a0 + 1, 16);
    g2_37b6("  level?  On your next  ", a0 + 1, 17);
    g2_37b6("   Apogee games order   ", a0 + 1, 18);
    g2_37b6("please tell us your best", a0 + 1, 19);
    g2_37b6(" Duke Nukum high score. ", a0 + 1, 20);
    g2_37b6("                        ", a0 + 1, 21);
    g2_37b6(" Thank you for playing! ", a0 + 1, 22);
#endif
    g2_0036(0xf);
    if (d_cc81_ == 0) {
        while ((d_a0fa_ & 0x80) == 0) {
        }
    }
#if EPISODE == 3
    g2_2870(a0 + 0x18, 0x16);
#else
    g2_2870(a0 + 0x18, 0x12);
#endif
    g2_01a9(0xf);
    g2_3fe1();
    g2_02f4();
    g2_2870(0x27, 0x18);
    g2_3114();
    g2_0491();
    g2_2870(0x27, 0x18);
    g2_2870(0x27, 0x18);
}

