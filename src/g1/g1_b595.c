extern int d_0099;
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_0602;
extern int d_0604;
extern int d_0606;
extern int d_0608;
extern int d_060a;
extern int d_060c;
extern int d_060e;
extern int d_0702[];
extern int d_5002;
extern int d_554a;
extern int d_b630;
extern int d_b634;
extern int d_b9dc;
extern int d_c283;
extern int d_c293;
extern char d_c68c;
extern char d_d134;
extern char d_d135;
extern char d_d138;
extern char d_d13f;
extern int d_d142;
extern char d_d4c0;
extern int d_d56c;
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_b292(int a0, int a1, int a2) {}
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_367e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_1b8a(int a0, int a1, int a2) {}
#include <dos.h>
/*@body*/
void g1_b595(void)
{
    if (d_554a != 0) {
        ++d_554a;
        if (d_554a == 10)
            d_c293 = 1;
        return;
    }

    d_0602 = !d_0602;
    if (d_c283 == 0)
        return;

    if (d_d56c != 2) {
        if (d_d56c != 0) {
            if (d_0608 == 0) {
                ++d_0604;
                if (d_0604 == (d_060c >> 1)) {
                    if (d_0099 + d_009d - 2 < d_b630)
                        g1_1b8a(1, d_b630, d_b634 - 32);
                    else
                        g1_1b8a(2, d_b630 + 3, d_b634 - 32);
                }
                if (d_0604 > d_060c) {
                    d_0604 = 0;
                    d_0606 = 0;
                    d_0608 = 1;
                    if (d_0099 + d_009d - 2 < d_b630)
                        d_060a = 1;
                    else
                        d_060a = 0;
                }
            } else {
                d_b634 += d_0702[d_0606];
                if (d_060a != 0) {
                    if (!g1_367e(d_b630 - 1, d_b634 - 64))
                        --d_b630;
                } else {
                    if (!g1_367e(d_b630 + 3, d_b634 - 64))
                        ++d_b630;
                }
                ++d_0606;
                if (d_0606 == 12) {
                    d_0608 = 0;
                    d_060c = (d_0437 >> 1) + 1;
                    d_0604 = 0;
                }
            }
            if (d_0099 + d_009d - 2 < d_b630)
                g1_b292(d_0602, d_b630, d_b634);
            else
                g1_b292(d_0602 + 2, d_b630, d_b634);
            if (g1_3558(d_b630 + 1, d_b634 - 64)) {
                g1_2b86(3, d_b630 + 2, d_b634 - 92);
                --d_d142;
            }
            if (d_0437 != 0 && d_d142 < 10) {
                if (d_d142 < 10)
                    g1_2e64(d_b630 + 2, d_b634 - 32);
                if (d_d142 < 6)
                    g1_2e64(d_b630 + 1, d_b634 - 64);
                if (d_d142 < 2)
                    g1_2e64(d_b630 + 3, d_b634 - 64);
            }
            if (d_d142 == 1 && d_b9dc != 0)
                d_d56c = 0;
            else if (d_d142 == 0)
                d_d56c = 2;
        } else {
            if (!g1_326e(d_b630, d_b634) && d_5002 == 0) {
                d_5002 = 1;
                g1_0042(40);
                disable();
                d_d135 = d_d138 = d_d13f = d_d4c0 = d_c68c = d_d134 = 0;
                enable();
            }
            if (d_5002 > 30)
                d_c293 = 1;
            if (d_5002 != 0)
                ++d_5002;
            if (d_5002 != 0 && d_b634 > 0x100 && d_009f > 0x100) {
                d_b634 -= 0x80;
                d_009f -= 0x80;
                d_060e = 1;
            }
            if (d_0099 + d_009d - 2 < d_b630)
                g1_b292(d_0602, d_b630, d_b634);
            else
                g1_b292(d_0602 + 2, d_b630, d_b634);
            return;
        }
    } else {
        d_b634 += 32;
        if (d_0437 == 0)
            g1_314c(d_b630 + 2, d_b634);
        if (d_0437 == 32)
            g1_2b86(1, d_b630 + 2, d_b634);
        if (d_0437 == 64)
            g1_314c(d_b630, d_b634);
        if (d_0437 == 96)
            g1_2b86(3, d_b630 + 2, d_b634);
        if (d_0099 + d_009d - 2 < d_b630)
            g1_b292(0, d_b630, d_b634);
        else
            g1_b292(2, d_b630, d_b634);
        if (g1_3714(d_b630 + 1, d_b634)) {
            g1_0042(41);
            d_554a = 1;
        }
        return;
    }
}
