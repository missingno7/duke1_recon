extern char d_6e0a_;
extern char far *d_a0fb_;
extern int d_c295_;
void asm_05eb(int page);
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_0adc(void)
{
    register int si;

    for (si = 0; si < d_c295_; si++) {
        asm_05eb(d_6e0a_);
        asm_0424(d_a0fb_ + 0x1ae0, 0x21, 0x60);
        asm_0424(d_a0fb_ + 0x500, si * 2 + 0x1e, 0x6c);
        asm_05eb(!d_6e0a_);
        asm_0424(d_a0fb_ + 0x1ae0, 0x21, 0x60);
        asm_0424(d_a0fb_ + 0x500, si * 2 + 0x1e, 0x6c);
    }
}