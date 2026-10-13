extern int d_0099;
extern int d_009d;
extern int d_009f;
extern char d_0644;
extern char d_68f7;
extern int d_c279;
extern int d_c27b;
extern int d_c28b;
extern int d_c28d;
extern int d_c684;
extern int d_c686;
extern int d_c68a;
extern char d_c68c;
extern char d_d138;
extern int d_d139;
extern char d_d13f;
extern char d_d4c0;
void g2_18b8(void);
void pascal g1_9bb5(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
/*@body*/
void g1_a032(void)
{
    if (d_c684 != 0) {
        if (d_d139 == 1) {
            d_d139 = 0;
            d_009d = d_c27b - d_0099 + 2;
            d_009f = d_c28d - 0x300;
            d_0644 = 1;
            d_c68c = 0;
            d_c68a = 8;
            d_c686 = 0;
        }

        if (d_d139 > 1)
            --d_d139;
        if (d_c686 > 0) {
            g1_9bb5(d_c686 % 4, d_c279, d_c28b);
            --d_c686;
        } else {
            g1_9bb5(d_d139 % 4, d_c279, d_c28b);
        }

        if (d_68f7 != 0) {
            if (g1_3513(d_c279 + 2, d_c28b)) {
                d_68f7 = 0;
                g2_18b8();
            }
        }
        if (g1_3513(d_c279 + 2, d_c28b)) {
            if (d_c68c != 0 && d_d139 == 0 && d_d13f == 0 &&
                d_d4c0 == 0 && d_d138 == 0) {
                d_d139 = 8;
                g1_0042(7);
            }
        }
    }
}
