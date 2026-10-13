#include <dos.h>
extern char d_02fa;
extern char d_0436;
extern char d_06e2;
extern int d_4ed2;
extern char d_555a;
extern char d_c68c;
extern char d_d138;
extern char d_d13f;
extern int d_d4bd;
extern char d_d4c0;
extern int d_d4c1;
extern int d_d570;
void g2_16f3(void);

int g1_3513(int a0, int a1) { return 0; }
void pascal g1_6183(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
/*@body*/
void g1_6292(void)
{
    ++d_06e2;
    if (d_06e2 == 1)
        d_06e2 = 0;

    if (d_d570 == 0)
        return;

    if (g1_3513(d_d4bd + 1, d_d4c1) ||
        g1_3513(d_d4bd + 1, d_d4c1 - 128)) {
        if (d_555a) {
            g2_16f3();
            d_555a = 0;
        }
    }

    if (d_4ed2 != 0)
        goto after_gates;
    if (d_c68c == 0)
        goto after_gates;
    if (d_d13f != 0)
        goto after_gates;
    if (d_d4c0 != 0)
        goto after_gates;
    if (d_d138 != 0)
        goto after_gates;
    if (g1_3513(d_d4bd + 1, d_d4c1) ||
        g1_3513(d_d4bd + 1, d_d4c1 - 128)) {
        d_4ed2 = 1;
        if (d_02fa % 2 != 0)
            g1_0042(0x27);
        disable();
        d_c68c = 0;
        enable();
    }

after_gates:
    if (d_4ed2 == 0)
        g1_6183(0, d_d4bd, d_d4c1);
    if (d_4ed2 == 0)
        return;

    if (d_06e2 == 0)
        ++d_4ed2;
    if (d_4ed2 < 5) {
        if (d_4ed2 == 3 && d_02fa % 2 == 0)
            g1_0042(0x13);
        g1_6183(d_4ed2 - 1, d_d4bd, d_d4c1);
        return;
    }
    if (d_4ed2 < 5)
        return;

    switch (d_4ed2) {
    case 4:
        g1_6183(3, d_d4bd, d_d4c1);
        break;
    case 5:
        g1_6183(2, d_d4bd, d_d4c1);
        break;
    case 6:
        g1_6183(1, d_d4bd, d_d4c1);
        break;
    case 7:
        g1_6183(0, d_d4bd, d_d4c1);
        break;
    case 8:
        g1_6183(0, d_d4bd, d_d4c1);
        d_0436 = 1;
        break;
    }
}







