/* g2_01a9 candidate */
#include <dos.h>
void asm_029d(int index, int value);
/*@body*/
void pascal g2_01a9(int value)
{
    register int i;
    for (i = 0; i < 16; ++i) {
        delay(value);
        asm_029d(i, 0);
    }
}
