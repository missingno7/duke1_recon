struct g1_aac2_record { int state, x, y, kind; };
extern struct g1_aac2_record d_73fb_[];
extern int d_0437;
extern int d_0600;
extern int d_5312_;
extern char d_6379_;
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_aa1b(int a0, int a1, int a2) {}
char pascal g1_3558(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
int g1_367e(int a0, int a1) { return 0; }
void pascal g1_2a40(int a0, int a1, int a2) {}
/*@body*/
void g1_aac2(void)
{
    register int i;
    struct g1_aac2_record far *p;

    d_5312_ = 1;
    for (i = 0; i < d_0600; ++i) {
        p = &d_73fb_[i];
        if (p->state == 0)
            continue;

        d_5312_ = 0;
        if (p->state > 2) {
            switch (p->kind) {
            case 0:
                g1_aa1b(0, p->x, p->y);
                break;
            case 1:
                g1_aa1b(6, p->x, p->y);
                break;
            case 2:
                g1_aa1b(3, p->x, p->y);
                break;
            case 3:
                g1_aa1b(7, p->x, p->y);
                break;
            }
            ++p->state;
            ++p->kind;
            if (p->kind == 4)
                p->kind = 0;
            if (p->state == 0x14) {
                p->state = 0;
                g1_2e64(p->x, p->y);
                g1_2e64(p->x, p->y - 0x80);
                g1_2e64(p->x - 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0xc0);
                g1_2e64(p->x - 1, p->y);
                g1_0b85(5000L);
                g1_2a40(0x640, p->x, p->y);
                continue;
            }
        } else {
            if (!g1_3714(p->x, p->y + 0x80)) {
                p->y += 0x40;
            } else {
                if (g1_367e(p->x - 1, p->y) && p->state == 1) {
                    p->state = 2;
                    p->kind = 0;
                } else if (g1_367e(p->x + 2, p->y) && p->state == 2) {
                    p->state = 1;
                    p->kind = 0;
                }
            }

            if (p->kind == 0) {
                if (p->state == 1)
                    g1_aa1b(6, p->x, p->y);
                if (p->state == 2)
                    g1_aa1b(7, p->x, p->y);
                if (d_0437 != 0x40 && d_0437 != 0)
                    continue;
                p->kind = 1;
                continue;
            }

            if (p->state == 1) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    --p->x;
                if (p->kind < 3)
                    g1_aa1b(p->kind, p->x, p->y);
                else
                    g1_aa1b(5 - p->kind, p->x, p->y);
                if (d_0437 == 0 || d_0437 == 0x40) {
                    if (g1_3714(p->x, p->y + 0x80))
                        ++p->kind;
                    if (p->kind == 6)
                        p->kind = 1;
                }
            }

            if (p->state == 2) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    ++p->x;
                if (p->kind < 3)
                    g1_aa1b(p->kind + 2, p->x, p->y);
                else
                    g1_aa1b(8 - p->kind, p->x, p->y);
                if (d_0437 == 0 || d_0437 == 0x40) {
                    if (g1_3714(p->x, p->y + 0x80))
                        ++p->kind;
                    if (p->kind == 6)
                        p->kind = 1;
                }
            }

            if (g1_3558(p->x, p->y)) {
                p->state = 0;
                g1_2e64(p->x, p->y);
                g1_2e64(p->x, p->y - 0x80);
                g1_2e64(p->x - 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0xc0);
                g1_2e64(p->x - 1, p->y);
                g1_0042(0x12);
                g1_0b85(200L);
                continue;
            }
            if (g1_3513(p->x, p->y)) {
                d_6379_ = 1;
                g1_0042(0x23);
                p->state = 3;
                p->kind = 0;
            }
        }
    }
}
