extern char far *d_6b54;
void outport(int port, int value);
void asm_04c5(char far *a0, int a1, int a2);
/*@body*/
void pascal g2_37b6(char far *text, register int x, int y)
{
    register int i;

    i = 0;
    outport(0x3ce, 5);
    for (; text[i] != 0; ++i) {
        if (text[i] >= 'a') {
            asm_04c5(d_6b54 + (text[i] - 'a') * 40 + 0xac8,
                     x + i, y * 8);
        } else {
            asm_04c5(d_6b54 + (text[i] - ' ') * 40 + 0x190,
                     x + i, y * 8);
        }
    }
}
