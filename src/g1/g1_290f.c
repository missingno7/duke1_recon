extern int d_009b;
extern int d_009f;
extern char d_0644;
extern int d_5002_;
/*@body*/
void g1_290f(void)
{
    if (d_5002_ == 0 && d_0644 != 0) {
        if (d_009b < 100 && d_009f > 0) {
            d_009f -= 128;
            d_009b += 16;
            if (d_009b >= 100)
                d_0644 = 0;
        } else if (d_009b > 112) {
            d_009f += 128;
            d_009b -= 16;
            if (d_009b <= 112)
                d_0644 = 0;
        }
    }
}
