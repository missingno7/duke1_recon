#include <dos.h>
void asm_029d(int a0, int a1);    /* accepted signature */
/*@body*/
void pascal g2_0009(int a0)
{
    register int i;
    for (i = 0; i < 16; ++i) {
        delay(a0);
        asm_029d(i, 0x17);
    }
}
