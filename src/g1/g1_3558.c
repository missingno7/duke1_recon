struct g1_3558_record { int state, value1, value2, value3; };
extern struct g1_3558_record d_cb6d[];
extern int d_c295;
extern int abs(int);
/*@body*/
char pascal g1_3558(int a0, register int a1)
{
    register int i;
    struct g1_3558_record far *p;

    for (i = 0; i < d_c295; i++) {
        p = &d_cb6d[i];
        if (p->state != 0) {
            if (abs(p->value1 - a0) < 2 &&
                p->value2 - a1 < 128 &&
                p->value2 - a1 >= -128) {
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
