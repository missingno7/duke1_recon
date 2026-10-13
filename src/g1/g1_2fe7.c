struct t_551e { int state, value1, value2; };
extern struct t_551e d_551e_[];
extern int d_051a;
/*@body*/
void pascal g1_2fe7(register int a0, int a1)
{
    register int i;
    struct t_551e far *p;

    for (i = 0; i < d_051a; i++) {
        p = &d_551e_[i];
        if (p->state == 0) {
            p->state = 1;
            p->value1 = a0;
            p->value2 = a1;
            break;
        }
    }
}
