/* goto kept: the used == 1 path jumps BACK into the first branch's draw; -O tail merging
   only produces forward jumps into the later copy (rule TAIL-MERGE), and the structured
   form (receipt-structured-final.json) differs in 157 bytes. */
struct g1_3882_record { int used, x, y; };
extern struct g1_3882_record d_a8da_[];
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern char d_0439;
extern int d_0524;
extern char d_0644;
extern char d_555b_;
extern unsigned int far *d_7729_;
extern char far *d_a0fb_;
extern char d_c68c_;
extern char d_d134_;
extern int d_d646_[];
void asm_0424(char far *a0, int a1, int a2);
void g2_0fc1(void);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_363b(int a0, int a1) { return 0; }
char g1_1352(void) { return 0; }
void pascal g1_0042(int a0) {}
/*@body*/
void g1_3882(void)
{
    register int si;
    struct g1_3882_record far *p;

    for (si = 0; si < d_0524; ++si) {
        p = &d_a8da_[si];
        if (g1_326e(p->x, p->y) == 0) {
            if (g1_363b(p->x, p->y - 0x20)) {
                if (d_555b_) {
                    d_555b_ = 0;
                    g2_0fc1();
                }
                if (!d_0439) {
                    if (d_c68c_) {
                        if (g1_1352()) {
                            if (!d_d134_) {
                                ++p->used;
                                p->y -= 0x80;
                                *((d_7729_ + p->y) + (p->x >> 1) - 1) = 0x1ae0;
                                d_009b -= 0x10;
                                g1_0042(0x14);
                                if (d_009b <= 0x40)
                                    d_0644 = 1;
                                d_0439 = 0;
                                asm_0424(d_a0fb_ + 0x320,
                                         p->x - d_009d,
                                         ((p->y - d_009f) >> 3) + 0x10);
                            }
                        }
                    }
                }
draw_second:
                asm_0424(d_a0fb_ + 0x320,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            } else if (p->used > 1) {
                --p->used;
                *((d_7729_ + p->y) + (p->x >> 1) - 1) = d_d646_[si];
                p->y += 0x80;
                asm_0424(d_a0fb_ + 0x320,
                         p->x - d_009d,
                         (p->y - d_009f) >> 3);
                continue;
            } else if (p->used == 1) {
                goto draw_second;
            } else {
                continue;
            }
        } else if (p->used > 1) {
            p->used--;
            *((d_7729_ + p->y) + (p->x >> 1) - 1) = d_d646_[si];
            p->y += 0x80;
        }
    }
}