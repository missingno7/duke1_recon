#include <stdlib.h>
#include <string.h>
extern char far *d_6b54;
extern char d_6e0a;
void asm_05eb(int page);
void asm_053c(char far *bitmap, int x, int y);
/*@body*/
void pascal g2_2789(long value, int x, int page)
{
    char text[16];
    register int si;
    register int di;

    ultoa(value, text, 10);
    di = strlen(text);
    si = di - 1;
    for (; si >= 0; --si) {
        asm_05eb(1);
        asm_053c(d_6b54 + (text[di - si - 1] - '0') * 40 + 0x410,
                 x - si, page * 8);
        asm_05eb(0);
        asm_053c(d_6b54 + (text[di - si - 1] - '0') * 40 + 0x410,
                 x - si, page * 8);
    }
    asm_05eb(!d_6e0a);
}
