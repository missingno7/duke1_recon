extern char d_a0fa_;
void pascal g2_1241(int a0);
void pascal g1_0151(char a0) {}
/*@body*/
char pascal g1_0351(int a0)
{
    g2_1241(a0);
    if (d_a0fa_ >= 2 && d_a0fa_ <= 10) {
        g1_0151(d_a0fa_ + 0x2f);
        return 1;
    }
    return 0;
}
