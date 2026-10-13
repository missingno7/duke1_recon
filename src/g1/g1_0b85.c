/* Add to the score and redraw it on both pages (resets display on wrap to 0). */
#include <dos.h>
extern long d_68f8_;
void asm_05eb(int a0);
void pascal g2_2789(long a0, int a1, int a2);
/*@body*/
void pascal g1_0b85(long value)
{
    outport(0x3ce, 5);
    d_68f8_ += value;
    if (d_68f8_ == 0L) {
        asm_05eb(0);
        g2_2789(0x00989680L, 0x25, 3);
        g2_2789(0L, 0x1e, 3);
        asm_05eb(1);
        g2_2789(0x00989680L, 0x25, 3);
        g2_2789(0L, 0x1e, 3);
    }
    asm_05eb(0);
    g2_2789(d_68f8_, 0x25, 3);
    asm_05eb(1);
    g2_2789(d_68f8_, 0x25, 3);
}
