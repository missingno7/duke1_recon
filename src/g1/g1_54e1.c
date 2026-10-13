struct g1_54e1_record { int state, x, y; };
extern struct g1_54e1_record d_a0ff_[];
extern int d_0437;
extern int d_05ac;
extern int d_06dc;
extern int d_06de;
extern int d_d57e_[];
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
void pascal g1_0042(int a0) {}
void pascal g1_2e64(int a0, int a1) {}
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_5427(int a0, int a1, int a2) {}
int g1_367e(int a0, int a1) { return 0; }
void pascal g1_1b8a(int a0, int a1, int a2) {}
/*@body*/
void g1_54e1(void)
{
    register int i;
    struct g1_54e1_record far *p;

    ++d_06de;
    if (d_06de == 2) {
        d_06de = 0;
        ++d_06dc;
    }
    if (d_06dc == 2)
        d_06dc = 0;

    for (i = 0; i < d_05ac; ++i) {
        p = &d_a0ff_[i];
        if (p->state == 0)
            continue;

        if (g1_3558(p->x, p->y) != 0 ||
            g1_3558(p->x + 2, p->y) != 0)
            ++d_d57e_[i];

        if (d_d57e_[i] == 2) {
            g1_314c(p->x + 2, p->y);
            g1_314c(p->x, p->y);
            g1_2b86(1, p->x + 1, p->y);
            g1_0b85(0x9c4L);
            g1_0042(0x12);
            p->state = 0;
            continue;
        }

        if (d_d57e_[i] == 1 && d_0437 == 0) {
            g1_2e64(p->x + 2, p->y - 0x40);
        }
        if (g1_3714(p->x, p->y + 0x80) == 0) {
            p->y += 0x20;
            g1_5427(0, p->x, p->y);
            continue;
        }

        if (p->state == 1) {
            if (g1_367e(p->x, p->y) != 0) {
                p->state = 2;
                g1_1b8a(2, p->x + 4, p->y - 0x40);
            } else if (g1_367e(p->x, p->y + 0x80) == 0) {
                p->state = 2;
                g1_1b8a(2, p->x + 4, p->y - 0x40);
            } else {
                if (d_06de == 0)
                    --p->x;
                g1_5427(d_06dc, p->x, p->y);
            }
        }

        if (p->state == 2) {
            if (g1_367e(p->x + 4, p->y) != 0 ||
                g1_367e(p->x + 4, p->y + 0x80) == 0) {
                p->state = 1;
                g1_1b8a(1, p->x - 2, p->y - 0x40);
                g1_5427(d_06dc + 2, p->x - 1, p->y);
                continue;
            }
            if (d_06de == 0)
                ++p->x;
            g1_5427(d_06dc + 2, p->x, p->y);
        }
    }
}
