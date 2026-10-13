struct t_b63c { int state, x, y, kind; };
extern struct t_b63c d_b63c_[];
extern int d_0522;
/*@body*/
void pascal g1_2b86(register int a0, int a1, int a2)
{
    register int i;
    struct t_b63c far *p;

    for (i = 0; i < d_0522; i++) {
        p = &d_b63c_[i];
        if (p->state == 0) {
            p->state = 1;
            p->x = a1;
            p->y = a2;
            p->kind = a0;
            break;
        }
    }
}
