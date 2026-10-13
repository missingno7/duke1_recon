void outport(int port, int value);
void asm_05eb(int a0);
void asm_02ad(int a0, int a1);
/*@body*/
void g2_3114(void)
{
    register int x;
    register int y;

    outport(0x3c4, 0x0f02);
    asm_05eb(0);
    for (y = 0; y < 25; y++) {
        for (x = 0; x < 40; x += 2) {
            asm_02ad(0, y * 640 + x);
        }
    }
}
