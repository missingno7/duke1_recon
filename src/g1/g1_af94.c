struct g1_af94_record { int state, x, y; };
extern struct g1_af94_record d_a680_[];
extern int d_0437;
extern int d_05fe;
extern int d_0700;
extern char d_6379_;
int g1_3714(int a0, int a1) { return 0; }
int g1_367e(int a0, int a1) { return 0; }
void pascal g1_af06(int a0, int a1, int a2) {}
char pascal g1_3558(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void g1_af94(void)
{
    register int i;
    struct g1_af94_record far *p;

    if (d_0437 == 0 || d_0437 == 0x40)
        ++d_0700;
    if (d_0700 == 3)
        d_0700 = 0;

    for (i = 0; i < d_05fe; ++i) {
        p = &d_a680_[i];
        if (p->state != 0) {
            if (g1_3714(p->x, p->y + 0x80) == 0)
                p->y += 0x40;
            if (g1_367e(p->x - 1, p->y) != 0 ||
                g1_3714(p->x - 2, p->y + 0x80) == 0)
                p->state = 2;
            if (g1_367e(p->x + 2, p->y) != 0 ||
                g1_3714(p->x + 2, p->y + 0x80) == 0)
                p->state = 1;

            if (p->state == 1) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    --p->x;
                g1_af06(d_0700, p->x, p->y);
            }
            if (p->state == 2) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    ++p->x;
                g1_af06(d_0700 + 3, p->x, p->y);
            }
            g1_3558(p->x, p->y);
            if (g1_3513(p->x, p->y) != 0)
                d_6379_ = 1;
        }
    }
}




