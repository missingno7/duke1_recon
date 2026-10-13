struct g1_314c_record { int f[15]; };
extern struct g1_314c_record d_5320[];
extern int d_043e;
extern int d_064c;
void pascal g1_0042(int a0) {}
/*@body*/
void pascal g1_314c(int a0, int a1)
{
    register int i;
    struct g1_314c_record far *p;

    d_064c++;
    if (d_064c > 3)
        d_064c = 0;
    for (i = 0; i < d_043e; i++) {
        p = &d_5320[i];
        if (p->f[0] == 0) {
            p->f[0] = 1;
            p->f[1] = a0;
            p->f[2] = a1;
            p->f[3] = a0 + 1;
            p->f[4] = a1;
            p->f[5] = a0;
            p->f[6] = a1 + 8;
            p->f[7] = a0 + 1;
            p->f[8] = a1 + 8;
            switch (d_064c) {
            case 0:
                p->f[9] = 0xa0;
                p->f[10] = 0x140;
                p->f[11] = 0x1e0;
                p->f[12] = 0x280;
                break;
            case 1:
                p->f[9] = 0x280;
                p->f[10] = 0xa0;
                p->f[11] = 0x140;
                p->f[12] = 0x1e0;
                break;
            case 2:
                p->f[9] = 0x140;
                p->f[10] = 0x280;
                p->f[11] = 0x1e0;
                p->f[12] = 0xa0;
                break;
            case 3:
                p->f[9] = 0x1e0;
                p->f[10] = 0x280;
                p->f[11] = 0x140;
                p->f[12] = 0xa0;
                break;
            }
            g1_0042(10);
            return;
        }
    }
}
