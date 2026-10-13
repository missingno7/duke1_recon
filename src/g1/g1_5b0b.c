struct g1_5b0b_record { int state, x, y; };
extern struct g1_5b0b_record d_abec[];
extern int d_0437;
extern int d_05ae;
extern int d_05b0;
extern int d_05b2;
extern int d_4eda[];
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2e64(int a0, int a1) {}
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_59cf(int a0, int a1, int a2) {}
int g1_367e(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
/*@body*/
void g1_5b0b(void)
{
    register int i;
    struct g1_5b0b_record far *p;

    ++d_05ae;
    ++d_05b0;
    if (d_05b0 == 0x3c)
        d_05b0 = 0;

    if (d_05b0 < 0x19 && d_05ae >= 4)
        d_05ae = 0;
    if (d_05b0 >= 0x19 && d_05ae >= 8)
        d_05ae = 4;

    for (i = 0; i < d_05b2; ++i) {
        p = &d_abec[i];
        if (p->state != 0) {
            if ((g1_3558(p->x, p->y) != 0 ||
                 g1_3558(p->x + 2, p->y) != 0) && d_05b0 < 0x19)
                ++d_4eda[i];

            if (d_4eda[i] == 2) {
                g1_314c(p->x + 2, p->y);
                g1_314c(p->x, p->y);
                g1_2e64(p->x + 2, p->y - 0x80);
                g1_2b86(1, p->x + 1, p->y);
                g1_2b86(1, p->x + 1, p->y - 0x80);
                g1_2b86(1, p->x, p->y - 0x80);
                g1_0b85(5000L);
                p->state = 0;
                continue;
            }

            if (d_4eda[i] == 1 && d_0437 == 0)
                g1_2e64(p->x + 2, p->y - 0x40);

            if (g1_3714(p->x + 1, p->y + 0x80) == 0) {
                p->y += 0x80;
                g1_59cf(d_05ae, p->x, p->y);
                continue;
            }

            if (p->state == 1) {
                if (g1_367e(p->x, p->y + 0x80) == 0 || g1_367e(p->x, p->y) != 0) {
                    p->state = 2;
                } else {
                    if (d_0437 == 0x40 || d_0437 == 0)
                        --p->x;
                    g1_59cf(d_05ae, p->x, p->y);
                    continue;
                }
            }

            if (p->state == 2) {
                if (g1_367e(p->x + 3, p->y + 0x80) == 0 || g1_367e(p->x + 3, p->y) != 0)
                    p->state = 1;
                else if (d_0437 == 0x40 || d_0437 == 0)
                    ++p->x;
                g1_59cf(d_05ae, p->x, p->y);
            }
        }
    }
}
