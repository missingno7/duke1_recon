#include <dos.h>
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
extern char d_a0fa;
extern char d_cc81;
void pascal g2_42a3(int a0);
void pascal g2_3d8c(int a0, int a1, int a2) {}
void pascal g2_194d(int a0) {}
void pascal g2_37b6(char far *a0, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
char g2_276f(void) { return 0; }
/*@body*/
void pascal g2_4009(register int a0)
{
    d_cc81 = 0;
    for (;;) {
#if EPISODE == 1
        d_a0fa = 0;
#endif
        g2_3d8c(a0, 3, 7);
        outport(0x3ce, 5);
        g2_42a3(a0);
        g2_194d(a0);
        g2_37b6("Modify which action?", a0 + 1, 15);
        g2_37b6("choose(1-6):", a0 + 1, 16);
        g2_37b6("  Press 'ESC' to exit.", a0 + 1, 20);
        for (;;) {
            while (d_a0fa == 0x25)
                ;
            g2_2870(a0 + 14, 16);
            if (d_a0fa == 1)
                return;
            switch (d_a0fa) {
            case 2:
                g2_37b6("Modifying UP.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa == 2)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa != 1) {
                    d_a0fa = g2_276f();
                    d_02f4 = d_a0fa;
                    enable();
                    break;
                }
                break;
            case 3:
                g2_37b6("Modifying DOWN.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa == 3)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa != 1) {
                    d_a0fa = g2_276f();
                    d_02f5 = d_a0fa;
                    enable();
                    break;
                }
                break;
            case 4:
                g2_37b6("Modifying LEFT.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa == 4)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa != 1) {
                    d_a0fa = g2_276f();
                    d_02f6 = d_a0fa;
                    enable();
                    break;
                }
                break;
            case 5:
                g2_37b6("Modifying RIGHT.          ", a0 + 1, 18);
                g2_37b6("  hit new key:            ", a0 + 1, 19);
                while (d_a0fa == 5)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa != 1) {
                    d_a0fa = g2_276f();
                    d_02f7 = d_a0fa;
                    enable();
                    break;
                }
                break;
            case 6:
                g2_37b6("Modifying FIRE.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa == 6)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa != 1) {
                    d_a0fa = g2_276f();
                    d_02f8 = d_a0fa;
                    enable();
                    break;
                }
                break;
            case 7:
                g2_37b6("Modifying JUMP.          ", a0 + 1, 18);
                g2_37b6("  Hit new key:            ", a0 + 1, 19);
                while (d_a0fa == 7)
                    ;
                g2_2870(a0 + 16, 19);
                if (d_a0fa != 1) {
                    d_a0fa = g2_276f();
                    d_02f9 = d_a0fa;
                    enable();
                    break;
                }
                break;
            }
            break;
        }
    }
}
