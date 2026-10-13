struct g1_2e64_record { int used, value1, value2; };
extern struct g1_2e64_record d_d1cf[];
extern int d_0520;
/*@body*/
void pascal g1_2e64(register int a0, int a1)
{
    register int i;
    struct g1_2e64_record far *p;

    for (i = 0; i < d_0520; i++) {
        p = &d_d1cf[i];
        if (p->used == 0) {
            p->used = 1;
            p->value1 = a0;
            p->value2 = a1;
            break;
        }
    }
}
