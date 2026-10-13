extern char far *d_6b54;
void asm_04c5(char far *a0, int a1, int a2);
/*@body*/
void pascal g2_385b(char a0, int a1, int a2)
{
    if (a0 >= 'a') {
        asm_04c5(d_6b54 + (a0 - 'a') * 40 + 0xac8, a1, a2);
    } else {
        asm_04c5(d_6b54 + (a0 - ' ') * 40 + 0x190, a1, a2);
    }
}