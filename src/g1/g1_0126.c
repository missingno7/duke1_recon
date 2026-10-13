extern char d_554c;
extern char d_a0fa;
void pascal g2_12ad(int a0);
/*@body*/
unsigned char pascal g1_0126(int a0)
{
    g2_12ad(a0);
    if (d_a0fa >= 2 && d_a0fa <= 10) {
        d_554c = d_a0fa + 0x2f;
        return 1;
    }
    return 0;
}