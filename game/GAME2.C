/* GAME2.C - second translation unit (menus, text screens, high scores, timer and sound) of Duke Nukum v2.0. */

#define UNIT 2      /* selects this unit's declarations in duke.h */
#include "duke.h"

/* ---- uninitialised data (BSS) ---- */

/* G2 BSS objects in ascending DN1 address order. Each typed array spans to the next object start. */






















/* 0xa0f4; accepted scalar type. */
void interrupt far (*d_a0f4_)(void);
/* 0xa0f8; accepted scalar type. */
int d_a0f8_;
/* 0xa0fa; accepted scalar type. */
char d_a0fa_;
/* 0xa0fb; accepted scalar type. */
char far *d_a0fb_;
/* 0xa0ff; array extent from address gap. */
struct g1_54e1_record d_a0ff_[100];
/* 0xa357; array extent from address gap. */
struct g1_79d9_record d_a357_[100];
/* 0xa677; accepted scalar type. */
int d_a677_;
/* 0xa679; accepted scalar type. */
int d_a679_;
/* 0xa67b; accepted scalar type. */
int d_a67b_;
/* 0xa67d; accepted scalar type. */
char d_a67d_;
/* 0xa67e; accepted scalar type. */
int d_a67e_;
/* 0xa680; array extent from address gap. */
struct g1_af94_record d_a680_[100];
/* 0xa8d8; accepted scalar type. */
char d_a8d8_;
/* 0xa8d9; accepted scalar type. */
char d_a8d9_;
/* 0xa8da; array extent from address gap. */
struct g1_3882_record d_a8da_[100];
/* 0xab32; array extent from address gap. */
struct g1_5d6f_record d_ab32_[20];
/* 0xabd2; accepted scalar type. */
int d_abd2_;
/* 0xabd4; array extent from address gap. */
int d_abd4_[9];
/* 0xabe6; accepted scalar type. */
int d_abe6_;
/* UNREFERENCED: [0xabe8,0xabec) has no accepted object start or direct DS reference. */
char d_abe8_[4];
/* 0xabec; array extent from address gap. */
struct g1_5b0b_record d_abec_[100];
/* 0xae44; array extent from address gap. */
struct g1_a218_record d_ae44_[100];
/* 0xb09c; array extent from address gap. */
int d_b09c_[9];
/* 0xb0ae; accepted scalar type. */
int d_b0ae_;
/* UNREFERENCED: [0xb0b0,0xb0b4) has no accepted object start or direct DS reference. */
char d_b0b0_[4];
/* 0xb0b4; array extent from address gap. */
struct g1_5f0c_record d_b0b4_[100];
/* 0xb3d4; accepted scalar type. */
int d_b3d4_;
/* 0xb3d6; array extent from address gap. */
struct t_b3d6 d_b3d6_[100];
/* 0xb62e; accepted scalar type. */
int d_b62e_;
/* 0xb630; accepted scalar type. */
int d_b630_;
/* 0xb632; accepted scalar type. */
int d_b632_;
/* 0xb634; accepted scalar type. */
int d_b634_;
/* 0xb636; accepted scalar type. */
int d_b636_;
/* 0xb638; accepted scalar type. */
char far *d_b638_;
/* 0xb63c; array extent from address gap. */
struct t_b63c d_b63c_[16];
/* 0xb6bc; array extent from address gap. */
struct g1_4f91_record d_b6bc_[100];
/* 0xb9dc; accepted scalar type. */
int d_b9dc_;
/* 0xb9de; array extent from address gap. */
struct t_b9de d_b9de_[200];
/* 0xc01e; array extent from address gap. */
struct g1_7163_record d_c01e_[100];
/* 0xc276; accepted scalar type. */
int d_c276_;
/* 0xc278; accepted scalar type. */
char d_c278_;
/* 0xc279; accepted scalar type. */
int d_c279_;
/* 0xc27b; accepted scalar type. */
int d_c27b_;
/* 0xc27d; accepted scalar type. */
char far *d_c27d_;
/* 0xc281; accepted scalar type. */
int d_c281_;
/* 0xc283; accepted scalar type. */
int d_c283_;
/* 0xc285; accepted scalar type. */
char far *d_c285_;
/* 0xc289; accepted scalar type. */
int d_c289_;
/* 0xc28b; accepted scalar type. */
int d_c28b_;
/* 0xc28d; accepted scalar type. */
int d_c28d_;
/* 0xc28f; accepted scalar type. */
char far *d_c28f_;
/* 0xc293; accepted scalar type. */
int d_c293_;
/* 0xc295; accepted scalar type. */
int d_c295_;
/* 0xc297; accepted scalar type. */
int d_c297_;
/* 0xc299; array extent from address gap. */
struct Record d_c299_[100];
/* 0xc681; accepted scalar type. */
int d_c681_;
/* 0xc683; accepted scalar type. */
char d_c683_;
/* 0xc684; accepted scalar type. */
int d_c684_;
/* 0xc686; accepted scalar type. */
int d_c686_;
/* 0xc688; accepted scalar type. */
int d_c688_;
/* 0xc68a; accepted scalar type. */
int d_c68a_;
/* 0xc68c; accepted scalar type. */
char d_c68c_;
/* 0xc68d; accepted scalar type. */
int d_c68d_;
/* 0xc68f; accepted scalar type. */
int d_c68f_;
/* 0xc691; array extent from address gap. */
struct record d_c691_[100];
/* 0xc8e9; accepted scalar type. */
int d_c8e9_;
/* 0xc8eb; array extent from address gap. */
struct t_c8eb d_c8eb_[7];
/* 0xc915; array extent from address gap. */
struct g1_9757_row d_c915_[100];
/* 0xcb6d; array extent from address gap. */
struct t_cb6d d_cb6d_[9];
/* 0xcbb5; array extent from address gap. */
char far *d_cbb5_[50];
/* 0xcc7d; accepted scalar type. */
char far *d_cc7d_;
/* 0xcc81; accepted scalar type. */
char d_cc81_;
/* 0xcc82; accepted scalar type. */
int d_cc82_;
/* 0xcc84; array extent from address gap. */
struct g1_c1b2_record d_cc84_[200];
/* 0xd134; accepted scalar type. */
char d_d134_;
/* 0xd135; accepted scalar type. */
char d_d135_;
/* 0xd136; accepted scalar type. */
int d_d136_;
/* 0xd138; accepted scalar type. */
char d_d138_;
/* 0xd139; accepted scalar type. */
int d_d139_;
/* 0xd13b; accepted scalar type. */
int d_d13b_;
/* 0xd13d; accepted scalar type. */
int d_d13d_;
/* 0xd13f; accepted scalar type. */
char d_d13f_;
/* 0xd140; accepted scalar type. */
int d_d140_;
/* 0xd142; accepted scalar type. */
int d_d142_;
/* 0xd144; accepted scalar type. */
unsigned int d_d144_;
/* 0xd146; accepted scalar type. */
int d_d146_;
/* 0xd148; accepted scalar type. */
char d_d148_;
/* 0xd149; array extent from address gap. */
int d_d149_[1];
/* 0xd14b; accepted scalar type. */
int d_d14b_;
/* 0xd14d; accepted scalar type. */
int d_d14d_;
/* UNREFERENCED: [0xd14f,0xd155) has no accepted object start or direct DS reference. */
char d_d14f_[6];
/* 0xd155; accepted scalar type. */
int d_d155_;
/* 0xd157; array extent from address gap. */
struct t_b9de d_d157_[15];
/* 0xd1cf; array extent from address gap. */
struct t_d1cf d_d1cf_[20];
/* 0xd247; accepted scalar type. */
int d_d247_;
/* 0xd249; array extent from address gap. */
int d_d249_[12];
/* 0xd261; array extent from address gap. */
struct g1_6e71_record d_d261_[100];
/* 0xd4b9; accepted scalar type. */
int d_d4b9_;
/* 0xd4bb; accepted scalar type. */
int d_d4bb_;
/* 0xd4bd; accepted scalar type. */
int d_d4bd_;
/* 0xd4bf; accepted scalar type. */
char d_d4bf_;
/* 0xd4c0; accepted scalar type. */
char d_d4c0_;
/* 0xd4c1; accepted scalar type. */
int d_d4c1_;
/* 0xd4c3; array extent from address gap. */
struct s8 d_d4c3_[21];
/* 0xd56b; accepted scalar type. */
char d_d56b_;
/* 0xd56c; accepted scalar type. */
int d_d56c_;
/* 0xd56e; accepted scalar type. */
int d_d56e_;
/* 0xd570; accepted scalar type. */
int d_d570_;
/* 0xd572; accepted scalar type. */
int d_d572_;
/* 0xd574; accepted scalar type. */
int d_d574_;
/* 0xd576; accepted scalar type. */
char d_d576_;
/* 0xd577; accepted scalar type. */
int d_d577_;
/* 0xd579; accepted scalar type. */
char d_d579_;
/* 0xd57a; accepted scalar type. */
int d_d57a_;
/* 0xd57c; accepted scalar type. */
int d_d57c_;
/* 0xd57e; array extent from address gap. */
int d_d57e_[100];
/* 0xd646; array extent from address gap. */
int d_d646_[100];
/* 0xd70e; accepted scalar type. */
int d_d70e_;
/* 0xd710; accepted scalar type. */
char far *d_d710_;
/* 0xd714; accepted scalar type. */
char far *d_d714_;
/* 0xd718; accepted scalar type. */
int d_d718_;

/* ---- initialised data ---- */

/* G2 initialised data (DGROUP 0x0b46..0x0f2b in every episode), in definition order.
   Defined before the first function so that the strings of the two pointer tables
   open the unit's literal pool (rule DATA-LAYOUT).  Proven by
   `python tools/tubuild.py G2_TEXT --data`.  d_0cd1 is not referenced by any code. */
