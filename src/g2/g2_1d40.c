#include <stdlib.h>
extern long d_4fa2_[];
extern char d_5008_[10][11];
void pascal g2_2d58(int a0);
void pascal g2_37b6(char far *a0, int a1, int a2);
/*@body*/
void pascal g2_1d40(int a0)
{
    char buffer[20];
    register int i;

    g2_2d58(a0);
    g2_37b6(" --- HIGH  SCORES ---", a0 + 2, 3);
    for (i = 0; i < 8; ++i) {
        ltoa((long)i + 1L, buffer, 10);
        g2_37b6(buffer, a0 + 2, i * 2 + 5);
        g2_37b6(".", a0 + 3, i * 2 + 5);
        ltoa(d_4fa2_[i], buffer, 10);
        g2_37b6(buffer, a0 + 6, i * 2 + 5);
        g2_37b6(d_5008_[i], a0 + 14, i * 2 + 5);
    }
}
