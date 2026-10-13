extern char d_554c_;
extern char d_a0fa_;
void pascal g2_12ad(int a0);
/*@body*/
unsigned char pascal g1_0126(int a0)
{
    g2_12ad(a0);
    if (d_a0fa_ >= 2 && d_a0fa_ <= 10) {
        d_554c_ = d_a0fa_ + 0x2f;
        return 1;
    }
    return 0;
}