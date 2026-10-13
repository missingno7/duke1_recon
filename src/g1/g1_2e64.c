struct t_d1cf { int used, x, y; };
extern struct t_d1cf d_d1cf[];
extern int d_0520;
/*@body*/
void pascal g1_2e64(register int a0, int a1)
{
    register int i;
    struct t_d1cf far *p;

    for (i = 0; i < d_0520; i++) {
        p = &d_d1cf[i];
        if (p->used == 0) {
            p->used = 1;
            p->x = a0;
            p->y = a1;
            break;
        }
    }
}
