/* goto kept: the counter timeout leaves the wait loop past the first fade-in wait; the
   structured while/break forms (receipts 6337ed3791d958c7, dab76c2736839010) emit 756 bytes. */
#include <dos.h>
extern int d_02fb;
extern char d_a0fa;
extern char far *d_a0fb;
extern int d_b9dc;
extern char d_cc81;
extern char d_d56b;
void pascal g2_01a9(int a0);
void g2_3114(void);
void g2_3568(void);
void pascal g2_0036(int a0);
void g2_44a5(void);
void pascal g2_452b(int a0);
void g2_36c1(void);
void g2_340f(void);
void g2_4334(void);
void g2_4394(void);
void g2_43f5(void);
void g2_4444(void);
void g2_2473(void);
void asm_0424(char far *a0, int a1, int a2);
void pascal g1_0b85(long a0) {}
void pascal g1_e92e(int a0) {}
/*@body*/
void g1_e947(void)
{
    register int i;
    register int phase;
    long counter;
    int button1;
    int button2;

    counter = 0L;
    phase = 0;
    g1_0b85(100000L);
    if (d_b9dc != 0) {
        g2_01a9(10);
        g2_36c1();
        g2_0036(10);
        for (i = 0; i < 0x34; ++i) {
            phase = !phase;
            asm_0424(d_a0fb + (phase % 2) * 0xa0 + 0x5820,
                     0x1a, 0x7d - i);
            g1_e92e(10);
        }
        for (i = 0; i < 0x32; ++i) {
            phase = !phase;
            asm_0424(d_a0fb + (phase % 2) * 0xa0 + 0x5820,
                     0x1a, 0x4a);
            g1_e92e(10);
        }
        for (i = 0; i < 5; ++i) {
            asm_0424(d_a0fb + i * 0xa0 + 0x5960,
                     0x1a, 0x4b - i);
            g1_e92e(14);
        }

        counter = 0L;
        d_a0fa = 0;
        if (d_d56b != 0) {
            button1 = inportb(0x201) & 0x10;
            button2 = inportb(0x201) & 0x20;
        } else {
                button1 = button2 = 1;
            }
            while (d_a0fa == 0 && button1 != 0 && button2 != 0) {
                if (d_d56b != 0) {
                    button1 = inportb(0x201) & 0x10;
                    button2 = inportb(0x201) & 0x20;
                } else {
                    button1 = button2 = 1;
                }
                if (d_02fb % 2 != 0) {
                    ++counter;
                    if (counter == 0x16e360L) {
                        g2_01a9(10);
                        g2_340f();
                        g2_0036(10);
                        goto stage_after_first;
                    }
                    if (counter == 0x493e0L)
                        g2_2473();
                }
            }

            g2_01a9(10);
            g2_340f();
            g2_0036(10);
            if (d_cc81 == 0) {
                do {
                } while ((d_a0fa & 0x80) == 0);
            }
    stage_after_first:
            g2_4334();
            d_02fb = 0;

            g2_01a9(10);
            g2_3568();
            g2_0036(10);
            if (d_cc81 == 0) {
                do {
                } while ((d_a0fa & 0x80) == 0);
            }
            g2_4394();
            d_02fb = 0;

            g2_01a9(10);
            g2_340f();
            g2_0036(10);
            if (d_cc81 == 0) {
                do {
                } while ((d_a0fa & 0x80) == 0);
            }
            g2_43f5();
            d_02fb = 0;

            g2_01a9(10);
            g2_3568();
            g2_0036(10);
            if (d_cc81 == 0) {
                do {
                } while ((d_a0fa & 0x80) == 0);
            }
            g2_4444();
            g2_01a9(10);
        } else {
        d_02fb = 0;
        while (d_02fb < 500) {
        }
        g2_01a9(20);
        g2_3114();
        g2_3568();
        g2_0036(20);
        if (d_cc81 == 0) {
            do {
            } while ((d_a0fa & 0x80) == 0);
        }
        g2_44a5();
        g2_01a9(20);
    }
    d_02fb = 0;
    g2_452b(7);
}
