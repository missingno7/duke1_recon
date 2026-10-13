struct g1_43fa_record { int state, x, y; };
extern struct g1_43fa_record d_772e_[];
extern int d_009d;
extern int d_009f;
extern int d_0540;
extern char d_6379_;
extern char far *d_a0fb_;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void g1_43fa(void)
{
    register int i;
    struct g1_43fa_record far *p;

    for (i = 0; i < d_0540; ++i) {
        p = &d_772e_[i];
        if (p->state == 0)
            continue;
        ++p->state;
        if (p->state >= 0x0f) {
            if (p->state == 0x0f && g1_326e(p->x, p->y) == 0)
                g1_0042(0x2b);
            if (p->state < 0x19) {
                if ((p->state % 2) == 0)
                    continue;
                if (g1_326e(p->x, p->y) != 0)
                    continue;
                asm_0424(d_a0fb_ + 0x0f00,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                continue;
            }
            if (p->state < 0x2d) {
                if (g1_326e(p->x, p->y) != 0)
                    continue;
                if (g1_326e(p->x + 6, p->y) != 0)
                    continue;
                asm_0424(d_a0fb_ + ((p->state % 2) * 0xa0) + 0xfa0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                asm_0424(d_a0fb_ + ((p->state % 2) * 0xa0) + 0xfa0,
                         p->x - d_009d + 2,
                         ((p->y - d_009f) >> 3) + 0x10);
                asm_0424(d_a0fb_ + ((p->state % 2) * 0xa0) + 0x10e0,
                         p->x - d_009d + 4,
                         ((p->y - d_009f) >> 3) + 0x10);
                if (g1_3513(p->x, p->y) != 0) {
                    d_6379_ = 1;
                    continue;
                }
                if (g1_3513(p->x + 2, p->y - 0x20) != 0) {
                    d_6379_ = 1;
                    continue;
                }
                if (g1_3513(p->x + 4, p->y) == 0)
                    continue;
                d_6379_ = 1;
            } else if (p->state > 0x41) {
                p->state = 1;
            }
        }
    }
}