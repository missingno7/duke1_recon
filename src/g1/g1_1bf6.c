/* goto kept: success_update and clear_record are shared targets reached from both state
   branches; the structured forms tried by the worker emitted different sizes. */
struct t_52dd { int used, x, y, marker; };
extern struct t_52dd d_52dd_[];
extern int d_0099;
extern int d_009d;
extern int d_009f;
extern int d_051c;
extern int d_0648;
extern char d_6379_;
extern char far *d_a0fb_;
extern char d_d4bf_;
int g1_3513(int a0, int a1);
int g1_367e(int a0, int a1);
char pascal g1_326e(int a0, int a1);
void asm_0424(char far *a0, int a1, int a2);
unsigned char g1_12ce(void) { return 0; }
char g1_1247(void) { return 0; }
/*@body*/
void g1_1bf6(void)
{
    register int i;
    struct t_52dd far *p;

    d_0648 += 0xa0;
    if (d_0648 == 0x140)
        d_0648 = 0;

    for (i = 0; i < d_051c; ++i) {
        p = &d_52dd_[i];
        if (p->used == 0)
            continue;

        if (p->used == 1) {
            if (g1_3513(p->x, p->y)) {
                if (d_6379_ != 0)
                    goto success_update;
                if (d_d4bf_ != 0)
                    goto success_update;
                if (g1_1247() == 0)
                    goto success_update;
                --d_0099;
                goto success_update;
            } else {
                --p->x;
                if (g1_367e(p->x, p->y) != 0)
                    goto clear_record;
                if (g1_367e(p->x, p->y + 0x40) != 0)
                    goto clear_record;
                if (g1_326e(p->x, p->y) == 0) {
                    if (p->marker != 0) {
                        p->marker = 0;
                        asm_0424(d_a0fb_ + 0x1e00,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x13);
                    } else {
                        asm_0424(d_a0fb_ + d_0648 + 0x1860,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x13);
                    }
                } else {
                    p->used = 0;
                }
            }
        }

        if (p->used == 2) {
            if (g1_3513(p->x, p->y)) {
                if (d_6379_ == 0 && d_d4bf_ == 0 && g1_12ce())
                    ++d_0099;
success_update:
                p->used = 0;
                d_6379_ = 1;
            } else {
                ++p->x;
                if (g1_367e(p->x + 1, p->y) != 0)
                    goto clear_record;
                if (g1_367e(p->x + 1, p->y + 0x40) != 0)
                    goto clear_record;
                if (g1_326e(p->x, p->y) != 0)
                    goto clear_record;
                if (p->marker != 0) {
                    p->marker = 0;
                    asm_0424(d_a0fb_ + 0x1ea0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
                } else {
                    asm_0424(d_a0fb_ + d_0648 + 0x19a0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
                }
            }
        }
        goto loop_continue;
clear_record:
        p->used = 0;
loop_continue:
        ;
    }
}
