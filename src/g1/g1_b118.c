#include <dos.h>
extern char d_02fa;
extern int d_02fb;
extern char far *d_0ba1[];
extern char d_6e0a;
extern char d_a0fa;
extern char d_d134;
extern char d_d4c0;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *a0, int a1, int a2);
void pascal g2_2870(int a0, int a1);
void asm_05eb(int page);
void asm_05f7(int page);
/*@body*/
void g1_b118(void)
{
    register int si;

    si = d_02fa;
    si <<= 2;
    g2_3d8c(2, 1, 3);
    g2_37b6(d_0ba1[si], 3, 3);
    g2_37b6(d_0ba1[si + 1], 3, 4);
    g2_37b6(d_0ba1[si + 2], 3, 5);
    g2_37b6(d_0ba1[si + 3], 3, 6);
    g2_37b6("      Press ENTER:      ", 3, 8);
    enable();
    do {
        g2_2870(0x1a, 8);
    } while (d_a0fa != 0x1c);
    d_d4c0 = 0;
    d_d134 = 0;
    disable();
    asm_05eb(!d_6e0a);
    asm_05f7(d_6e0a);
    d_02fb = 0;
}
