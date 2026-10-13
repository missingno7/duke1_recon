extern char d_554f_;
extern char d_5550_;
extern char d_5551_;
extern char d_5552_;
extern char d_6e0a_;
extern char far *d_a0fb_;
void asm_05eb(int a0);
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void pascal g1_bb9f(void)
{
    register int si;
    register int di;

    si = d_6e0a_;
    di = 0;
    do {
        ++di;
        asm_05eb(si);
        if (d_554f_ != 0)
            asm_0424(d_a0fb_ + 0x4d80, 0x1e, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x1e, 0x90);
        if (d_5550_ != 0)
            asm_0424(d_a0fb_ + 0x4e20, 0x20, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x20, 0x90);
        if (d_5551_ != 0)
            asm_0424(d_a0fb_ + 0x4ec0, 0x22, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x22, 0x90);
        if (d_5552_ != 0)
            asm_0424(d_a0fb_ + 0x4f60, 0x24, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x24, 0x90);
        si = !si;
    } while (di == 1);
}
