struct t_c8eb { int used, value1, value2; };
extern struct t_c8eb d_c8eb_[];
extern int d_051e;
/*@body*/
void pascal g1_29d0(register int a0, int a1)
{
    register int i;
    struct t_c8eb far *p;

    for (i = 0; i < d_051e; ++i) {
        p = &d_c8eb_[i];
        if (p->used == 0) {
            p->used = 1;
            p->value1 = a0;
            p->value2 = a1;
            break;
        }
    }
}