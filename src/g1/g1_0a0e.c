extern int d_03a1;
extern int d_4ed4_;
extern char d_6e0a_;
extern char far *d_a0fb_;
void asm_05eb(int a0);
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void g1_0a0e(void)
{
    register int i;
    for (i = 0; i < 8; ++i) {
        asm_05eb(d_6e0a_);
        asm_0424(d_a0fb_ + 0x26c0, i + 0x1e, 0x3c);
        if (d_4ed4_ - 1 > i)
            asm_0424(d_a0fb_ + 0x2620, i + 0x1e, 0x3c);
        asm_05eb(!d_6e0a_);
        asm_0424(d_a0fb_ + 0x26c0, i + 0x1e, 0x3c);
        if (d_4ed4_ - 1 > i)
            asm_0424(d_a0fb_ + 0x2620, i + 0x1e, 0x3c);
        d_03a1 = 0;
    }
}
