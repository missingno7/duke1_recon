struct g1_2fe7_record { int used, value1, value2; };
extern struct g1_2fe7_record d_551e[];
extern int d_051a;
/*@body*/
void pascal g1_2fe7(register int a0, int a1)
{
    register int i;
    struct g1_2fe7_record far *p;

    for (i = 0; i < d_051a; i++) {
        p = &d_551e[i];
        if (p->used == 0) {
            p->used = 1;
            p->value1 = a0;
            p->value2 = a1;
            break;
        }
    }
}
