struct g1_1b51_record { int used, arg0, arg1, marker; };
extern struct g1_1b51_record d_52dd[];
extern int d_051c;
/*@body*/
void pascal g1_1b51(void)
{
    register int i;

    for (i = 0; i < d_051c; i++) {
        d_52dd[i].used = 0;
        d_52dd[i].marker = 0;
    }
}
