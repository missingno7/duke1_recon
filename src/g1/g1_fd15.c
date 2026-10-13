extern char d_0098;
extern char d_03a3;
extern int d_040c;
extern char d_0b46;
extern char d_530e;
extern char d_5553;
extern char d_5554;
extern char d_5555;
extern char d_555a;
extern char d_555b;
extern char d_555c;
extern char d_5a11;
extern char d_5c6a;
extern char d_5c6b;
extern char d_5ec8;
extern char d_637e;
extern char d_68f7;
extern char d_a0fa;
extern char d_c278;
extern char d_c683;
extern char d_cc81;
void g2_3114(void);
void pascal g2_0009(int a0);
void pascal g2_01a9(int a0);
void g2_340f(void);
void pascal g2_0036(int a0);
void g2_3bd7(void);
void g2_3568(void);
void g2_3c38(void);
int pascal g1_049f(int a0) { return 0; }
unsigned char pascal g1_0126(int a0) { return 0; }
void g1_fc9c(void) {}
void pascal g1_0042(int a0) {}
/*@body*/
void g1_fd15(void)
{
    register int state;

    for (;;) {
        g2_3114();
        state = g1_049f(7);

        d_5a11 = 0;
        d_5c6b = 0;
        d_5554 = 0;
        d_637e = 0;
        d_5ec8 = 0;
        d_555a = 0;
        d_555c = 0;
        d_5553 = 0;
        d_555b = 0;
        d_68f7 = 0;
        d_5555 = 0;
        d_5c6a = 0;

        if (state == 1) {
            d_c683 = 0;
            d_c278 = 1;
            d_040c = 0;
            d_0098 = 1;
            d_03a3 = 0;
            g2_01a9(0x14);
            g2_340f();
            g2_0036(0x14);
            if (d_cc81 == 0) {
                while ((d_a0fa & 0x80) == 0) {
                }
            }
            g2_3bd7();
            g2_01a9(0x14);
            g2_3568();
            g2_0036(0x14);
            if (d_cc81 == 0) {
                while ((d_a0fa & 0x80) == 0) {
                }
            }
            g2_3c38();
            d_530e = 0;
            g2_0009(0x14);
            if (d_0b46 == 1) {
                d_5a11 = 1;
                d_5c6b = 1;
                d_5554 = 1;
                d_637e = 1;
                d_5ec8 = 1;
                d_555a = 1;
                d_555c = 1;
                d_5553 = 1;
                d_555b = 1;
                d_68f7 = 1;
                d_5555 = 1;
                d_5c6a = 1;
            }
            g1_0042(0x1a);
            return;
        }

        if (state == 2) {
            if (d_c278 == 0)
                continue;
            d_c683 = 1;
            d_0098 = 0;
            d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 3 && g1_0126(7) != 0) {
            d_03a3 = 1;
            d_c683 = 0;
            d_0098 = 0;
            if (d_0b46 == 1) {
                d_5a11 = 1;
                d_5c6b = 1;
                d_5554 = 1;
                d_637e = 1;
                d_5ec8 = 1;
                d_555a = 1;
                d_555c = 1;
                d_5553 = 1;
                d_555b = 1;
                d_68f7 = 1;
                d_5555 = 1;
                d_5c6a = 1;
            }
            return;
        }

        if (state == 4) {
            d_c683 = 0;
            d_c278 = 1;
            d_040c = 0;
            d_0098 = 2;
            if (0)      /* unreachable store present in the original: TC 2.0 keeps if (0) bodies */
                d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 5) {
            if (d_c278 == 0)
                continue;
            d_c683 = 2;
            d_0098 = 0;
            d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 0) {
            g2_01a9(0x14);
            g1_fc9c();
            continue;
        }
    }
}
