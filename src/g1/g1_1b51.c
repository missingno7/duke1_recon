struct t_52dd { int used, x, y, marker; };
extern struct t_52dd d_52dd_[];
extern int d_051c;
/*@body*/
void pascal g1_1b51(void)
{
    register int i;

    for (i = 0; i < d_051c; i++) {
        d_52dd_[i].used = 0;
        d_52dd_[i].marker = 0;
    }
}
