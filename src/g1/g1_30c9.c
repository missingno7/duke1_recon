struct t_551e { int state, value1, value2; };
extern struct t_551e d_551e_[];
extern int d_0412[];
extern int d_051a;
void pascal g1_3034(int a0, int a1, int a2) {}
/*@body*/
void g1_30c9(void)
{
    register int i;
    struct t_551e far *p;

    for (i = 0; i < d_051a; i++) {
        p = &d_551e_[i];
        if (p->state != 0) {
            p->state++;
            p->value2 += d_0412[p->state - 2];
            if (p->state < 16) {
                g1_3034((p->state - 2) / 3, p->value1, p->value2);
            }
            if (p->state == 18)
                p->state = 0;
        }
    }
}
