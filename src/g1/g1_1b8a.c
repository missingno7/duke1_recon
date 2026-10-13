struct t_52dd { int used, x, y, marker; };
extern struct t_52dd d_52dd[];
extern int d_051c;
char pascal g1_326e(int a0, int a1);
void pascal g1_0042(int a0) {}
/*@body*/
void pascal g1_1b8a(register int a0, int a1, int a2)
{
    register int i;
    struct t_52dd far *p;
    for (i = 0; i < d_051c; ++i) {
        p = &d_52dd[i];
        if (p->used == 0) {
            p->used = a0;
            p->x = a1;
            p->y = a2;
            p->marker = 1;
            if (g1_326e(p->x, p->y) == 0)
                g1_0042(11);
            return;
        }
    }
}
