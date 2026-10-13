extern char d_6e0a_;
extern char d_9682_;
extern int d_9b38_;
void asm_05eb(int a0);
void asm_0424(char far* a0, int a1, int a2);
/*@body*/
void pascal g2_1ffa(char far* bitmap)
{
    asm_05eb(d_6e0a_);
    asm_0424(bitmap, d_9682_ + 0x1e, d_9b38_ + 0xa0);
    asm_05eb(!d_6e0a_);
    asm_0424(bitmap, d_9682_ + 0x1e, d_9b38_ + 0xa0);
    d_9682_ += 2;
}
