struct t_cb6d { int state, x, y, marker; };
extern struct t_cb6d d_cb6d_[];
extern int d_c295_;
extern int abs(int);
/*@body*/
char pascal g1_3558(int a0, register int a1)
{
    register int i;
    struct t_cb6d far *p;

    for (i = 0; i < d_c295_; i++) {
        p = &d_cb6d_[i];
        if (p->state != 0) {
            if (abs(p->x - a0) < 2 &&
                p->y - a1 < 128 &&
                p->y - a1 >= -128) {
                if (p->state == 1) {
                    p->state = 0;
                    return 1;
                }
                if (p->state == 5) {
                    p->state = 0;
                    return 2;
                }
                p->state = 0;
            }
        }
    }
    return 0;
}
