extern char d_6e0a;
extern char far *d_a0fb;
extern int d_c295;
void asm_05eb(int page);
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_0adc(void)
{
    register int si;

    for (si = 0; si < d_c295; si++) {
        asm_05eb(d_6e0a);
        asm_0424(d_a0fb + 0x1ae0, 0x21, 0x60);
        asm_0424(d_a0fb + 0x500, si * 2 + 0x1e, 0x6c);
        asm_05eb(!d_6e0a);
        asm_0424(d_a0fb + 0x1ae0, 0x21, 0x60);
        asm_0424(d_a0fb + 0x500, si * 2 + 0x1e, 0x6c);
    }
}