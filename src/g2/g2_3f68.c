extern int d_039f;
extern int d_0b9f;
extern unsigned char d_0ce1[];
extern unsigned char d_0d04[];
extern int d_5305_;
void pascal g2_385b(char a0, int a1, int a2) {}
/*@body*/
void g2_3f68(void)
{
    register int i;

    if (d_0b9f < 0x28)
        ++d_0b9f;
    if (d_0b9f == 0x28) {
        d_5305_ += 2;
        if (d_5305_ % 26 == 0)
            d_0b9f = 0;
        if (d_5305_ > 0x1ee)
            d_5305_ = 0;
    }
    ++d_039f;
    if (d_039f == 4)
        d_039f = 0;
    for (i = 0; i < 26; ++i)
        g2_385b(*(int near *)&d_0d04[d_5305_ + i], i + 2,
                d_0ce1[d_039f + i] + 0xa2);
}