#if EPISODE == 1
char d_0b46 = 1;
#elif EPISODE == 2
char d_0b46 = 0;
#else
char d_0b46 = 0;
#endif
#if EPISODE == 1
char far *d_0b47[22] = {
    "drop0.dn1",
    "drop3.dn1",
    "drop0.dn1",
    "drop3.dn1",
    "drop7.dn1",
    "drop3.dn1",
    "drop3.dn1",
    "drop5.dn1",
    "drop7.dn1",
    "drop7.dn1",
    "drop2.dn1",
    "drop2.dn1",
    "drop1.dn1",
    "drop2.dn1",
    "drop3.dn1",
    "drop3.dn1",
    "drop5.dn1",
    "drop2.dn1",
    "drop0.dn1",
    "drop11.dn1",
    "drop13.dn1",
    "drop9.dn1"
};
#elif EPISODE == 2
char far *d_0b47[22] = {
    "drop8.dn2",
    "drop9.dn2",
    "drop9.dn2",
    "drop9.dn2",
    "drop8.dn2",
    "drop5.dn2",
    "drop11.dn2",
    "drop2.dn2",
    "drop3.dn2",
    "drop9.dn2",
    "drop3.dn2",
    "drop3.dn2",
    "drop5.dn2",
    "drop8.dn2",
    "drop1.dn2",
    "drop1.dn2",
    "drop5.dn2",
    "drop2.dn2",
    "drop8.dn2",
    "drop11.dn2",
    "drop13.dn2",
    "drop9.dn2"
};
#elif EPISODE == 3
char far *d_0b47[22] = {
    "drop0.dn3",
    "drop10.dn3",
    "drop10.dn3",
    "drop3.dn3",
    "drop6.dn3",
    "drop5.dn3",
    "drop12.dn3",
    "drop12.dn3",
    "drop12.dn3",
    "drop13.dn3",
    "drop1.dn3",
    "drop1.dn3",
    "drop0.dn3",
    "drop0.dn3",
    "drop2.dn3",
    "drop6.dn3",
    "drop2.dn3",
    "drop2.dn3",
    "drop13.dn3",
    "drop2.dn3",
    "drop13.dn3",
    "drop9.dn3"
};
#endif
int d_0b9f = 0;
#if EPISODE == 1
char far *d_0ba1[76] = {
    "\0",
    "\0",
    "\0",
    "\0",
    "You are entering the",
    "next level.  Now is a",
    "good time to SAVE your",
    "game.               ",
    "Surprise Duke, I'll be  ",
    "tracking your every move",
    "with my security camera ",
    "system!                 ",
    "On the next level you'll",
    "need to find a special",
    "access card that looks",
    "like a computer board.",
    "",
    "",
    "",
    "",
    "If you find the boots on",
    "the next level you'll be",
    "able to jump higher!",
    "SAVE your game now.   ",
    "I see you're still      ",
    "trying Duke. Never mind,",
    "my robot drones will    ",
    "soon be the end of you! ",
    "The next level is very",
    "tough--but there's also",
    "a secret shortcut!",
    "Don't forget to SAVE.",
    "Hmmm...  I see you've   ",
    "survived my Maze of     ",
    "Madness.  I might have  ",
    "underestimated you.     ",
    "You are doing quite well",
    "so far...let's see if   ",
    "you can keep it up. Also",
    "remember to SAVE.       ",
    "Duke, in spite of your  ",
    "persistance, my plan to ",
    "rule Earth will not be  ",
    "stopped.  Ah, ha, ha!   ",
    "Find the GRAPPLING HOOKS",
    "to beat the next level. ",
    "Use them to grab on to  ",
    "special grated ceilings.",
    "Why bother Duke?  Not   ",
    "even Commander Keen     ",
    "could survive the perils",
    "of my Mercury Mines!    ",
    "There are several secret",
    "bonuses you can earn on",
    "each level!  Register to",
    "get the complete list.",
    "I hate heroes! Your luck",
    "is about to run out.    ",
    "Perhaps now would be a  ",
    "good time to flee, Duke!",
    "Secret Bonus Hint:      ",
    "Collect the letters     ",
    "D, U, K, E in order to  ",
    "earn bonus number five. ",
    "Duke, join me now and   ",
    "live, or continue this  ",
    "foolishness and I'll    ",
    "squash you myself!      ",
    "You are about to enter",
    "the secret Bubble City",
    "fortress of Dr. Proton.",
    "There's no turning back!",
    "I'm coming down to crush",
    "you, Duke.  It's just   ",
    "you and me now.         ",
    "                        "
};
#elif EPISODE == 2
char far *d_0ba1[76] = {
    "\0",
    "\0",
    "\0",
    "\0",
    "You are about to enter  ",
    "the next level.  Don't  ",
    "forget to SAVE your     ",
    "game.  Good luck!       ",
    "Ah ha, Duke.  I see even",
    "with your stunted       ",
    "abilities you managed to",
    "find my moonbase.       ",
    "Hint:  You'll need to   ",
    "collect the robot hand  ",
    "to help you survive the ",
    "next level!             ",
    "You lose, Duke Pukem,   ",
    "I'm sending my newly    ",
    "improved Techbots to    ",
    "dispense with you!      ",
    "You might find that the ",
    "next level is too windy ",
    "for you...!             ",
    "                        ",
    "Duke, you make me laugh!",
    "Which is why it's almost",
    "sad to know you'll soon ",
    "be moon dust...         ",
    "You might find your     ",
    "super jump boots on the ",
    "next level if you look  ",
    "hard enough...          ",
    "Duke, you used to make  ",
    "me laugh--but now you're",
    "beginning to upset me.  ",
    "You will not last long! ",
    "Now entering an ancient ",
    "underground lunar city! ",
    "Beware of the snake     ",
    "Techbot!                ",
    "                        ",
    "                        ",
    "                        ",
    "                        ",
    "Hint:  The grappling    ",
    "hooks will \"lift\" your  ",
    "chances of completing   ",
    "the next level.         ",
    "                        ",
    "                        ",
    "                        ",
    "                        ",
    "You are about to enter  ",
    "the next level.  Don't  ",
    "forget to SAVE your     ",
    "game.                   ",
    "Tell me Duke, is all of ",
    "that lava down there as ",
    "hot as it looks?        ",
    "Ha, ha, ha, haaa...     ",
    "Dr. Proton's lunar hide-",
    "out is very, very close!",
    "Be prepared for any     ",
    "surprises or traps...   ",
    "Confused Duke?  Your    ",
    "perilously low intellect",
    "will accelerate your    ",
    "demise in my maze!      ",
    "The final challenge is  ",
    "ahead--Dr. Proton's     ",
    "secret lunar fortress!  ",
    "                        ",
    "Are you ready to lose,  ",
    "Duke?  Then enter my    ",
    "secret chamber...       ",
    "                        "
};
#elif EPISODE == 3
char far *d_0ba1[76] = {
    "\0",
    "\0",
    "\0",
    "\0",
    "You are about to enter  ",
    "the next level.  Be sure",
    "to SAVE your game.      ",
    "",
    "Duke, you've tracked me ",
    "to the Moon and into    ",
    "Earth's future.  Don't  ",
    "you ever take a break?  ",
    "You are about to enter  ",
    "the next level.  Be sure",
    "to SAVE your game.      ",
    "",
    "",
    "",
    "",
    "",
    "HINT:  You will need to ",
    "find your super jump    ",
    "boots on the next level.",
    "",
    "Duke, I see you where-  ",
    "ever you go.  And I have",
    "devised many traps that ",
    "will end your mission.  ",
    "Hint:  Look for the time",
    "transport machine to    ",
    "help you solve the next ",
    "level.                 ",
    "",
    "",
    "",
    "",
    "Hint:  The robot hand is",
    "very well hidden--but   ",
    "must be found!          ",
    "",
    "I am warning you, Duke. ",
    "It is about time I show ",
    "you the awesome power of",
    "Dr. Proton!             ",
    "You have done well to   ",
    "survive this far, but   ",
    "what lies ahead may be  ",
    "your match!",
    "",
    "",
    "",
    "",
    "You are about to enter  ",
    "the next level.  Be sure",
    "to SAVE your game.      ",
    "",
    "So Duke, did you enjoy  ",
    "my killer rabbitoids?   ",
    "Nothing will out last   ",
    "them...Ah, ha, ha...!   ",
    "Keep going Duke, we're  ",
    "counting on you...!     ",
    "                        ",
    "                        ",
    "",
    "",
    "",
    "",
    "Unless you can stop Dr. ",
    "Proton, Earth will be   ",
    "helpless against his    ",
    "mindless Techbots.",
    "Duke, I'm coming to     ",
    "crush you myself!  Earth",
    "is mine, and so will be ",
    "victory over you!       "
};
#endif
unsigned char d_0cd1[16] = { 0 };
unsigned char d_0ce1[35] = { 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 0, 0, 0, 0 };
char d_0d04[550] = "                           DUKE NUKUM is one of the best, feature-packed games ever made for an IBM PC! It beats Nintendo easily!    DUKE NUKUM features:     Incredible animation,   One megabyte of graphics, dual scrolling playfields,  arcade sound effects,     and much, much more...! A built in Hint Mode makes learning the game easy!    Supports joystick, too.   You'll find dozens of    secret rooms with prizes. Duke can somersault and   cling onto ceilings with     his special hooks.       GET DUKE NUKUM NOW!                             ";
int d_0f2a = 0;

void pascal g2_0009(int a0)
{
    register int i;
    for (i = 0; i < 16; ++i) {
        delay(a0);
        asm_029d(i, 0x17);
    }
}

void pascal g2_0036(register int a0)
{
    asm_029d(0, 0);
    delay(a0);
    asm_029d(1, 1);
    delay(a0);
    asm_029d(2, 2);
    delay(a0);
    asm_029d(3, 3);
    delay(a0);
    asm_029d(4, 4);
    delay(a0);
    asm_029d(5, 5);
    delay(a0);
    asm_029d(6, 6);
    delay(a0);
    asm_029d(7, 7);
    delay(a0);
    asm_029d(8, 16);
    delay(a0);
    asm_029d(9, 17);
    delay(a0);
    asm_029d(10, 18);
    delay(a0);
    asm_029d(11, 19);
    delay(a0);
    asm_029d(12, 20);
    delay(a0);
    asm_029d(13, 21);
    delay(a0);
    asm_029d(14, 22);
    delay(a0);
    asm_029d(15, 23);
    delay(a0);
}

/* g2_01a9 candidate */
void pascal g2_01a9(int value)
{
    register int i;
    for (i = 0; i < 16; ++i) {
        delay(value);
        asm_029d(i, 0);
    }
}

void g2_01d5(void)
{
    asm_05eb(!d_6e0a_);
    asm_05f7(d_6e0a_);
}

void pascal g2_01f5(int mode, int far *a1, int far *a2)
{
    int second;
    int mask1;
    int mask2;
    register int state;
    register int first;

    if (mode == 1) {
        mask1 = 1;
        mask2 = 2;
    } else {
        mask1 = 4;
        mask2 = 8;
    }
    *a1 = 0;
    *a2 = 0;
    disable();
    outportb(0x201, inportb(0x201));
    do {
        state = inportb(0x201);
        first = (state & mask1) != 0;
        second = (state & mask2) != 0;
        *a1 += first;
        *a2 += second;
    } while (first + second != 0 && *a1 < 500 && *a2 < 500);
    enable();
}

void pascal g2_0286(int a0)
{
    register int si;
    register int di;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    asm_05eb(0);
    asm_05f7(0);
    for (di = 0; di < 25; di++) {
        for (si = 0; si < 20; si++) {
            asm_02ad(a0, si * 2 + di * 640);
        }
    }
}

void g2_02f4(void)
{
    g2_01a9(0x14);
    g2_0286(0x1710);
    g2_37b6("          ORDERING INFORMATION          ", 0, 0);
    g2_37b6("      Duke Nukum consists of three      ", 0, 2);
    g2_37b6("    unique and challenging episodes!    ", 0, 3);
    g2_37b6("                                        ", 0, 4);
    g2_37b6(" Episode ONE:    Shrapnel City          ", 0, 5);
    g2_37b6(" Episode TWO:    Mission: Moonbase      ", 0, 6);
    g2_37b6(" Episode THREE:  Trapped in the Future! ", 0, 7);
    g2_37b6("                                        ", 0, 8);
    g2_37b6("  You can order each episode for $15.   ", 0, 9);
    g2_37b6("  Or for only $30, you'll receive all   ", 0, 10);
    g2_37b6("     three episodes, and also get:      ", 0, 11);
    g2_37b6("                                        ", 0, 12);
    g2_37b6(" 1) The \"Secret Hints and Tips\" sheet!  ", 0, 13);
    g2_37b6(" 2) A \"Cheat Mode\" password that will   ", 0, 14);
    g2_37b6("    give you FULL FIREPOWER and ALL THE ", 0, 15);
    g2_37b6("    KEYS to each level!                 ", 0, 16);
    g2_37b6(" 3) Several HOT new bonus games!        ", 0, 17);
    g2_37b6("                                        ", 0, 18);
    g2_37b6("   Each episode is set in an entirely   ", 0, 19);
    g2_37b6(" new location, with exciting challenges ", 0, 20);
    g2_37b6(" and of course, more adventure than any ", 0, 21);
    g2_37b6("       human can possibly handle!       ", 0, 22);
    g2_37b6("  Press any key for more information... ", 0, 24);
    g2_0036(0x14);
}

