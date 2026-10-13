extern int d_0099;
extern int d_009d;
extern int d_009f;
extern char d_0644;
extern char d_68f7;
extern int d_c279;
extern int d_c27b;
extern int d_c28b;
extern int d_c28d;
extern int d_c686;
extern int d_c688;
extern int d_c68a;
extern char d_c68c;
extern char d_d138;
extern int d_d13b;
extern char d_d13f;
extern char d_d4c0;
void g2_18b8(void);
void pascal g1_9bb5(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
/*@body*/
void g1_a125(void)
{
    if (d_c688 == 0)
        return;

    if (d_d13b == 1) {
        d_d13b = 0;
        d_009d = d_c279 - d_0099 + 2;
        d_009f = d_c28b + 0xfd00;
        d_0644 = 1;
        d_c68c = 0;
        d_c686 = 8;
        d_c68a = 0;
    }

    if (d_d13b > 1)
        --d_d13b;

    if (d_c68a > 0)
        {
            g1_9bb5(d_c68a % 4, d_c27b, d_c28d);
            --d_c68a;
        }
    else
        g1_9bb5(d_d13b % 4, d_c27b, d_c28d);

    if (d_68f7 != 0 && g1_3513(d_c27b + 2, d_c28d)) {
        d_68f7 = 0;
        g2_18b8();
    }

    if (!g1_3513(d_c27b + 2, d_c28d))
        return;

    if (d_c68c != 0 && d_d13b == 0 && d_d13f == 0 &&
        d_d4c0 == 0 && d_d138 == 0) {
        d_d13b = 8;
        g1_0042(7);
    }
}

