struct s8 { int a, b, c, d; };
extern struct s8 d_d4c3_[];
extern int d_0518;
/*@body*/
void pascal g1_2a40(register int a0, int a1, int a2)
{
    register int i;
    struct s8 far *p;

    for (i = 0; i < d_0518; i++) {
        p = &d_d4c3_[i];
        if (p->a == 0) {
            p->a = 1;
            p->b = a1;
            p->c = a2;
            p->d = a0;
            break;
        }
    }
}