void g2_0491(void)
{
    g2_0286(0x1710);
    g2_37b6("          ORDERING INFORMATION          ", 0, 0);
    g2_37b6("  Order NOW by sending a check or money ", 0, 2);
    g2_37b6("   order for $30 (add $3 shipping) to:  ", 0, 3);
    g2_37b6("                                        ", 0, 4);
    g2_37b6("            Apogee Software             ", 0, 5);
    g2_37b6("            P.O. Box 476389             ", 0, 6);
    g2_37b6("         Garland, TX  75047  (USA)      ", 0, 7);
    g2_37b6("                                        ", 0, 8);
    g2_37b6("  Order NOW toll free:  1-800-852-5659  ", 0, 9);
    g2_37b6("    (Visa and MasterCard accepted!)     ", 0, 10);
    g2_37b6("                                        ", 0, 11);
    g2_37b6("   Specify disk size:  5.25\" or 3.5\".   ", 0, 12);
    g2_37b6("                                        ", 0, 13);
    g2_37b6("  Foreign orders: Please read the file  ", 0, 14);
    g2_37b6("    FOREIGN.DOC to place your order.    ", 0, 15);
    g2_37b6("                                        ", 0, 16);
    g2_37b6(" Order today and continue your exciting ", 0, 17);
    g2_37b6(" adventures as Duke Nukum.  Once again, ", 0, 18);
    g2_37b6("  for $33 (including shipping) you'll   ", 0, 19);
    g2_37b6("  get all three updated episodes, the   ", 0, 20);
    g2_37b6("     cheat mode, and the hints and      ", 0, 21);
    g2_37b6("       tricks sheet.  Thank you!        ", 0, 22);
    g2_37b6("             Press any key.             ", 0, 24);
    if (d_cc81_ == 0) {
        while ((d_a0fa_ & 0x80) == 0) {
        }
    }
}

/* g2_062c candidate */
void g2_062c(void)
{
    g2_01a9(0x14);
    g2_0286(0x1710);
    g2_37b6("                THE STORY               ", 0, 0);
    g2_37b6("The year is 1997.  Doctor Proton and his", 0, 2);
    g2_37b6(" army of Techbots have taken control of ", 0, 3);
    g2_37b6("Earth's largest city.   Once a respected", 0, 4);
    g2_37b6("    genius and scientist, Dr. Proton    ", 0, 5);
    g2_37b6(" (he changed his name from Blunderwitz  ", 0, 6);
    g2_37b6(" early in his career) decided he could  ", 0, 7);
    g2_37b6("   rule Earth with a new world order.   ", 0, 8);
    g2_37b6("                                        ", 0, 9);
    g2_37b6("After a terrible radiation accident that", 0, 10);
    g2_37b6(" altered his brain,  Dr. Proton took to ", 0, 11);
    g2_37b6("  the underworld and developed an army  ", 0, 12);
    g2_37b6(" of advanced robots -- called Techbots. ", 0, 13);
    g2_37b6("  The Techbots are extremely dangerous, ", 0, 14);
    g2_37b6(" and guard Dr. Proton's secret hideout. ", 0, 15);
    g2_37b6("    Every attempt by the military to    ", 0, 16);
    g2_37b6(" overcome Dr. Proton ended in disaster. ", 0, 17);
    g2_37b6("   It seems Dr. Proton's plan to rule   ", 0, 18);
    g2_37b6("        Earth is well underway...       ", 0, 19);
    g2_37b6("             Press any key.             ", 0, 24);
    g2_0036(0x14);
    if (d_cc81_ == 0)
        while ((d_a0fa_ & 0x80) == 0)
            ;
    g2_2870(0x27, 0x18);
    g2_0286(0x1710);
    g2_37b6("                THE STORY               ", 0, 0);
    g2_37b6("   Self-proclaimed hero Duke Nukum is   ", 0, 2);
    g2_37b6("   Earth's final chance. Hired by the   ", 0, 3);
    g2_37b6("    CIA, Duke has orders to stop Dr.    ", 0, 4);
    g2_37b6("    Proton and rid the world of this    ", 0, 5);
    g2_37b6("  latest madman.  Armed only with his   ", 0, 6);
    g2_37b6("  pistol and his can-do attitude, Duke  ", 0, 7);
    g2_37b6("  is the one person who might stand a   ", 0, 8);
    g2_37b6("            chance of success.          ", 0, 9);
    g2_26d5();
    if (d_cc81_ == 0)
        while ((d_a0fa_ & 0x80) == 0)
            ;
    g2_2870(0x27, 0x18);
    g2_0286(0x1710);
    g2_37b6("           KEYBOARD CONTROLS            ", 0, 0);
    g2_37b6("                                        ", 0, 1);
    g2_37b6(" The following keys control Duke:       ", 0, 2);
    g2_37b6("   LEFT ARROW  - Move Left              ", 0, 3);
    g2_37b6("   RIGHT ARROW - Move Right             ", 0, 4);
    g2_37b6("   CTRL        - Jump Upward            ", 0, 5);
    g2_37b6("   ALT         - Fire Nuclear Pistol    ", 0, 6);
    g2_37b6("                                        ", 0, 7);
    g2_37b6(" The UP ARROW is the ACTION KEY, which  ", 0, 8);
    g2_37b6(" will enable Duke to:                   ", 0, 9);
    g2_37b6("                                        ", 0, 10);
    g2_37b6("   1) Activate elevators, teleporters,  ", 0, 11);
    g2_37b6("      and time machines.                ", 0, 12);
    g2_37b6("   2) Read notes or monitors.           ", 0, 13);
    g2_37b6("   3) Open doors.                       ", 0, 14);
    g2_37b6("   4) Insert access cards, keys, and    ", 0, 15);
    g2_37b6("      other useful objects.             ", 0, 16);
    g2_37b6("                                        ", 0, 17);
    g2_37b6(" Note: When Duke has the grappling      ", 0, 18);
    g2_37b6(" hooks the UP ARROW will swing him      ", 0, 19);
    g2_37b6(" above a ledge if there is room.        ", 0, 20);
    g2_37b6("                                        ", 0, 21);
    g2_37b6(" Keyboard controls can be altered       ", 0, 22);
    g2_37b6(" within the \"Game Setup\" menu option.   ", 0, 23);
    g2_37b6("             Press any key.             ", 0, 24);
    if (d_cc81_ == 0)
        while ((d_a0fa_ & 0x80) == 0)
            ;
    g2_2870(0x27, 0x18);
    g2_0286(0x1710);
    g2_37b6("         IMPORTANT INFORMATION          ", 0, 0);
    g2_37b6("Duke Nukum needs food and soft drinks   ", 0, 2);
    g2_37b6("to keep him healthy!  Grab all the food ", 0, 3);
    g2_37b6("and drinks you can find (sometimes      ", 0, 4);
    g2_37b6("hidden in boxes).                       ", 0, 5);
    g2_37b6("Duke is armed with a CIA prototype      ", 0, 7);
    g2_37b6("Nuclear Pistol, which has proved to be  ", 0, 8);
    g2_37b6("extremely powerful in field tests. Let's", 0, 9);
    g2_37b6("hope it works in an actual mission!     ", 0, 10);
    g2_37b6("Dr. Proton has built several nuclear    ", 0, 12);
    g2_37b6("reactors to provide power for all of    ", 0, 13);
    g2_37b6("his Techbots and traps.  Duke should    ", 0, 14);
    g2_37b6("consider destroying these reactors a    ", 0, 15);
    g2_37b6("high priority.                          ", 0, 16);
    g2_37b6("It's possible that Duke will find many  ", 0, 18);
    g2_37b6("useful objects.  For example, keys can  ", 0, 19);
    g2_37b6("open doors, boots can help Duke jump    ", 0, 20);
    g2_37b6("higher, and extra pistols will increase ", 0, 21);
    g2_37b6("Duke's firepower. ", 0, 22);
    g2_37b6("             Press any key.             ", 0, 24);
    if (d_cc81_ == 0)
        while ((d_a0fa_ & 0x80) == 0)
            ;
    g2_2870(0x27, 0x18);
    g2_0286(0x1710);
    g2_37b6("         IMPORTANT INFORMATION          ", 0, 0);
    g2_37b6("Duke has unlimited chances (lives) to   ", 0, 2);
    g2_37b6("complete his mission, but every time    ", 0, 3);
    g2_37b6("Duke dies he will have to restart the   ", 0, 4);
    g2_37b6("current level from the beginning.  Duke ", 0, 5);
    g2_37b6("should consume drinks and food to keep  ", 0, 6);
    g2_37b6("his health high.                        ", 0, 7);
    g2_37b6("Each level Duke completes will bring    ", 0, 9);
    g2_37b6("him closer to finding Dr. Proton.  But  ", 0, 10);
    g2_37b6("Dr. Proton will watch Duke's every move ", 0, 11);
    g2_37b6("with an advanced security system (notice", 0, 12);
    g2_37b6("the video cameras that follow your every", 0, 13);
    g2_37b6("move!).  Destroying every camera on a   ", 0, 14);
    g2_37b6("level will earn you a secret bonus.     ", 0, 15);
    g2_37b6("There are several other secret bonuses  ", 0, 16);
    g2_37b6("you might discover.                     ", 0, 17);
    g2_37b6("You can only save and restore Duke's    ", 0, 19);
    g2_37b6("progress in the small hallways between  ", 0, 20);
    g2_37b6("levels.  Hint:  You should save after   ", 0, 21);
    g2_37b6("each level you complete.                ", 0, 22);
    g2_37b6("             Press any key.             ", 0, 24);
    if (d_cc81_ == 0)
        while ((d_a0fa_ & 0x80) == 0)
            ;
    g2_2870(0x27, 0x18);
    g2_01a9(10);
}

