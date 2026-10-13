struct g1_a30a_record { int used; int x; int y; };
extern struct g1_a30a_record d_5c6c_[];
extern int d_009d;
extern int d_009f;
extern int d_5004_;
extern char d_6379_;
extern char far *d_637a_;
char pascal g1_326e(int a0, int a1) {}
int g1_3714(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
void asm_0424(char far *bitmap, int x, int y);
/*@body*/
void g1_a30a(void)
{
    register int i;
    struct g1_a30a_record far *p;

    i = 0;
    while (i < d_5004_) {
        p = &d_5c6c_[i];
        if (p->used != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x40;
                if (g1_3513(p->x, p->y) != 0) {
                    p->used = 0;
                    d_6379_ = 1;
                    g1_2b86(2, p->x, p->y);
                    g1_0042(0x21);
                }
                asm_0424(d_637a_ + 0x8b60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
        }
        ++i;
    }
}
