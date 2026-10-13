struct t_cb6d { int state, x, y, marker; };
extern struct t_cb6d d_cb6d_[];
extern int d_c295_;
void pascal g1_0042(int a0) {}
/*@body*/
void pascal g1_18d4(register int a0, int a1, int a2)
{
    register int i;
    struct t_cb6d far *p;

    for (i = 0; i < d_c295_; ++i) {
        p = &d_cb6d_[i];
        if (p->state == 0) {
            g1_0042(6);
            p->marker = 1;
            p->state = a2 + 1;
            p->x = a0;
            p->y = a1;
            return;
        }
    }
}
