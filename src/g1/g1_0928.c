/* goto kept: jumps into the do-while test; the structured loops tried emit different code
   (measured by luna-g1_0928, 2026-10-13). */
#include <string.h>
extern long d_4fa2[];
extern long d_68f8;
extern char d_a0fa;
extern char d_5008[10][11];
void pascal g2_3d8c(int a0, int a1, int a2);
void g2_23f7(void);
void pascal g1_0042(int a0) {}
void pascal g1_0874(int a0, int a1, char far *a2) {}
/*@body*/
void g1_0928(void)
{
    register int entry;
    register int slot;

    slot = 0;
    goto test;
    do {
        if ((unsigned long)d_4fa2[slot] < (unsigned long)d_68f8) {
            entry = 10;
            while (entry > slot) {
                d_4fa2[entry] = d_4fa2[entry - 1];
                strcpy(d_5008[entry], d_5008[entry - 1]);
                --entry;
            }
            d_5008[slot][0] = 0;
            d_4fa2[slot] = d_68f8;
            g2_3d8c(7, 2, 5);
            g1_0042(0x18);
            g2_23f7();
            while (d_a0fa == 0x15) {
            }
            g1_0874(0x0e, 0x0b, d_5008[slot]);
            return;
        }
        ++slot;
test:
        ;
    } while (slot < 8);
}
