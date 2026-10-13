extern char d_6e0a;
extern int d_9b38;
extern char far *d_a0fb;
void asm_05eb(int a0);
void asm_0424(char far *a0, int a1, int a2);
/*@body*/
void g2_3b79(void)
{
    asm_05eb(d_6e0a);
    asm_0424(d_a0fb + 0x4c40, 0x24, d_9b38 + 0xa0);
    asm_05eb(!d_6e0a);
    asm_0424(d_a0fb + 0x4c40, 0x24, d_9b38 + 0xa0);
}
