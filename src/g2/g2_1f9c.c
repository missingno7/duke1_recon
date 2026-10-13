extern char d_6e0a_;
extern int d_9b38_;
extern char far *d_a0fb_;
void asm_05eb(int a0);
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void g2_1f9c(void)
{
    asm_05eb(d_6e0a_);
    asm_0424(d_a0fb_ + 0x2800, 0x24, d_9b38_ + 0xa0);
    asm_05eb(!d_6e0a_);
    asm_0424(d_a0fb_ + 0x2800, 0x24, d_9b38_ + 0xa0);
}