extern int d_5000;
extern int d_5316;
extern unsigned int far *d_7729;
extern int d_d574;
extern int d_d577;
void pascal g1_2b86(register int a0, int a1, int a2) {}
/*@body*/
void g1_a6f4(void)
{
    if (d_5316 == 0) return;
    if (d_5000 == 0) return;
    g1_2b86(3, d_d574 + 2, d_d577);
    if (*(d_7729 + d_d577 + (d_d574 >> 1)) == 0x2fe0U) {
        d_5316 = 0;
        d_5000 = 0;
    } else {
        *(d_7729 + d_d577 + (d_d574 >> 1)) = 0x2fe0U;
    }
    d_d574 += 2;
}



