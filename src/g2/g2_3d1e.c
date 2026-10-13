extern char d_a0fa_;
extern char d_d134_;
extern char d_d4c0_;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far* a0, int a1, int a2) {}
void pascal g2_2870(int a0, int a1) {}
/*@body*/
void pascal g2_3d1e(register int a0)
{
    g2_3d8c(a0, 5, 1);
    g2_37b6("Are you sure you want to", a0 + 1, 11);
    g2_37b6("         quit?          ", a0 + 1, 12);
    while (d_a0fa_ == 1) {
    }
    g2_2870(a0 + 0x10, 12);
    d_d4c0_ = 0;
    d_d134_ = 0;
    if (d_a0fa_ == 0x15)
        return 1;
    d_a0fa_ = 0;
    return 0;
}
