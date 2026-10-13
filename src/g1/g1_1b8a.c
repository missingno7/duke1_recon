struct g1_1b8a_record { int used; int arg0; int arg1; int marker; };
extern struct g1_1b8a_record d_52dd[];
extern int d_051c;
char pascal g1_326e(int a0, int a1);
void pascal g1_0042(int a0) {}
/*@body*/
void pascal g1_1b8a(register int a0, int a1, int a2)
{
    register int i;
    struct g1_1b8a_record far *p;
    for (i = 0; i < d_051c; ++i) {
        p = &d_52dd[i];
        if (p->used == 0) {
            p->used = a0;
            p->arg0 = a1;
            p->arg1 = a2;
            p->marker = 1;
            if (g1_326e(p->arg0, p->arg1) == 0)
                g1_0042(11);
            return;
        }
    }
}
