#include <dos.h>
extern char d_a0fa;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_148f(int a0);
void pascal g2_2870(int a0, int a1);
void pascal g2_4009(int a0);
void pascal g2_1058(int a0);
void pascal g2_10f0(int a0);
void g1_006f(int a0) {}
/*@body*/
void pascal g1_008a(register int a0)
{
    g2_3d8c(a0, 2, 4);
    outport(0x3ce, 5);
    g2_148f(a0);
    delay(100);
    do {
        g2_2870(a0 + 0x18, 0x0c);
        if (d_a0fa == 0x24) {
            g1_006f(a0);
            return;
        }
        if (d_a0fa == 0x25) {
            g2_4009(a0);
            return;
        }
        if (d_a0fa == 0x1f) {
            g2_1058(a0);
            return;
        }
        if (d_a0fa == 0x23) {
            g2_10f0(a0);
            return;
        }
    } while (d_a0fa != 0x1c && d_a0fa != 1 && d_a0fa != 0x39);
}
