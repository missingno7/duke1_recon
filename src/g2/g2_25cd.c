#include <dos.h>
extern char d_d56b;
/*@body*/
void g2_25cd(void)
{
    char first;
    char second;

    d_d56b = 1;
    first = inportb(0x201) & 0x10;
    second = inportb(0x201) & 0x20;
    if (first == 0) {
        d_d56b = 0;
    } else if (second == 0) {
        d_d56b = 0;
    }
}
