/* goto kept (STRUCTURING BACKLOG): label-level transliteration that matches; the best
   structured form so far (cand_structured_989.c) is 989/981 bytes.  To be restructured. */
#include <dos.h>
extern int d_0095;
extern int d_02fb;
extern char d_530e;
extern char d_a0fa;
extern char d_cc81;
extern char d_d135;
extern char d_d56b;
void g2_3114(void);
void pascal g2_01a9(int a0);
void g2_32b6(void);
void pascal g2_0036(int a0);
void g2_3fe1(void);
void g2_02f4(void);
void g2_315d(void);
int pascal g2_3d1e(int a0);
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_38be(int a0);
void pascal g2_1d40(int a0);
void pascal g2_2870(int a0, int a1);
void g2_0e19(void);
void g2_062c(void);
void g2_0491(void);
void g1_006f(int a0) {}
void pascal g1_008a(int a0) {}
/*@body*/
int pascal g1_049f(register int a0)
{
    unsigned long ticks;
    unsigned char button1;
    unsigned char button2;

    ticks = 0;
    button1 = inportb(0x201) & 0x10;
    button2 = inportb(0x201) & 0x20;
    if (d_d56b == 0) {
        button1 = 1;
        button2 = 1;
    }
    g2_3114();

L_04d6:
    g2_01a9(20);
    g2_32b6();
    g2_0036(20);
    ticks = 0;
    d_a0fa = 0;
    goto L_058c;

L_04ff:
    if (d_d56b != 0) {
        button1 = inportb(0x201) & 0x10;
        button2 = inportb(0x201) & 0x20;
    }
    if (d_02fb % 2 != 0) {
        ++ticks;
        if (ticks == 0x16e360UL) {
            d_a0fa = 0;
            goto L_07bf;
        }
        if (ticks == 0xf4240UL) {
            g2_01a9(20);
            g2_3fe1();
            g2_02f4();
            g2_0036(20);
        }
        if (ticks == 0x7a120UL) {
            g2_01a9(20);
            g2_315d();
            g2_0036(20);
        }
    }

L_058c:
    if (d_a0fa == 0 && button1 != 0 && button2 != 0)
        goto L_04ff;

L_05a2:
    if (d_a0fa == 0x10)
        goto L_05b0;
    if (d_a0fa != 1)
        goto L_05d6;
L_05b0:
    if (ticks >= 0x7a120UL)
        goto L_05d6;
L_05bf:
    while (d_a0fa == 0x10) {
    }
    if (g2_3d1e(7) != 0)
        goto L_07ff;

L_05d6:
    ticks = 0;
    outport(0x3ce, 0x105);
    goto L_0608;

L_05f2:
    if (d_d56b != 0) {
        button1 = inportb(0x201) & 0x10;
        button2 = inportb(0x201) & 0x20;
    }
L_0608:
    if (button1 == 0 || button2 == 0)
        goto L_05f2;
    ticks = 0;
    g2_3d8c(a0, 2, 8);
    outport(0x3ce, 5);
    g2_38be(a0);
    g2_0036(15);
L_064b:
    d_a0fa = 0;
    goto L_067b;

L_0652:
    ++ticks;
    if (ticks <= 0xbbaee0UL)
        goto L_067b;
    d_a0fa = 0;
    g2_01a9(20);
    goto L_07bf;

L_067b:
    if (d_d56b != 0) {
        button1 = inportb(0x201) & 0x10;
        button2 = inportb(0x201) & 0x20;
    }
    if (d_a0fa == 0 && button1 != 0 && button2 != 0)
        goto L_0652;
    if (d_a0fa == 0x1f || d_a0fa == 0x39 || d_a0fa == 0x1c)
        goto L_0714;
    if (button1 == 0)
        goto L_06e0;
    if (button2 != 0)
        goto L_071a;
    goto L_06e0;

L_06ca:
    if (d_d56b != 0) {
        button1 = inportb(0x201) & 0x10;
        button2 = inportb(0x201) & 0x20;
    }
L_06e0:
    if (button1 == 0 || button2 == 0)
        goto L_06ca;
    if (d_cc81 == 0 && d_d56b != 0)
        g1_006f(a0);
    if (d_cc81 == 0)
        goto L_0608;
    g2_01a9(20);
L_0714:
    return 1;

L_071a:
    if (d_a0fa == 0xc0 && d_d135 != 0 && d_0095 != 0)
        return 4;
    if (d_a0fa != 0x2e)
        goto L_0769;
L_073c:
    while (d_a0fa == 0x2e) {
    }
    g2_01a9(15);
    g2_315d();
    g2_0036(15);
    d_a0fa = 0;
    while (d_a0fa == 0) {
    }
    goto L_085c;

L_0769:
    if (d_a0fa != 0x23)
        goto L_078f;
L_0770:
    g2_1d40(a0);
    while (d_a0fa == 0x23) {
    }
    g2_2870(a0 + 0x18, 20);
    goto L_085c;

L_078f:
    if (d_a0fa != 0x2f)
        goto L_07ab;
L_0796:
    if (d_530e == 0)
        goto L_07a5;
    g2_0e19();
    goto L_085c;

L_07a5:
    return 2;
L_07ab:
    if (d_a0fa == 0x13)
        return 3;
    if (d_a0fa != 0x19)
        goto L_07c5;
L_07bf:
    return 5;
L_07c5:
    if (d_a0fa != 0x17)
        goto L_07dd;
L_07cc:
    g2_01a9(15);
    g2_062c();
    goto L_085c;

L_07dd:
    if (d_a0fa == 1)
        goto L_07eb;
    if (d_a0fa != 0x10)
        goto L_0803;
L_07eb:
    while (d_a0fa == 0x10) {
    }
    if (g2_3d1e(7) == 0)
        goto L_085c;
L_07ff:
    return 0;

L_0803:
    if (d_a0fa != 0x22)
        goto L_0811;
    g1_008a(a0);
    goto L_085c;

L_0811:
    if (d_a0fa == 0x14)
        goto L_04d6;
    if (d_a0fa != 0x18)
        goto L_064b;
L_0825:
    g2_01a9(15);
    g2_3fe1();
    g2_02f4();
    g2_2870(0x27, 0x18);
    g2_3114();
    g2_0491();
    g2_2870(0x27, 0x18);

L_085c:
    g2_01a9(15);
    g2_32b6();
    goto L_0608;
}
