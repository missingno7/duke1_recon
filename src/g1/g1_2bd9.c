struct t_b63c { int state, x, y, kind; };
extern struct t_b63c d_b63c_[];
extern int d_009d;
extern int d_009f;
extern int d_0522;
extern char d_6379_;
extern char far *d_637a_;
char pascal g1_326e(int a0, int a1);
void asm_0424(char far *bitmap, int a0, int a1);
int g1_3513(int a0, int a1);
/*@body*/
void g1_2bd9(void)
{
    register int i;
    struct t_b63c far *p;

    for (i = 0; i < d_0522; ++i) {
        p = &d_b63c_[i];
        if (p->state != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (p->kind == 3) {
                    ++p->state;
                    if (p->state == 2) {
                        asm_0424(d_637a_ + 0x8160,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x10);
                    }
                    if (p->state == 4) {
                        if (g1_326e(p->x - 1, p->y - 0x40) == 0)
                            asm_0424(d_637a_ + 0x8200,
                                     p->x - d_009d - 1,
                                     ((p->y - d_009f) >> 3) + 8);
                        if (g1_326e(p->x + 1, p->y - 0x40) == 0)
                            asm_0424(d_637a_ + 0x82a0,
                                     p->x - d_009d + 1,
                                     ((p->y - d_009f) >> 3) + 8);
                        if (g1_326e(p->x - 1, p->y + 0x40) == 0)
                            asm_0424(d_637a_ + 0x8340,
                                     p->x - d_009d - 1,
                                     ((p->y - d_009f) >> 3) + 0x18);
                        if (g1_326e(p->x + 1, p->y + 0x40) == 0)
                            asm_0424(d_637a_ + 0x83e0,
                                     p->x - d_009d + 1,
                                     ((p->y - d_009f) >> 3) + 0x18);
                        p->state = 0;
                    }
                } else {
                    if (p->kind == 1) {
                        asm_0424(d_637a_ + p->state * 0xa0 + 0x19a0,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x10);
                    } else {
                        if (g1_3513(p->x, p->y) != 0)
                            d_6379_ = 1;
                        asm_0424(d_637a_ + p->state * 0xa0 + 0x37a0,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x10);
                    }
                    ++p->state;
                    if (p->state == 7)
                        p->state = 0;
                }
            } else {
                p->state = 0;
            }
        }
    }
}



