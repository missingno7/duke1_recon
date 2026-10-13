struct g1_87bf_record { int state, x, y; };
extern struct g1_87bf_record d_68fc_[];
extern int d_0099;
extern int d_009d;
extern int d_009f;
extern int d_05d2;
extern int d_4ed6_;
extern char far *d_637a_;
char pascal g1_326e(int a0, int a1) { return 0; }
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0b85(long value) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
/*@body*/
void g1_87bf(void)
{
    register int i;
    struct g1_87bf_record far *p;

    d_4ed6_ = 1;
    for (i = 0; i < d_05d2; ++i) {
        p = &d_68fc_[i];
        if (p->state == 0)
            continue;

        d_4ed6_ = 0;
        if (g1_326e(p->x, p->y) != 0)
            continue;

        if (p->x - 2 > d_0099 + d_009d) {
            asm_0424(d_637a_ + 0x7d00,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else if (p->x + 2 < d_0099 + d_009d) {
            asm_0424(d_637a_ + 0x7e40,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_637a_ + 0x7da0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }

        if (g1_3558(p->x, p->y) != 0) {
            g1_2a40(0, p->x, p->y);
            g1_0b85(100L);
            g1_2b86(1, p->x, p->y);
            p->state = 0;
            g1_0042(0x12);
        }
    }
}


