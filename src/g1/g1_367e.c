extern unsigned int far *d_7729;
extern char d_530f;
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_0042(int a0) {}
void pascal g1_0b85(long a0) {}
/*@body*/
int g1_367e(register int a0, register int a1, int a2)
{
    int far *p;

    p = d_7729 + (a0 >> 1) + ((a1 >> 7) << 7) - 1;
    if (d_530f != 0) {
        if (*p == 0x1800) {
            *p = 0x17e0;
            g1_2e64(a0, a1);
        } else if (p[128] == 0x1800) {
            p[128] = 0x17e0;
            g1_2e64(a0, a1 + 128);
        } else {
            goto check;
        }
        g1_0042(42);
        g1_0b85(10L);
        return 1;
    }
check:
    if (*p > 0x17ff)
        return 1;
    return 0;
}



