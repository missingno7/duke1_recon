struct g1_4f91_record { int state, x, y, marker; };
extern struct g1_4f91_record d_b6bc_[];
extern int d_0099;
extern int d_009d;
extern int d_0437;
extern int d_05aa;
extern int d_0698[];
extern int d_5081_[];
char pascal g1_326e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2e64(int a0, int a1) {}
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_4d42(int a0, int a1, int a2) {}
int g1_367e(int a0, int a1) { return 0; }
void pascal g1_1b8a(int a0, int a1, int a2) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_2fe7(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
/*@body*/
void g1_4f91(void)
{
    register int i;
    struct g1_4f91_record far *p;

    for (i = 0; i < d_05aa; ++i) {
        p = &d_b6bc_[i];
        if (g1_326e(p->x, p->y) == 0 && p->marker == 0)
            p->marker = 1;
        if (p->state == 0 || p->marker == 0)
            continue;

        while (1) {
            if (g1_3558(p->x + 1, p->y - 128) != 0 ||
                g1_3558(p->x + 1, p->y) != 0)
                ++d_5081_[i];
            if (d_5081_[i] == 3) {
                g1_314c(p->x + 1, p->y - 256);
                g1_314c(p->x, p->y - 128);
                g1_314c(p->x + 2, p->y);
                g1_2b86(1, p->x + 1, p->y - 128);
                g1_2b86(1, p->x + 2, p->y - 64);
                g1_2b86(1, p->x + 2, p->y - 128);
                g1_2b86(1, p->x + 1, p->y);
                if (d_0437 == 0)
                    g1_2fe7(p->x, p->y);
                g1_0b85(2000L);
                p->state = 0;
                break;
            }

            if (d_5081_[i] == 1 && d_0437 == 0)
                g1_2e64(p->x, p->y - 192);
            if (d_5081_[i] == 2 && d_0437 == 0) {
                g1_2e64(p->x + 2, p->y - 192);
                g1_2e64(p->x, p->y - 192);
            }

            if (p->state < 25) {
                if (g1_3714(p->x + 1, p->y + 128) == 0) {
                    if (p->x > d_0099 + d_009d - 3)
                        g1_4d42(2, p->x, p->y);
                    else
                        g1_4d42(5, p->x, p->y);
                    p->y += 128;
                    break;
                }

                if (p->x > d_0099 + d_009d - 3) {
                    p->marker = 1;
                    if (p->state != 12)
                        g1_4d42(0, p->x, p->y);
                } else {
                    if (p->state != 12)
                        g1_4d42(3, p->x, p->y);
                    p->marker = 2;
                }
                ++p->state;
                p->y = (p->y >> 7) << 7;
                if (p->state == 13) {
                    if (p->marker == 1) {
                        g1_1b8a(1, p->x - 1, p->y - 80);
                        g1_4d42(1, p->x, p->y);
                    }
                    if (p->marker == 2) {
                        g1_1b8a(2, p->x + 3, p->y - 80);
                        g1_4d42(4, p->x, p->y);
                    }
                    ++p->state;
                }
                break;
            }

            if (p->state < 50) {
                if (p->marker == 1) {
                    if (g1_3714(p->x + 1, p->y - 256) != 0) {
                        p->y = (p->y >> 7) << 7;
                        g1_4d42(2, p->x, p->y);
                        p->state = 1;
                        break;
                    }
                    if (g1_367e(p->x - 1, p->y) == 0) {
                        p->x -= d_0698[p->state - 25];
                        p->y -= d_0698[p->state - 24];
                    } else {
                        p->y -= d_0698[p->state - 24];
                    }
                    g1_4d42(2, p->x, p->y);
                    p->state += 2;
                    break;
                }
                if (p->marker == 2) {
                    if (g1_3714(p->x + 1, p->y - 256) != 0) {
                        p->y = (p->y >> 7) << 7;
                        g1_4d42(5, p->x, p->y);
                        p->state = 1;
                        break;
                    }
                    if (g1_367e(p->x + 4, p->y) == 0) {
                        p->x += d_0698[p->state - 25];
                        p->y -= d_0698[p->state - 24];
                    } else {
                        p->y -= d_0698[p->state - 24];
                    }
                    g1_4d42(5, p->x, p->y);
                    p->state += 2;
                    break;
                }
            }

            p->state = 1;
        }
    }
}