void g2_0d39(void)
{
    g2_3d8c(2, 3, 1);
    g2_37b6("   Your game is SAVED.  ", 3, 7);
    g2_37b6("      Press ENTER:      ", 3, 8);
    do {
        g2_2870(0x1a, 8);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_02fb = 0;
    g2_01d5();
}

void g2_0d97(void)
{
    g2_3d8c(2, 3, 2);
    g2_37b6("   Incorrect number.    ", 3, 7);
    g2_37b6("Your game was NOT saved.", 3, 8);
    g2_37b6("                        ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_02fb = 0;
    g2_01d5();
}

void g2_0e19(void)
{
    g2_3d8c(7, 3, 2);
    g2_37b6("This option will be     ", 8, 7);
    g2_37b6("available after you play", 8, 8);
    g2_37b6("the first level.        ", 8, 9);
    g2_37b6("      Press ENTER:      ", 8, 10);
    do {
        g2_2870(0x1f, 0x0a);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_02fb = 0;
    g2_01d5();
}

void g2_0e98(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Find the key", 3, 7);
    g2_37b6("that goes here and press", 3, 8);
    g2_37b6("the UP ARROW.           ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_02fb = 0;
    g2_01d5();
}

void g2_0f2a(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Press the UP", 3, 7);
    g2_37b6("ARROW to read the notes.", 3, 8);
    g2_37b6("                        ", 3, 8);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 0x0a);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_0fc1(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Press the UP", 3, 7);
    g2_37b6("ARROW to activate the   ", 3, 8);
    g2_37b6("ELEVATORS.              ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void pascal g2_1058(register int a0)
{
    g2_3d8c(a0, 3, 2);
    outport(0x3ce, 5);
    while (d_a0fa_ == 0x1f)
        ;
    g2_37b6("       Sound toggle", a0, 7);
    if (d_0097 = !d_0097) {
        g2_37b6("     The sound is ON", a0, 9);
    } else {
        g2_37b6("     The sound is OFF", a0, 9);
        outportb(0x61, inportb(0x61) & 0xfd);
    }
    delay(300);
    g2_2870(a0 + 0x18, 0x0a);
    while (d_a0fa_ == 0x1f)
        ;
}

void pascal g2_10f0(register int a0)
{
    g2_3d8c(a0, 3, 2);
    outport(0x3ce, 5);
    while (d_a0fa_ == 0x23)
        ;
    g2_37b6("       Hint toggle ", a0, 7);
    d_0b46 = !d_0b46;
    if (d_0b46) {
        g2_37b6("     Hint mode is ON", a0, 9);
        d_5a11_ = 1;
        d_5c6b_ = 1;
        d_5554_ = 1;
        d_637e_ = 1;
        d_5ec8_ = 1;
        d_555a_ = 1;
        d_555c_ = 1;
        d_5553_ = 1;
        d_555b_ = 1;
        d_68f7_ = 1;
        d_5555_ = 1;
        d_5c6a_ = 1;
    } else {
        g2_37b6("     Hint mode is OFF", a0, 9);
        d_5a11_ = 0;
        d_5c6b_ = 0;
        d_5554_ = 0;
        d_637e_ = 0;
        d_5ec8_ = 0;
        d_555a_ = 0;
        d_555c_ = 0;
        d_5553_ = 0;
        d_555b_ = 0;
        d_68f7_ = 0;
        d_5555_ = 0;
        d_5c6a_ = 0;
    }
    g2_2870(a0 + 0x18, 0x0a);
    while (d_a0fa_ == 0x23)
        ;
}

void pascal g2_11f2(register int a0)
{
    g2_3d8c(a0, 3, 1);
    outport(0x3ce, 5);
    g2_37b6("       Game PAUSED. ", a0, 7);
    while (d_a0fa_ == 0x19) {
    }
    g2_2870(a0 + 0x18, 8);
}

void pascal g2_1241(register int a0)
{
    g2_3d8c(a0, 3, 2);
    g2_37b6("      Save a game.      ", a0, 7);
    g2_37b6("    Which game number   ", a0, 8);
    g2_37b6("  do you want to save?  ", a0, 9);
    g2_37b6("      Choose (1-9):     ", a0, 10);
    while (d_a0fa_ == 0x1f)
        ;
    g2_2870(a0 + 0x14, 0x0a);
}

void pascal g2_12ad(register int a0)
{
    g2_3d8c(a0, 3, 2);
    g2_37b6("      Restore a game.   ", a0, 7);
    g2_37b6("    Which game number   ", a0, 8);
    g2_37b6("  do you want to load?  ", a0, 9);
    g2_37b6("      Choose (1-9):     ", a0, 10);
    while (d_a0fa_ == 0x13) {
    }
    g2_2870(a0 + 0x14, 10);
}

void g2_1319(void)
{
    outportb(0x43, 0x36);
    outportb(0x40, 0);
    outportb(0x40, 0);
    setvect(8, d_a0f4_);
    outportb(0x61, inportb(0x61) & 0xfd);
}

void pascal g2_1340(register int a0, register int a1)
{
    char x;
    char y;

    d_a0fa_ = 0;
    x = inportb(0x201) & 0x10;
    y = inportb(0x201) & 0x20;
    while (d_a0fa_ == 0 && x != 0 && y != 0) {
        x = inportb(0x201) & 0x10;
        y = inportb(0x201) & 0x20;
        asm_0424(d_a0fb_ + 0x3520, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb_ + 0x35c0, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb_ + 0x3660, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb_ + 0x3700, a0, a1 * 8);
        delay(5);
    }
    asm_0424(d_a0fb_ + 0x37a0, a0, a1 * 8);
}

void g2_1454(void)
{
    d_6e0a_ = 0;
    g2_3d8c(2, 5, 1);
    g2_37b6("     Get ready Duke,    ", 3, 11);
    g2_37b6("    you're going in!!   ", 3, 12);
}

void pascal g2_148f(register int a0)
{
    g2_37b6("        GAME SETUP", a0, 6);
    g2_37b6("      J)oystick mode", a0, 8);
    g2_37b6("      K)eyboard mode", a0, 9);
    g2_37b6("      S)ound toggle", a0, 10);
    g2_37b6("      H)int toggle", a0, 11);
}

void g2_14e6(void)
{
    do {
    } while (d_a0fa_ == 0x44);
    g2_3d8c(2, 1, 1);
    g2_37b6("Are you sure you want to", 3, 3);
    g2_37b6("RESTART the level(Y/N)? ", 3, 4);
    g2_2870(0x1a, 4);
    d_d4c0_ = 0;
    d_d134_ = 0;
}

void g2_1534(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Drink soda  ", 3, 7);
    g2_37b6("to increase your health!", 3, 8);
    g2_37b6("                        ", 3, 8);
    g2_37b6("      Press ENTER:      ", 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_15c9(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Eat turkey  ", 3, 7);
    g2_37b6("to increase your health!", 3, 8);
    g2_37b6("                        ", 3, 8);
    g2_37b6("      Press ENTER:      ", 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_165e(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: The nuclear ", 3, 7);
    g2_37b6("molecule increases your ", 3, 8);
    g2_37b6("health to maximum!      ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_16f3(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Press the UP", 3, 7);
    g2_37b6("ARROW to open the DOOR.", 3, 8);
    g2_37b6("                        ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_178a(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Press the UP", 3, 7);
    g2_37b6("ARROW here after you   ", 3, 8);
    g2_37b6("have found the ROBOHAND.", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_1821(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Find the    ", 3, 7);
    g2_37b6("ACCESS CARD and press   ", 3, 8);
    g2_37b6("the UP ARROW here.      ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_18b8(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Press the UP", 3, 7);
    g2_37b6("ARROW to activate the   ", 3, 8);
    g2_37b6("TRANSPORTER.            ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void pascal g2_194d(register int a0)
{
    g2_37b6(d_00a1[(unsigned char)d_02f4].field, a0 + 0x11, 9);
    g2_37b6(d_00a1[(unsigned char)d_02f5].field, a0 + 0x11, 10);
    g2_37b6(d_00a1[(unsigned char)d_02f6].field, a0 + 0x11, 11);
    g2_37b6(d_00a1[(unsigned char)d_02f7].field, a0 + 0x11, 12);
    g2_37b6(d_00a1[(unsigned char)d_02f8].field, a0 + 0x11, 13);
    g2_37b6(d_00a1[(unsigned char)d_02f9].field, a0 + 0x11, 14);
}

void pascal g2_1a0d(register int a0)
{
    g2_37b6("      DUKE HELP MENU", a0, 4);
    g2_37b6("      --------------", a0, 5);
    g2_37b6("      S)ave a game", a0, 7);
    g2_37b6("      I)nstructions", a0, 8);
    g2_37b6("      G)ame Setup", a0, 9);
    g2_37b6("      H)igh scores", a0, 10);
    g2_37b6("    F10) Restart Level", a0, 11);
}

void g2_1a82(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: Find the    ", 3, 7);
    g2_37b6("ACCESS CARD first and   ", 3, 8);
    g2_37b6("then insert it in here. ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void g2_1b19(void)
{
    d_a0fa_ = 0;
    g1_0042(0x19);
    g2_3d8c(2, 3, 2);
    g2_37b6("Secret Tip: You need the", 3, 7);
    g2_37b6("correct key before      ", 3, 8);
    g2_37b6("you can use this lock.  ", 3, 9);
    g2_37b6("      Press ENTER:      ", 3, 10);
    enable();
    do {
        g2_2870(0x1a, 10);
        d_d4c0_ = 0;
        d_d134_ = 0;
    } while (d_a0fa_ != 0x1c);
    disable();
    d_a0fa_ = 0;
    d_02fb = 0;
    g2_01d5();
}

void pascal g2_1bb0(register int a0)
{
    g2_3d8c(a0, 2, 2);
    g2_37b6(" You can only save a game", a0, 6);
    g2_37b6("  in the main hallways.", a0, 7);
    do {
    } while (d_a0fa_ == 0x1f);
    g2_2870(a0 + 0x18, 7);
}

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

void pascal g2_1d40(int a0)
{
    char buffer[20];
    register int i;

    g2_2d58(a0);
    g2_37b6(" --- HIGH  SCORES ---", a0 + 2, 3);
    for (i = 0; i < 8; ++i) {
        ltoa((long)i + 1L, buffer, 10);
        g2_37b6(buffer, a0 + 2, i * 2 + 5);
        g2_37b6(".", a0 + 3, i * 2 + 5);
        ltoa(d_4fa2_[i], buffer, 10);
        g2_37b6(buffer, a0 + 6, i * 2 + 5);
        g2_37b6(d_5008_[i], a0 + 14, i * 2 + 5);
    }
}

void g2_1e1b(void)
{
    FILE *stream;
    register int i;
#if EPISODE == 1
    stream = fopen("HIGHS.DN1", "w+");
#elif EPISODE == 2
    stream = fopen("HIGHS.dn2", "w+");
#else
    stream = fopen("HIGHS.dn3", "w+");
#endif
    for (i = 0; i < 10; i++) {
        fprintf(stream, "%lu", d_4fa2_[i]);
        fprintf(stream, "%s\n", d_5008_[i]);
    }
    fclose(stream);
}

void g2_1e97(void)
{
    outportb(0x43, 0x36);
    outportb(0x40, 0x51);
    outportb(0x40, 0x20);
    disable();
    d_a8d8_ = 0;
    d_d579_ = 0;
    d_02fb = 0;
    d_0097 = 1;
    d_a0f4_ = getvect(8);
    setvect(8, g2_25fc);
    enable();
}

void pascal g2_1ee1(int a0)
{
    g2_2d58(a0);
    outport(0x3ce, 5);
    g2_37b6("       Instructions ", a0, 3);
    g2_1bfb(a0);
    g2_2870(0x1a, 0x14);
}

void g2_1f24(void)
{
    g2_3d8c(7, 5, 1);
    g2_37b6("   Loading Duke Nukum,", 8, 11);
    g2_37b6("      please wait...  ", 8, 12);
}

void pascal g2_1f5a(int a0)
{
    g2_3d8c(a0, 3, 7);
    outport(0x3ce, 5);
    g2_37b6("      Joystick mode", a0, 7);
    delay(100);
}

void g2_1f9c(void)
{
    asm_05eb(d_6e0a_);
    asm_0424(d_a0fb_ + 0x2800, 0x24, d_9b38_ + 0xa0);
    asm_05eb(!d_6e0a_);
    asm_0424(d_a0fb_ + 0x2800, 0x24, d_9b38_ + 0xa0);
}

void pascal g2_1ffa(char far* bitmap)
{
    asm_05eb(d_6e0a_);
    asm_0424(bitmap, d_9682_ + 0x1e, d_9b38_ + 0xa0);
    asm_05eb(!d_6e0a_);
    asm_0424(bitmap, d_9682_ + 0x1e, d_9b38_ + 0xa0);
    d_9682_ += 2;
}

void g2_205f(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    fputc(d_02f4, stream);
    fputc(d_02f5, stream);
    fputc(d_02f6, stream);
    fputc(d_02f7, stream);
    fputc(d_02f8, stream);
    fputc(d_02f9, stream);
    fclose(stream);
}

void g2_2104(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    if (stream) {
        d_02f4 = fgetc(stream);
        d_02f5 = fgetc(stream);
        d_02f6 = fgetc(stream);
        d_02f7 = fgetc(stream);
        d_02f8 = fgetc(stream);
        d_02f9 = fgetc(stream);
    }
    fclose(stream);
}

void pascal g2_219d(char a0)
{
    char previous;
    FILE *stream;
    char far *filename;

    previous = d_a0fa_;
#if EPISODE == 1
    filename = "saved .dn1";
#elif EPISODE == 2
    filename = "saved .dn2";
#else
    filename = "saved .dn3";
#endif
    filename[5] = a0;
    stream = fopen(filename, "rb");
    if (stream == 0) {
        g2_3d8c(7, 2, 1);
        g2_37b6("     Game not found!!", 7, 5);
        fclose(stream);
        while (d_a0fa_ == previous) {
        }
        d_a0fa_ = 0;
        while (d_a0fa_ == 0) {
        }
        d_5318_ = 1;
        return;
    }
    d_5318_ = 0;
    d_009d = getw(stream);
    d_009f = getw(stream);
    d_0099 = getw(stream);
    d_009b = getw(stream);
    d_02fa = getw(stream);
    d_c295_ = getw(stream);
    d_798a_ = getw(stream);
    d_a0f8_ = getw(stream);
    d_4ed4_ = getw(stream);
    d_cc82_ = getw(stream);
    d_5a11_ = getw(stream);
    d_5c6b_ = getw(stream);
    d_5554_ = getw(stream);
    d_637e_ = getw(stream);
    d_5ec8_ = getw(stream);
    d_555a_ = getw(stream);
    d_555b_ = getw(stream);
    d_68f7_ = getw(stream);
    d_555c_ = getw(stream);
    d_5553_ = getw(stream);
    d_5555_ = getw(stream);
    d_5c6a_ = getw(stream);
    if (d_0b46 == 0) {
        d_5a11_ = d_5c6b_ = d_5554_ = d_637e_ = d_5ec8_ = d_555a_ = d_555b_ = d_68f7_ = d_555c_ = d_5553_ = d_5555_ = d_5c6a_ = 0;
    }
    fscanf(stream, "%ld", &d_68f8_);
    fclose(stream);
}

void g2_23f7(void)
{
    g2_37b6("       High Score       ", 8, 5);
    g2_37b6("------------------------", 8, 6);
    g2_37b6("                        ", 8, 7);
    g2_37b6("Enter your name into the", 8, 8);
    g2_37b6("Duke Nukum Hame of FAME.", 8, 9);
    g2_37b6("       ----------       ", 8, 11);
    g2_37b6(" Press ENTER when done. ", 8, 13);
}

void g2_2473(void)
{
    g2_3d8c(7, 0, 1);
    if (d_cc81_ != 0) {
        g2_37b6("\040\040\040\040\040Press a button..\040\040\040", 7, 1);
    } else {
        g2_37b6("\040\040\040\040\040\040Press any key.\040\040\040\040", 7, 1);
    }
}

void g2_24b1(void)
{
    FILE *stream;
    register int i;

#if EPISODE == 1
    stream = fopen("HIGHS.DN1", "r");
#elif EPISODE == 2
    stream = fopen("HIGHS.dn2", "r");
#else
    stream = fopen("HIGHS.dn3", "r");
#endif
    if (stream == 0) {
        d_4fa2_[0] = 40000L;
        strcpy(d_5008_[0], "TODD");
        d_4fa6_[0] = 30000L;
        strcpy(d_5008_[1], "SCOTT");
        d_4faa_[0] = 20000L;
        strcpy(d_5008_[2], "GEORGE");
        d_4fae_[0] = 10000L;
        strcpy(d_5008_[3], "AL");
        d_4fb2_[0] = 500L;
        strcpy(d_5008_[4], "JOHN");
    } else {
        for (i = 0; i < 10; i++) {
            fscanf(stream, "%lu", &d_4fa2_[i]);
            fscanf(stream, "%[^\n]s", d_5008_[i]);
        }
    }
    fclose(stream);
}

void g2_25cd(void)
{
    char first;
    char second;

    d_d56b_ = 1;
    first = inportb(0x201) & 0x10;
    second = inportb(0x201) & 0x20;
    if (first == 0) {
        d_d56b_ = 0;
    } else if (second == 0) {
        d_d56b_ = 0;
    }
}

void interrupt g2_25fc(void)
{
    register unsigned int period;

    if (d_530b_ != 0) {
        d_530b_ = 0;
        d_0f2a = 0;
        d_a8d8_ = 1;
    }

    if (((int far *)d_cbb5_[(unsigned char)d_531b_])[d_0f2a] == -1) {
        d_a8d8_ = 0;
        d_d579_ = 0;
        outportb(0x61, inportb(0x61) & 0xfd);
    }

    if (d_a8d8_ != 0) {
        period = ((int far *)d_cbb5_[(unsigned char)d_531b_])[d_0f2a];
        if (period == 0 && d_0097 != 0) {
            outportb(0x61, inportb(0x61) & 0xfc);
        } else if (d_0097 != 0) {
            outportb(0x43, 0xb6);
            outportb(0x42, period & 0x100);
            outportb(0x42, period >> 8);
            outportb(0x61, inportb(0x61) | 3);
        }
        ++d_0f2a;
    } else {
        outportb(0x61, inportb(0x61) & 0xfd);
    }

    ++d_02fb;
    ++d_d718_;
    if (d_d718_ == 8) {
        d_d718_ = 0;
        d_a0f4_();
    } else {
        outportb(0x20, 0x20);
    }
}

void g2_26d5(void)
{
#if EPISODE == 1
    g2_37b6("      EPISODE ONE:  SHRAPNEL CITY       ", 0, 12);
    g2_37b6("  Your mission as Duke Nukum:  A plane  ", 0, 14);
    g2_37b6(" will fly over Dr. Proton's sieged city ", 0, 15);
    g2_37b6("   and drop Duke on a huge skyscraper.  ", 0, 16);
    g2_37b6(" Duke must proceed to Dr. Proton's well ", 0, 17);
    g2_37b6(" guarded hideout believed to be hidden  ", 0, 18);
    g2_37b6("  deep underground. Dr. Proton must be  ", 0, 19);
    g2_37b6("    stopped or the world is doomed!     ", 0, 20);
    g2_37b6("             Press any key.             ", 0, 24);
#elif EPISODE == 2
    g2_37b6("    EPISODE TWO - MISSION: MOONBASE     ", 0, 11);
    g2_37b6("   When we last saw Duke he had just    ", 0, 13);
    g2_37b6("   barely survived an encounter with    ", 0, 14);
    g2_37b6("  Dr. Proton. Somehow, Duke managed to  ", 0, 15);
    g2_37b6(" penetrate Proton's captured city, beat ", 0, 16);
    g2_37b6(" his Techbot guards,  and forced Proton ", 0, 17);
    g2_37b6("     to flee to his moonbase. Using    ", 0, 18);
    g2_37b6("  Dr. Proton's time transport machine,  ", 0, 19);
    g2_37b6("  Duke has decided to chase him to the  ", 0, 20);
    g2_37b6("   Moon, and stop him cold...  (well,   ", 0, 21);
    g2_37b6("      at least that's the plan!)        ", 0, 22);
    g2_37b6("             Press any key.             ", 0, 24);
#else
    g2_37b6(" EPISODE THREE:  TRAPPED IN THE FUTURE! ", 0, 11);
    g2_37b6("    Again, Duke foiled the mad plans    ", 0, 12);
    g2_37b6("    of Dr. Proton.  His secret lunar    ", 0, 13);
    g2_37b6("  fortress now wrecked, Dr. Proton has  ", 0, 14);
    g2_37b6(" transported himself back to Earth, and ", 0, 15);
    g2_37b6("  used his time machine to hide in the  ", 0, 16);
    g2_37b6("   Earth's future. There he will once   ", 0, 17);
    g2_37b6("  again create a huge army of Techbots  ", 0, 18);
    g2_37b6("   that will allow him to control the   ", 0, 19);
    g2_37b6(" world.  Of course, Duke will not stand ", 0, 20);
    g2_37b6("   for this, and although he'd rather   ", 0, 21);
    g2_37b6("   watch Oprah,  he heads off to stop   ", 0, 22);
    g2_37b6("       Dr. Proton one more time...      ", 0, 23);
    g2_37b6("             Press any key.             ", 0, 24);
#endif
}

/* Wait out an 0xE0 extended-key prefix in the keyboard byte, then return it
   with the release bit cleared (interrupts left disabled). */
char g2_276f(void)
{
    if (d_a0fa_ == 0xe0) {
        while (d_a0fa_ == 0xe0)
            ;
        disable();
        return d_a0fa_ & 0x7f;
    }
    return d_a0fa_;
}

void pascal g2_2789(long value, int x, int page)
{
    char text[16];
    register int si;
    register int di;

    ultoa(value, text, 10);
    di = strlen(text);
    si = di - 1;
    for (; si >= 0; --si) {
        asm_05eb(1);
        asm_053c(d_6b54_ + (text[di - si - 1] - '0') * 40 + 0x410,
                 x - si, page * 8);
        asm_05eb(0);
        asm_053c(d_6b54_ + (text[di - si - 1] - '0') * 40 + 0x410,
                 x - si, page * 8);
    }
    asm_05eb(!d_6e0a_);
}

/* Wait for a key or joystick button, cycling a 4-frame animation at (x, y). */
void pascal g2_2870(register int a0, register int a1)
{
    char x = 1;
    char y = 1;

    d_a0fa_ = 0;
    if (d_d56b_ != 0) {
        g1_1076();
        x = inportb(0x201) & 0x10;
        y = inportb(0x201) & 0x20;
    }
    while (d_a0fa_ == 0 && x != 0 && y != 0) {
        if (d_d56b_ != 0) {
            x = inportb(0x201) & 0x10;
            y = inportb(0x201) & 0x20;
        }
        asm_0424(d_a0fb_ + 0x3520, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb_ + 0x35c0, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb_ + 0x3660, a0, a1 * 8);
        delay(5);
        asm_0424(d_a0fb_ + 0x3700, a0, a1 * 8);
        delay(5);
    }
    asm_0424(d_a0fb_ + 0x37a0, a0, a1 * 8);
}

void g2_29a2(void)
{
    register int si;

    si = 0x280;
    outport(0x3ce, 0x105);
    do {
        asm_02ad(0x3000, si);
        asm_02ad(0x3020, si + 0x1c);
        si += 0x280;
    } while (si < 0x1b80);
    si = 2;
    do {
        asm_02ad(0x3040, si);
        asm_02ad(0x3060, si + 0x1b80);
        si += 2;
    } while (si < 0x1c);
    asm_02ad(0x31c0, 0x141c);
    asm_02ad(0x31c0, 0x065c);
    asm_02ad(0x31c0, 0x0c9c);
    asm_02ad(0x3080, 0);
    asm_02ad(0x30a0, 0x001c);
    asm_02ad(0x30c0, 0x1b9c);
    asm_02ad(0x30e0, 0x1b80);
    asm_02ad(0x3340, 0x1b8b);
    asm_02ad(0x3360, 0x1b8d);
    asm_02ad(0x3380, 0x1b8f);
    asm_02ad(0x33a0, 0x1b91);
}

void g2_2ab9(void)
{
    register int si;
    register int di;

    di = 0;
    outport(0x3ce, 0x0105);
    g2_29a2();
    do {
        ++di;
        asm_05eb(di - 1);
        asm_02ad(0x3080, 0);
        asm_02ad(0x30a0, 0x001c);
        asm_02ad(0x30c0, 0x1b9c);
        asm_02ad(0x30e0, 0x1b80);
        asm_02ad(0x3100, 0x001e);
        asm_02ad(0x3100, 0x0020);
        asm_02ad(0x3100, 0x0022);
        asm_02ad(0x3100, 0x0024);
        asm_02ad(0x3120, 0x0026);
        asm_02ad(0x3160, 0x1ba6);
        for (si = 0x0280; si < 0x1b80; si += 0x0280)
            asm_02ad(0x3140, si + 0x0026);
        asm_02ad(0x3100, 0x141e);
        asm_02ad(0x3100, 0x0c9e);
        asm_02ad(0x3100, 0x1420);
        asm_02ad(0x3100, 0x0ca0);
        asm_02ad(0x3100, 0x1422);
        asm_02ad(0x3100, 0x0ca2);
        asm_02ad(0x3100, 0x1424);
        asm_02ad(0x3100, 0x0ca4);
        asm_02ad(0x31e0, 0x1426);
        asm_02ad(0x31e0, 0x0ca6);
        asm_02ad(0x3100, 0x1b9e);
        asm_02ad(0x3100, 0x1ba0);
        asm_02ad(0x3100, 0x1ba2);
        asm_02ad(0x3100, 0x1ba4);
        asm_02ad(0x3100, 0x065e);
        asm_02ad(0x3480, 0x0660);
        asm_02ad(0x34a0, 0x0662);
        asm_02ad(0x3100, 0x0664);
        asm_02ad(0x34c0, 0x0020);
        asm_02ad(0x34e0, 0x0022);
        asm_02ad(0x33c0, 0x141f);
        asm_02ad(0x33e0, 0x1421);
        asm_02ad(0x3400, 0x1423);
        asm_02ad(0x3420, 0x0c9f);
        asm_02ad(0x3440, 0x0ca1);
        asm_02ad(0x3460, 0x0ca3);
        asm_02ad(0x31e0, 0x0666);
    } while (di == 1);
}

void pascal g2_2d58(int a0)
{
    register int si;
    register int di;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    if (a0 == 2)
        asm_05eb(d_6e0a_);
    else
        asm_05eb(0);

    for (si = 0; si < 10; si++) {
        for (di = a0; di < a0 + 26; di += 2)
            asm_02ad(0x3220, si * 640 + di + 640);
    }

    asm_02ad(0x3240, a0 + 640);
    asm_02ad(0x3260, a0 + 664);
    asm_02ad(0x3280, a0 + 0x1900);
    asm_02ad(0x32a0, a0 + 0x1918);

    for (si = 0x500; si < 0x16a8; si += 640) {
        asm_02ad(0x32c0, si + a0);
        asm_02ad(0x32e0, si + a0 + 24);
    }

    for (si = 0x282; si < 0x298; si += 2) {
        asm_02ad(0x3300, si + a0);
        asm_02ad(0x3320, si + a0 + 0x1680);
    }
}

void pascal g2_2e8c(char x, char y, char far *text, char attribute)
{
    register int i = 0;
    char far *screen = (char far *)MK_FP(0xB800, 0);

    while (text[i] != 0) {
        *(screen + i * 2 + x * 2 + y * 160) = text[i];
        *(screen + i * 2 + x * 2 + y * 160 + 1) = attribute;
        ++i;
    }
}

/* g2_2f04 reconstructed candidate */
void g2_2f04(void)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#if EPISODE == 1
    g2_2e8c(0, 0, "\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", 31);
    g2_2e8c(0, 1, "\xB0\xB0\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF", 31);
    g2_2e8c(0, 2, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(9, 2, "\x48\x4F\x57\x20\x54\x4F\x20\x4F\x52\x44\x45\x52\x20\x54\x48\x45\x20\x52\x45\x4D\x41\x49\x4E\x49\x4E\x47\x20\x54\x57\x4F\x20\x49\x4E\x43\x52\x45\x44\x49\x42\x4C\x45\x20\x45\x50\x49\x53\x4F\x44\x45\x53\x20\x4F\x46\x20\x44\x55\x4B\x45\x20\x4E\x55\x4B\x55\x4D", 30);
    g2_2e8c(0, 3, "\xB0\xB0\xC6\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB5", 31);
    g2_2e8c(0, 4, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 5, "\xB0\xB0\xB3\x20\x54\x68\x65\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x76\x6F\x6C\x75\x6D\x65\x73\x20\x6F\x66\x20\x44\x55\x4B\x45\x20\x4E\x55\x4B\x55\x4D\x20\x68\x61\x76\x65\x20\x6D\x6F\x72\x65\x20\x6E\x65\x77\x20\x67\x72\x61\x70\x68\x69\x63\x73\x20\x74\x68\x61\x6E\x20\x61\x6C\x6C\x20\x62\x75\x74\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 6, "\xB0\xB0\xB3\x20\x74\x68\x65\x20\x6C\x61\x72\x67\x65\x73\x74\x20\x63\x6F\x6D\x6D\x65\x72\x63\x69\x61\x6C\x20\x67\x61\x6D\x65\x73\x21\x20\x20\x49\x6E\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x74\x77\x6F\x20\x79\x6F\x75\x27\x6C\x6C\x20\x74\x72\x61\x76\x65\x6C\x20\x74\x6F\x20\x74\x68\x65\x20\x6D\x6F\x6F\x6E\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 7, "\xB0\xB0\xB3\x20\x61\x6E\x64\x20\x62\x61\x74\x74\x6C\x65\x20\x44\x72\x2E\x20\x50\x72\x6F\x74\x6F\x6E\x20\x61\x73\x20\x68\x65\x20\x70\x6C\x61\x6E\x73\x20\x68\x69\x73\x20\x73\x65\x63\x6F\x6E\x64\x20\x61\x73\x73\x61\x75\x6C\x74\x20\x6F\x6E\x20\x45\x61\x72\x74\x68\x2E\x20\x20\x41\x6E\x64\x20\x69\x6E\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 8, "\xB0\xB0\xB3\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x74\x68\x72\x65\x65\x20\x79\x6F\x75\x27\x6C\x6C\x20\x77\x61\x72\x70\x20\x74\x6F\x20\x74\x68\x65\x20\x45\x61\x72\x74\x68\x27\x73\x20\x66\x75\x74\x75\x72\x65\x20\x74\x6F\x20\x73\x74\x6F\x70\x20\x44\x72\x2E\x20\x50\x72\x6F\x74\x6F\x6E\x20\x66\x72\x6F\x6D\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 9, "\xB0\xB0\xB3\x20\x63\x6F\x6D\x70\x6C\x65\x74\x69\x6E\x67\x20\x68\x69\x73\x20\x6D\x61\x6E\x69\x61\x63\x61\x6C\x20\x70\x6C\x61\x6E\x20\x74\x6F\x20\x72\x75\x6C\x65\x20\x74\x68\x65\x20\x77\x6F\x72\x6C\x64\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 10, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 11, "\xB0\xB0\xB3\x20\x59\x6F\x75\x20\x6D\x61\x79\x20\x6F\x72\x64\x65\x72\x20\x74\x68\x65\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x76\x6F\x6C\x75\x6D\x65\x73\x20\x6F\x66\x20\x44\x55\x4B\x45\x20\x4E\x55\x4B\x55\x4D\x20\x66\x6F\x72\x20\x6F\x6E\x6C\x79\x20\x24\x33\x30\x20\x28\x70\x6C\x75\x73\x20\x24\x33\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 12, "\xB0\xB0\xB3\x20\x73\x68\x69\x70\x70\x69\x6E\x67\x20\x70\x6C\x65\x61\x73\x65\x29\x2E\x20\x20\x59\x6F\x75\x27\x6C\x6C\x20\x61\x6C\x73\x6F\x20\x67\x65\x74\x20\x74\x68\x65\x20\x63\x75\x72\x72\x65\x6E\x74\x20\x76\x65\x72\x73\x69\x6F\x6E\x20\x6F\x66\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x6E\x65\x2C\x20\x74\x68\x65\x20\xB3", 31);
    g2_2e8c(0, 13, "\xB0\xB0\xB3\x20\x73\x65\x63\x72\x65\x74\x20\x63\x68\x65\x61\x74\x20\x63\x6F\x64\x65\x2C\x20\x74\x68\x65\x20\x68\x69\x6E\x74\x73\x20\x61\x6E\x64\x20\x74\x72\x69\x63\x6B\x73\x20\x73\x68\x65\x65\x74\x2C\x20\x70\x6C\x75\x73\x20\x61\x63\x63\x65\x73\x73\x20\x74\x6F\x20\x74\x68\x65\x20\x41\x70\x6F\x67\x65\x65\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 14, "\xB0\xB0\xB3\x20\x68\x69\x6E\x74\x73\x20\x6C\x69\x6E\x65\x21\x20\x20\x50\x4C\x55\x53\x2C\x20\x79\x6F\x75\x27\x6C\x6C\x20\x67\x65\x74\x20\x73\x65\x76\x65\x72\x61\x6C\x20\x6F\x66\x20\x41\x70\x6F\x67\x65\x65\x27\x73\x20\x61\x6D\x61\x7A\x69\x6E\x67\x20\x6E\x65\x77\x20\x67\x61\x6D\x65\x73\x21\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 15, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 16, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(4, 16, "\x4F\x72\x64\x65\x72\x20\x4E\x4F\x57\x20\x62\x79\x20\x63\x61\x6C\x6C\x69\x6E\x67\x20\x54\x4F\x4C\x4C\x20\x46\x52\x45\x45\x3A\x20\x20\x31\x2D\x38\x30\x30\x2D\x38\x35\x32\x2D\x35\x36\x35\x39\x20\x20\x28\x56\x69\x73\x61\x20\x61\x6E\x64\x20\x4D\x61\x73\x74\x65\x72\x43\x61\x72\x64\x29", 30);
    g2_2e8c(0, 17, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 18, "\xB0\xB0\xB3\x20\x4F\x72\x20\x6D\x61\x69\x6C\x20\x6F\x72\x64\x65\x72\x20\x74\x6F\x3A\x20\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x07\x20\x50\x2E\x4F\x2E\x20\x42\x6F\x78\x20\x34\x37\x36\x33\x38\x39\x20\x07\x20\x47\x61\x72\x6C\x61\x6E\x64\x2C\x20\x54\x58\x20\x37\x35\x30\x34\x37\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 19, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(2, 20, "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9", 31);
#elif EPISODE == 2
    g2_2e8c(0, 0, "\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", 31);
    g2_2e8c(0, 1, "\xB0\xB0\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF", 31);
    g2_2e8c(0, 2, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(9, 2, "\x4E\x4F\x54\x49\x43\x45\x3A\x20\x20\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x49\x53\x20\x4E\x4F\x54\x20\x53\x48\x41\x52\x45\x57\x41\x52\x45\x2C\x20\x46\x52\x45\x45\x57\x41\x52\x45\x20\x4F\x52\x20\x50\x55\x42\x4C\x49\x43\x20\x44\x4F\x4D\x41\x49\x4E\x21", 30);
    g2_2e8c(0, 3, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(8, 3, "\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x4D\x41\x59\x20\x4F\x4E\x4C\x59\x20\x42\x45\x20\x44\x49\x53\x54\x52\x49\x42\x55\x54\x45\x44\x20\x42\x59\x20\x41\x50\x4F\x47\x45\x45\x20\x53\x4F\x46\x54\x57\x41\x52\x45\x20\x50\x52\x4F\x44\x55\x43\x54\x49\x4F\x4E\x53\x2E", 30);
    g2_2e8c(0, 4, "\xB0\xB0\xC6\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB5", 31);
    g2_2e8c(0, 5, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 6, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x4F\x6E\x6C\x79\x20\x74\x68\x65\x20\x66\x69\x72\x73\x74\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x69\x73\x20\x61\x76\x61\x69\x6C\x61\x62\x6C\x65\x20\x61\x73\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x2E\x20\x54\x68\x65\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 7, "\xB0\xB0\xB3\x20\x20\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x28\x69\x6E\x63\x6C\x75\x64\x69\x6E\x67\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x29\x20\x61\x72\x65\x20\x6F\x6E\x6C\x79\x20\x73\x6F\x6C\x64\x20\x20\xB3", 31);
    g2_2e8c(0, 8, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x63\x6F\x6D\x6D\x65\x72\x63\x69\x61\x6C\x6C\x79\x20\x62\x79\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x6F\x72\x20\x61\x6E\x20\x61\x75\x74\x68\x6F\x72\x69\x7A\x65\x64\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x6F\x72\x2E\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 9, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 10, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x42\x75\x6C\x6C\x65\x74\x69\x6E\x20\x62\x6F\x61\x72\x64\x73\x2C\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x20\x76\x65\x6E\x64\x6F\x72\x73\x2C\x20\x75\x73\x65\x72\x73\x20\x67\x72\x6F\x75\x70\x73\x20\x61\x6E\x64\x20\x63\x6C\x75\x62\x73\x20\x6D\x61\x79\x20\x6E\x6F\x74\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 11, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x65\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 12, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 13, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x63\x6F\x6E\x73\x69\x73\x74\x73\x20\x6F\x66\x20\x74\x68\x72\x65\x65\x20\x75\x6E\x69\x71\x75\x65\x20\x61\x6E\x64\x20\x65\x78\x63\x69\x74\x69\x6E\x67\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x3A\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 14, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x53\x68\x72\x61\x70\x6E\x65\x6C\x20\x43\x69\x74\x79\x20\x20\x07\x20\x20\x4D\x69\x73\x73\x69\x6F\x6E\x3A\x20\x4D\x6F\x6F\x6E\x62\x61\x73\x65\x20\x20\x07\x20\x20\x54\x72\x61\x70\x70\x65\x64\x20\x69\x6E\x20\x74\x68\x65\x20\x46\x75\x74\x75\x72\x65\x21\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 15, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 16, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x54\x6F\x20\x6F\x72\x64\x65\x72\x20\x74\x68\x65\x20\x63\x6F\x6D\x70\x6C\x65\x74\x65\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x74\x72\x69\x6C\x6F\x67\x79\x2C\x20\x63\x61\x6C\x6C\x20\x31\x2D\x38\x30\x30\x2D\x38\x35\x32\x2D\x35\x36\x35\x39\x2E\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 17, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 18, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x4F\x72\x20\x77\x72\x69\x74\x65\x3A\x20\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x07\x20\x50\x2E\x4F\x2E\x20\x42\x6F\x78\x20\x34\x37\x36\x33\x38\x39\x20\x07\x20\x47\x61\x72\x6C\x61\x6E\x64\x2C\x20\x54\x58\x20\x37\x35\x30\x34\x37\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 19, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(2, 20, "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9", 31);
#elif EPISODE == 3
    g2_2e8c(0, 0, "\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", 31);
    g2_2e8c(0, 1, "\xB0\xB0\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF", 31);
    g2_2e8c(0, 2, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(9, 2, "\x4E\x4F\x54\x49\x43\x45\x3A\x20\x20\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x49\x53\x20\x4E\x4F\x54\x20\x53\x48\x41\x52\x45\x57\x41\x52\x45\x2C\x20\x46\x52\x45\x45\x57\x41\x52\x45\x20\x4F\x52\x20\x50\x55\x42\x4C\x49\x43\x20\x44\x4F\x4D\x41\x49\x4E\x21", 30);
    g2_2e8c(0, 3, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(8, 3, "\x54\x48\x49\x53\x20\x47\x41\x4D\x45\x20\x4D\x41\x59\x20\x4F\x4E\x4C\x59\x20\x42\x45\x20\x44\x49\x53\x54\x52\x49\x42\x55\x54\x45\x44\x20\x42\x59\x20\x41\x50\x4F\x47\x45\x45\x20\x53\x4F\x46\x54\x57\x41\x52\x45\x20\x50\x52\x4F\x44\x55\x43\x54\x49\x4F\x4E\x53\x2E", 30);
    g2_2e8c(0, 4, "\xB0\xB0\xC6\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB5", 31);
    g2_2e8c(0, 5, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 6, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x4F\x6E\x6C\x79\x20\x74\x68\x65\x20\x66\x69\x72\x73\x74\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x69\x73\x20\x61\x76\x61\x69\x6C\x61\x62\x6C\x65\x20\x61\x73\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x2E\x20\x54\x68\x65\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 7, "\xB0\xB0\xB3\x20\x20\x20\x66\x69\x6E\x61\x6C\x20\x74\x77\x6F\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x28\x69\x6E\x63\x6C\x75\x64\x69\x6E\x67\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x29\x20\x61\x72\x65\x20\x6F\x6E\x6C\x79\x20\x73\x6F\x6C\x64\x20\x20\xB3", 31);
    g2_2e8c(0, 8, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x63\x6F\x6D\x6D\x65\x72\x63\x69\x61\x6C\x6C\x79\x20\x62\x79\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x6F\x72\x20\x61\x6E\x20\x61\x75\x74\x68\x6F\x72\x69\x7A\x65\x64\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x6F\x72\x2E\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 9, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 10, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x42\x75\x6C\x6C\x65\x74\x69\x6E\x20\x62\x6F\x61\x72\x64\x73\x2C\x20\x73\x68\x61\x72\x65\x77\x61\x72\x65\x20\x76\x65\x6E\x64\x6F\x72\x73\x2C\x20\x75\x73\x65\x72\x73\x20\x67\x72\x6F\x75\x70\x73\x20\x61\x6E\x64\x20\x63\x6C\x75\x62\x73\x20\x6D\x61\x79\x20\x6E\x6F\x74\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 11, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x69\x73\x74\x72\x69\x62\x75\x74\x65\x20\x74\x68\x69\x73\x20\x65\x70\x69\x73\x6F\x64\x65\x20\x6F\x66\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 12, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 13, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x63\x6F\x6E\x73\x69\x73\x74\x73\x20\x6F\x66\x20\x74\x68\x72\x65\x65\x20\x75\x6E\x69\x71\x75\x65\x20\x61\x6E\x64\x20\x65\x78\x63\x69\x74\x69\x6E\x67\x20\x65\x70\x69\x73\x6F\x64\x65\x73\x3A\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 14, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x53\x68\x72\x61\x70\x6E\x65\x6C\x20\x43\x69\x74\x79\x20\x20\x07\x20\x20\x4D\x69\x73\x73\x69\x6F\x6E\x3A\x20\x4D\x6F\x6F\x6E\x62\x61\x73\x65\x20\x20\x07\x20\x20\x54\x72\x61\x70\x70\x65\x64\x20\x69\x6E\x20\x74\x68\x65\x20\x46\x75\x74\x75\x72\x65\x21\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 15, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 16, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x54\x6F\x20\x6F\x72\x64\x65\x72\x20\x74\x68\x65\x20\x63\x6F\x6D\x70\x6C\x65\x74\x65\x20\x44\x75\x6B\x65\x20\x4E\x75\x6B\x75\x6D\x20\x74\x72\x69\x6C\x6F\x67\x79\x2C\x20\x63\x61\x6C\x6C\x20\x31\x2D\x38\x30\x30\x2D\x38\x35\x32\x2D\x35\x36\x35\x39\x2E\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 17, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 18, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x4F\x72\x20\x77\x72\x69\x74\x65\x3A\x20\x20\x41\x70\x6F\x67\x65\x65\x20\x53\x6F\x66\x74\x77\x61\x72\x65\x20\x07\x20\x50\x2E\x4F\x2E\x20\x42\x6F\x78\x20\x34\x37\x36\x33\x38\x39\x20\x07\x20\x47\x61\x72\x6C\x61\x6E\x64\x2C\x20\x54\x58\x20\x37\x35\x30\x34\x37\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(0, 19, "\xB0\xB0\xB3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB3", 31);
    g2_2e8c(2, 20, "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9", 31);
#endif
}

void pascal g2_30b0(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_c285_ = malloc(0x7d01);
    if (d_c285_)
        fread(d_c285_, 0x7d00, 1, stream);
    fclose(stream);
}

void g2_3114(void)
{
    register int x;
    register int y;

    outport(0x3c4, 0x0f02);
    asm_05eb(0);
    for (y = 0; y < 25; y++) {
        for (x = 0; x < 40; x += 2) {
            asm_02ad(0, y * 640 + x);
        }
    }
}

void g2_315d(void)
{
    char far *video = (char far *)0xa0000000L;
    register int i;

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285_[i];
    outport(0x3c4, 0x0202);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285_[i + 0x1f40];
    outport(0x3c4, 0x0402);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285_[i + 0x3e80];
    outport(0x3c4, 0x0802);
    for (i = 0; i < 0x1f40; ++i)
        video[i] = d_c285_[i + 0x5dc0];
    asm_05f7(0);
}

void pascal g2_3252(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_b638_ = malloc(0x7d01);
    if (d_b638_ != 0) {
        fread(d_b638_, 0x7d00, 1, stream);
    }
    fclose(stream);
}

void g2_32b6(void)
{
    char far *screen = (char far *)MK_FP(0xa000, 0);
    register int si;

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638_[si];
    outport(0x3c4, 0x0202);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638_[si + 0x1f40];
    outport(0x3c4, 0x0402);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638_[si + 0x3e80];
    outport(0x3c4, 0x0802);
    for (si = 0; si < 0x1f40; ++si)
        screen[si] = d_b638_[si + 0x5dc0];
    asm_05f7(0);
}

void pascal g2_33ab(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    d_c27d_ = malloc(0x7d01);
    if (d_c27d_ != 0) {
        fread(d_c27d_, 0x7d00, 1, stream);
    }
    fclose(stream);
}

void g2_340f(void)
{
    register int si;
    char far *video = (char far *)MK_FP(0xA000, 0);

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (si = 0; si < 0x1f40; ++si)
        video[si] = d_c27d_[si];
    outport(0x3c4, 0x0202);
    for (si = 0; si < 0x1f40; ++si)
        video[si] = d_c27d_[si + 0x1f40];
    outport(0x3c4, 0x0402);
    for (si = 0; si < 0x1f40; ++si)
        video[si] = d_c27d_[si + 0x3e80];
    outport(0x3c4, 0x0802);
    for (si = 0; si < 0x1f40; ++si)
        video[si] = d_c27d_[si + 0x5dc0];
    asm_05f7(0);
}

void pascal g2_3504(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    d_a0bb_ = malloc(0x7d01);
    if (d_a0bb_ != 0) {
        fread(d_a0bb_, 0x7d00, 1, stream);
    }
    fclose(stream);
}

void g2_3568(void)
{
    register int i;
    char far *video = (char far *)MK_FP(0xa000, 0);

    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb_[i];
    }
    outport(0x3c4, 0x0202);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb_[i + 8000];
    }
    outport(0x3c4, 0x0402);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb_[i + 16000];
    }
    outport(0x3c4, 0x0802);
    for (i = 0; i < 8000; ++i) {
        video[i] = d_a0bb_[i + 24000];
    }
    asm_05f7(0);
}

void pascal g2_365d(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    d_c28f_ = malloc(0x7d01);
    if (d_c28f_) {
        fread(d_c28f_, 0x7d00, 1, stream);
    }
    fclose(stream);
}

void g2_36c1(void)
{
    char far *vram;
    register int si;

    vram = MK_FP(0xa000, 0);
    g2_3114();
    outport(0x3ce, 5);
    asm_05eb(0);
    asm_05f7(1);
    outport(0x3c4, 0x0102);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f_[si];
    outport(0x3c4, 0x0202);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f_[si + 0x1f40];
    outport(0x3c4, 0x0402);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f_[si + 0x3e80];
    outport(0x3c4, 0x0802);
    for (si = 0; si < 0x1f40; si++)
        vram[si] = d_c28f_[si + 0x5dc0];
    asm_05f7(0);
}

void pascal g2_37b6(char far *text, register int x, int y)
{
    register int i;

    i = 0;
    outport(0x3ce, 5);
    for (; text[i] != 0; ++i) {
        if (text[i] >= 'a') {
            asm_04c5(d_6b54_ + (text[i] - 'a') * 40 + 0xac8,
                     x + i, y * 8);
        } else {
            asm_04c5(d_6b54_ + (text[i] - ' ') * 40 + 0x190,
                     x + i, y * 8);
        }
    }
}

void pascal g2_385b(char a0, int a1, int a2)
{
    if (a0 >= 'a') {
        asm_04c5(d_6b54_ + (a0 - 'a') * 40 + 0xac8, a1, a2);
    } else {
        asm_04c5(d_6b54_ + (a0 - ' ') * 40 + 0x190, a1, a2);
    }
}

#if EPISODE == 1 || EPISODE == 2
/* g2_38be: at this place in the DN1, DN2 source */
void pascal g2_38be(register int a0)
{
    g2_37b6("      DUKE MAIN MENU", a0, 6);
    g2_37b6("      --------------", a0, 7);
    g2_37b6("   S)tart a new game", a0, 9);
    g2_37b6("   R)estore an old game", a0, 0x0a);
    g2_37b6("   I)nstructions", a0, 0x0b);
    g2_37b6("   O)rdering information", a0, 0x0c);
    g2_37b6("   G)ame setup", a0, 0x0d);
    g2_37b6("   H)igh scores", a0, 0x0e);
    g2_37b6("   P)reviews/Main Demo!", a0, 0x0f);
    g2_37b6("   V)iew user demo", a0, 0x10);
    g2_37b6("   T)itle screen", a0, 0x11);
    g2_37b6("   C)redits", a0, 0x12);
    g2_37b6("   Q)uit to DOS", a0, 0x13);
}
#endif

void pascal g2_3980(char far *filename)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    d_d714_ = malloc(0x2454);
    fread(d_d714_, 0x2454, 1, stream);
    fclose(stream);
    for (i = 0; i < 24; ++i) {
        d_cbb5_[i] = d_d714_ + (((struct g2_3980_record far *)(d_d714_ + ((((i << 1) << 1) << 1) << 1)))->f[8] >> 1 << 1);
        d_4fce_[i] = ((struct g2_3980_record far *)(d_d714_ + ((((i << 1) << 1) << 1) << 1)))->f[9];
    }
}

void pascal g2_3a38(char far *filename)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    d_d710_ = malloc(0x2134);
    fread(d_d710_, 0x1f40, 1, stream);
    fclose(stream);
    for (i = 0; i < 0x18; ++i) {
        d_cbb5_[i + 0x18] = d_d710_ + (((*((unsigned int far *)((char far *)d_d710_ + ((((i << 1) << 1) << 1) << 1) + 0x10))) >> 1) << 1);
        d_4fe6_[i] = *((unsigned char far *)((char far *)d_d710_ + ((((i << 1) << 1) << 1) << 1) + 0x10));
    }
}

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

void g2_3b79(void)
{
    asm_05eb(d_6e0a_);
    asm_0424(d_a0fb_ + 0x4c40, 0x24, d_9b38_ + 0xa0);
    asm_05eb(!d_6e0a_);
    asm_0424(d_a0fb_ + 0x4c40, 0x24, d_9b38_ + 0xa0);
}

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

void g2_3c9a(void)
{
    g2_37b6("     You have died.", 3, 3);
    g2_37b6("Bringing you back to the", 3, 4);
    g2_37b6("   last main hallway.", 3, 5);
    g2_37b6("      Press ENTER:", 3, 6);
}

void g2_3cdc(void)
{
    g2_37b6("You are now cheating.", 3, 3);
    g2_37b6("You have full fire power", 3, 4);
    g2_37b6("and all the keys.", 3, 5);
    g2_37b6("Have Fun!", 3, 6);
}

#if EPISODE == 3
/* g2_38be: at this place in the DN3 source */
void pascal g2_38be(register int a0)
{
    g2_37b6("      DUKE MAIN MENU", a0, 6);
    g2_37b6("      --------------", a0, 7);
    g2_37b6("   S)tart a new game", a0, 9);
    g2_37b6("   R)estore an old game", a0, 0x0a);
    g2_37b6("   I)nstructions", a0, 0x0b);
    g2_37b6("   O)rdering information", a0, 0x0c);
    g2_37b6("   G)ame setup", a0, 0x0d);
    g2_37b6("   H)igh scores", a0, 0x0e);
    g2_37b6("   P)reviews/Main Demo!", a0, 0x0f);
    g2_37b6("   V)iew user demo", a0, 0x10);
    g2_37b6("   T)itle screen", a0, 0x11);
    g2_37b6("   C)redits", a0, 0x12);
    g2_37b6("   Q)uit to DOS", a0, 0x13);
}
#endif

void pascal g2_3d1e(register int a0)
{
    g2_3d8c(a0, 5, 1);
    g2_37b6("Are you sure you want to", a0 + 1, 11);
    g2_37b6("         quit?          ", a0 + 1, 12);
    while (d_a0fa_ == 1) {
    }
    g2_2870(a0 + 0x10, 12);
    d_d4c0_ = 0;
    d_d134_ = 0;
    if (d_a0fa_ == 0x15)
        return 1;
    d_a0fa_ = 0;
    return 0;
}

/* Apparently draws a framed box from border tiles (asm_02ad) at column a2, row a1
   (pascal; parameters are listed in declaration order a2, a1, a0). */
void pascal g2_3d8c(int a2, int a1, int a0)
{
    register int si;
    register int di;

    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);
    if (a2 == 2)
        asm_05eb(d_6e0a_);
    else
        asm_05eb(0);

    for (si = 0; a0 * 16 * 40 > si; si += 640) {
        asm_02ad(0x32c0, a1 * 16 * 40 + (si + a2));
        asm_02ad(0x32e0, a1 * 16 * 40 + (si + a2) + 24);
    }
    for (di = 2; di < 23; di += 2)
        for (si = 0; a0 * 16 * 40 > si; si += 640)
            asm_02ad(0x3220, a1 * 16 * 40 + a2 + di + si);

    asm_02ad(0x3240, a1 * 16 * 40 + a2);
    asm_02ad(0x3260, a1 * 16 * 40 + a2 + 24);
    asm_02ad(0x3280, (a1 * 16 * 40 + a2) + a0 * 16 * 40);
    asm_02ad(0x32a0, (a1 * 16 * 40 + a2) + a0 * 16 * 40 + 24);

    for (di = 0; di < 22; di += 2) {
        asm_02ad(0x3300, a1 * 16 * 40 + (di + a2) + 2);
        asm_02ad(0x3320, (a0 * 16 * 40 + di + a2) + a1 * 16 * 40 + 2);
    }
}

void g2_3f68(void)
{
    register int i;

    if (d_0b9f < 0x28)
        ++d_0b9f;
    if (d_0b9f == 0x28) {
        d_5305_ += 2;
        if (d_5305_ % 26 == 0)
            d_0b9f = 0;
        if (d_5305_ > 0x1ee)
            d_5305_ = 0;
    }
    ++d_039f;
    if (d_039f == 4)
        d_039f = 0;
    for (i = 0; i < 26; ++i)
        g2_385b(*(int near *)&d_0d04[d_5305_ + i], i + 2,
                d_0ce1[d_039f + i] + 0xa2);
}

void g2_3fe1(void)
{
    while (d_a0fa_ == 0x18)
        ;
#if EPISODE != 3
    g2_3114();
#endif
}

void g2_3fed(void)
{
    while (d_a0fa_ == 0x17)
        ;
    g2_3114();
    g2_37b6("Instructions", 0x0e, 0);
}

void pascal g2_4009(register int a0)
{
    d_cc81_ = 0;
    for (;;) {
#if EPISODE == 1
        d_a0fa_ = 0;
#endif
        g2_3d8c(a0, 3, 7);
        outport(0x3ce, 5);
        g2_42a3(a0);
        g2_194d(a0);
        g2_37b6("Modify which action?", a0 + 1, 15);
        g2_37b6("choose(1-6):", a0 + 1, 16);
        g2_37b6("  Press 'ESC' to exit.", a0 + 1, 20);
        for (;;) {
            while (d_a0fa_ == 0x25)
                ;
            g2_2870(a0 + 14, 16);
            if (d_a0fa_ == 1)
                return;
            switch (d_a0fa_) {
            case 2:
                g2_37b6("Modifying UP.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa_ == 2)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa_ != 1) {
                    d_a0fa_ = g2_276f();
                    d_02f4 = d_a0fa_;
                    enable();
                    break;
                }
                break;
            case 3:
                g2_37b6("Modifying DOWN.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa_ == 3)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa_ != 1) {
                    d_a0fa_ = g2_276f();
                    d_02f5 = d_a0fa_;
                    enable();
                    break;
                }
                break;
            case 4:
                g2_37b6("Modifying LEFT.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa_ == 4)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa_ != 1) {
                    d_a0fa_ = g2_276f();
                    d_02f6 = d_a0fa_;
                    enable();
                    break;
                }
                break;
            case 5:
                g2_37b6("Modifying RIGHT.          ", a0 + 1, 18);
                g2_37b6("  hit new key:            ", a0 + 1, 19);
                while (d_a0fa_ == 5)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa_ != 1) {
                    d_a0fa_ = g2_276f();
                    d_02f7 = d_a0fa_;
                    enable();
                    break;
                }
                break;
            case 6:
                g2_37b6("Modifying FIRE.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa_ == 6)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa_ != 1) {
                    d_a0fa_ = g2_276f();
                    d_02f8 = d_a0fa_;
                    enable();
                    break;
                }
                break;
            case 7:
                g2_37b6("Modifying JUMP.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa_ == 7)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa_ != 1) {
                    d_a0fa_ = g2_276f();
                    d_02f9 = d_a0fa_;
                    enable();
                    break;
                }
                break;
            }
            break;
        }
    }
}

void pascal g2_42a3(register int a0)
{
    g2_37b6("      KEYBOARD MODE", a0, 7);
    g2_37b6("                        ", a0 + 1, 8);
    g2_37b6("  1.  Up     :", a0 + 1, 9);
    g2_37b6("  2.  Down   :", a0 + 1, 10);
    g2_37b6("  3.  Left   :", a0 + 1, 11);
    g2_37b6("  4.  Right  :", a0 + 1, 12);
    g2_37b6("  5.  Fire   :", a0 + 1, 13);
    g2_37b6("  6.  Jump   :", a0 + 1, 14);
}

/* Dr. Proton taunt shown at the end of a level; text differs per episode. */
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

void pascal g2_44f5(register int a0)
{
    g2_37b6(" Hold the joystick in the", a0, 9);
    g2_37b6(" upper left and press a", a0, 10);
    g2_37b6(" button.", a0, 11);
}

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

