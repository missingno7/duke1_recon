struct g1_8069_record { int f0, f2, f4, f6, f8, fa; };
extern struct g1_8069_record d_5ec9_[];
extern int d_0099;
extern int d_009d;
extern int d_0437;
extern int d_05ce;
extern int d_06f1;
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_7f4a(int a0, int a1, int a2) {}
void pascal g1_7dff(int a0, int a1, int a2) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2fe7(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
int g1_367e(int a0, int a1) { return 0; }
/*@body*/
void g1_8069(void)
{
    register int i;
    struct g1_8069_record far *p;

    d_06f1 = !d_06f1;
    for (i = 0; i < d_05ce; i++) {
        p = &d_5ec9_[i];
        if (p->f0 == 0)
            continue;

        if (g1_326e(p->f2, p->f4) == 0 && p->f6 == 0) {
            if (g1_3714(p->f2 + 3, p->f4 + 128))
                p->f6 = 24;
            else
                p->f6 = 1;
        }

        if (p->f6 == 0)
            continue;

        if (p->f6 > 2) {
            --p->f6;
            p->f4 -= 16;
        }
        if (p->fa > 1 && p->f6 <= 2) {
            p->f4 += 16;
            ++p->fa;
            if (p->fa >= 24 || g1_3714(p->f2 + 3, p->f4 + 128)) {
                p->f6 = 24;
                p->fa = 0;
            }
        }

        if (p->f2 + 3 > d_0099 + d_009d) {
            p->f0 = 2;
            if (d_0437 == 0 || d_0437 == 0x40) {
                if (g1_367e(p->f2 - 2, p->f4) == 0)
                    --p->f2;
            }
        } else if (p->f2 + 3 < d_0099 + d_009d) {
            p->f0 = 3;
            if (d_0437 == 0 || d_0437 == 0x40) {
                if (g1_367e(p->f2 + 8, p->f4) == 0)
                    ++p->f2;
            }
        } else {
            if (p->f6 < 3 && p->fa == 0)
                p->fa = 2;
            p->f0 = 1;
        }

        if (g1_3558(p->f2, p->f4) ||
            g1_3558(p->f2 + 8, p->f4) ||
            g1_3558(p->f2 + 4, p->f4 - 128)) {
            if (p->f8 != 0)
                --p->f8;
        }
        if (p->f8 < 4 && d_0437 == 0)
            g1_2e64(p->f2 + 3, p->f4 - 96);
        if (p->f8 < 3 && d_0437 == 0x20)
            g1_2e64(p->f2, p->f4 - 96);
        if (p->f8 < 2 && d_0437 == 0x40)
            g1_2e64(p->f2 + 2, p->f4 - 128);

        if (p->f8 == 0) {
            if (g1_3714(p->f2, p->f4 + 128) ||
                g1_3714(p->f2 + 8, p->f4 + 128)) {
                g1_314c(p->f2, p->f4);
                g1_314c(p->f2 + 2, p->f4 - 64);
                g1_314c(p->f2 + 4, p->f4);
                g1_314c(p->f2 + 6, p->f4 - 64);
                g1_314c(p->f2 + 8, p->f4);
                g1_2fe7(p->f2 + 1, p->f4 - 32);
                g1_2fe7(p->f2 + 5, p->f4 - 128);
                g1_2b86(1, p->f2 + 1, p->f4 - 32);
                g1_2b86(1, p->f2 + 7, p->f4 - 64);
                g1_2b86(1, p->f2 + 1, p->f4 - 32);
                g1_2b86(1, p->f2 + 2, p->f4 - 128);
                g1_2b86(1, p->f2 + 3, p->f4 - 128);
                g1_2b86(1, p->f2 + 5, p->f4 - 32);
                p->f0 = 0;
                g1_0b85(5000L);
                continue;
            }
            p->f4 += 32;
        }

        switch (p->f0) {
        case 2:
            g1_7f4a(d_06f1, p->f2, p->f4 - 128);
            g1_7dff(0, p->f2, p->f4);
            break;
        case 1:
            g1_7f4a(d_06f1 + 2, p->f2, p->f4 - 128);
            g1_7dff(1, p->f2, p->f4);
            break;
        case 3:
            g1_7f4a(d_06f1 + 4, p->f2, p->f4 - 128);
            g1_7dff(2, p->f2, p->f4);
            break;
        }
    }
}










