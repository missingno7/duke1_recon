struct g1_18d4_record { int state, value1, value2, marker; };
extern struct g1_18d4_record d_cb6d[];
extern int d_c295;
void pascal g1_0042(int a0) {}
/*@body*/
void pascal g1_18d4(register int a0, int a1, int a2)
{
    register int i;
    struct g1_18d4_record far *p;

    for (i = 0; i < d_c295; ++i) {
        p = &d_cb6d[i];
        if (p->state == 0) {
            g1_0042(6);
            p->marker = 1;
            p->state = a2 + 1;
            p->value1 = a0;
            p->value2 = a1;
            return;
        }
    }
}
