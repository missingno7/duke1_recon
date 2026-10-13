struct g1_c1b2_record {
    int kind;
    int x;
    int y;
};
extern struct g1_c1b2_record d_cc84_[];
extern int d_009d;
extern int d_009f;
extern int d_531e_;
extern char d_6379_;
extern char far *d_a0fb_;
void asm_0424(char far *bitmap, int x, int y);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void g1_c1b2(void)
{
    register int i;
    struct g1_c1b2_record far *p;

    i = 0;
    while (i < d_531e_) {
        p = &d_cc84_[i];
        if (g1_326e(p->x, p->y) == 0) {
            if (g1_3513(p->x, p->y) != 0)
                d_6379_ = 1;
            asm_0424(d_a0fb_ + p->kind,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 16);
        }
        ++i;
    }
}
