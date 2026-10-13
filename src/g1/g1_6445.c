struct g1_6445_record {
    int state;
    int x;
    int y;
    int kind;
    int flag8;
    int flag10;
};
extern struct g1_6445_record d_555d[];
extern int d_009d;
extern int d_009f;
extern int d_05b8;
extern char far *d_637a;
extern char far *d_a0fb;
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
char pascal g1_326e(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
int g1_367e(int a0, int a1) { return 0; }
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void g1_6445(void)
{
    register int i;
    struct g1_6445_record far *p;

    for (i = 0; i < d_05b8; ++i) {
        p = &d_555d[i];
        if (p->state != 0) {
            if (g1_3714(p->x, p->y + 0x80) == 0)
                p->y += 0x80;

            if (p->kind == 0) {
                if (g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    p->kind = 1;
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(0x1f4L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                }
            }

            if (p->kind == 0) {
                if (g1_326e(p->x, p->y) == 0 && p->state < 0x0c) {
                    asm_0424(d_a0fb,
                            p->x - d_009d,
                            ((p->y - d_009f) >> 3) + 0x10);
                    continue;
                }
            }

            if (p->kind == 0) {
                continue;
            }

                ++p->state;
                if (g1_326e(p->x, p->y) == 0) {
                    if (p->state < 0x0c) {
                        asm_0424(d_637a + 0x4600,
                                p->x - d_009d,
                                ((p->y - d_009f) >> 3) + 0x10);
                    }
                    if (p->state % 2 != 0 && p->state < 0x0c) {
                        asm_0424(d_637a + 0x46a0,
                                p->x - d_009d,
                                ((p->y - d_009f) >> 3) + 0x10);
                    }
                }

                if (p->state <= 0x0c)
                    continue;

                if (p->state == 0x0e) {
                    g1_2b86(2, p->x, p->y);
                    g1_0042(0x21);
                }
                else if (p->state == 0x11) {
                    if (g1_367e(p->x - 2, p->y) == 0 &&
                        g1_367e(p->x - 2, p->y + 0x80) != 0) {
                        g1_2b86(2, p->x - 2, p->y);
                    } else {
                        p->flag8 = 0;
                    }
                    if (g1_367e(p->x + 2, p->y) == 0 &&
                        g1_367e(p->x + 2, p->y + 0x80) != 0) {
                        g1_2b86(2, p->x + 2, p->y);
                    } else {
                        p->flag10 = 0;
                    }
                } else if (p->state == 0x13) {
                    if (p->flag8 != 0) {
                        if (g1_367e(p->x - 4, p->y) == 0 &&
                            g1_367e(p->x - 4, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x - 4, p->y);
                        } else {
                            p->flag8 = 0;
                        }
                    }
                    if (p->flag10 != 0) {
                        if (g1_367e(p->x + 4, p->y) == 0 &&
                            g1_367e(p->x + 4, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x + 4, p->y);
                        } else {
                            p->flag10 = 0;
                        }
                    }
                } else if (p->state == 0x15) {
                    if (p->flag8 != 0) {
                        if (g1_367e(p->x - 6, p->y) == 0 &&
                            g1_367e(p->x - 6, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x - 6, p->y);
                        } else {
                            p->flag8 = 0;
                        }
                    }
                    if (p->flag10 != 0) {
                        if (g1_367e(p->x + 6, p->y) == 0 &&
                            g1_367e(p->x + 6, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x + 6, p->y);
                        } else {
                            p->flag10 = 0;
                        }
                    }
                } else if (p->state == 0x17) {
                    if (p->flag8 != 0 &&
                        g1_367e(p->x - 8, p->y) == 0 &&
                        g1_367e(p->x - 8, p->y + 0x80) != 0)
                        g1_2b86(2, p->x - 8, p->y);
                    if (p->flag10 != 0 &&
                        g1_367e(p->x + 8, p->y) == 0 &&
                        g1_367e(p->x + 8, p->y + 0x80) != 0)
                        g1_2b86(2, p->x + 8, p->y);
                }

                if (p->state == 0x18)
                    p->state = 0;
        }
    }
}
