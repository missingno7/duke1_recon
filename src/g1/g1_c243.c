extern long d_514b[];
extern int d_554d;
/*@body*/
void pascal g1_c243(long key)
{
    register int i;

    for (i = 0; i < d_554d; ++i) {
        if (d_514b[i] == key)
            return;
    }
    d_514b[i] = key;
    ++d_554d;
}
