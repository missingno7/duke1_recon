#include <dos.h>
extern char d_0094;
extern char d_02fa;      /* accepted type */
extern int d_02fb;       /* accepted type */
extern char d_a0fa_;      /* accepted type */
void pascal g2_3d8c(int a0, int a1, int a2);    /* accepted signature */
void pascal g2_1a0d(int a0);    /* accepted signature */
void pascal g2_2870(int a0, int a1);    /* accepted signature */
void pascal g2_1bb0(int a0);    /* accepted signature */
void g2_0d39(void);    /* accepted signature */
void g2_0d97(void);    /* accepted signature */
void pascal g2_1d40(int a0);    /* accepted signature */
void pascal g2_1ee1(int a0);    /* accepted signature */
char pascal g1_0351(int a0) { return 0; }    /* accepted signature; stub for push cs; call near */
void pascal g1_008a(int a0) {}    /* accepted signature; stub for push cs; call near */
/*@body*/
void pascal g1_037e(register int a0)
{
    outport(0x3ce, 0x105);
    for (;;) {
        g2_3d8c(a0, 1, 5);
        outport(0x3ce, 5);
        g2_1a0d(a0);
        delay(100);
        for (;;) {
            g2_2870(0x1a, 0x0c);
            if (d_a0fa_ == 1 || d_a0fa_ == 0x39 || d_a0fa_ == 0x1c) {
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x1f) {
                if (d_02fa % 2 == 0) {
                    g2_1bb0(a0);
                    d_02fb = 0;
                    return;
                }
                if (g1_0351(a0)) {
                    g2_0d39();
                    d_02fb = 0;
                    return;
                }
                g2_0d97();
                break;
            }
            if (d_a0fa_ == 0x23) {
                g2_1d40(a0);
                while (d_a0fa_ == 0x23)
                    ;
                g2_2870(a0 + 0x18, 0x14);
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x17) {
                g2_1ee1(a0);
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 1 || d_a0fa_ == 0x10 || d_a0fa_ == 0x39) {
                d_a0fa_ = 0;
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x22) {
                g1_008a(a0);
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x44) {
                d_0094 = 1;
                d_02fb = 0;
                return;
            }
        }
    }
}
