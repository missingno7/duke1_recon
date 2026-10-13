#include <dos.h>
void pascal g2_2e8c(char x, char y, char far *text, char attribute);
/*@body*/
void pascal g2_2e8c(char x, char y, char far *text, char attribute)
{
    register int i = 0;
    char far *screen = (char far *)MK_FP(0xB800, 0);

    while (text[i] != 0) {
        *(screen + i * 2 + x * 2 + y * 160) = text[i];
        *(screen + i * 2 + x * 2 + y * 160 + 1) = attribute;
        ++i;
    }
}
