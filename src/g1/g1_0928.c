/* goto kept: jumps into the do-while test; the structured loops tried emit different code
   (measured by luna-g1_0928, 2026-10-13). */
#include <string.h>
extern long d_4fa2_[];
extern long d_68f8_;
extern char d_a0fa_;
extern char d_5008_[10][11];
void pascal g2_3d8c(int a0, int a1, int a2);
void g2_23f7(void);
void pascal g1_0042(int a0) {}
void pascal g1_0874(volatile int a0, volatile int a1, char far *a2) {}
/*@body*/
void g1_0928(void)
{
    register int entry;
    register int slot;

    slot = 0;
    goto test;
    do {
        if ((unsigned long)d_4fa2_[slot] < (unsigned long)d_68f8_) {
            entry = 10;
            while (entry > slot) {
                d_4fa2_[entry] = d_4fa2_[entry - 1];
                strcpy(d_5008_[entry], d_5008_[entry - 1]);
                --entry;
            }
            d_5008_[slot][0] = 0;
            d_4fa2_[slot] = d_68f8_;
            g2_3d8c(7, 2, 5);
            g1_0042(0x18);
            g2_23f7();
            while (d_a0fa_ == 0x15) {
            }
            g1_0874(0x0e, 0x0b, d_5008_[slot]);
            return;
        }
        ++slot;
test:
        ;
    } while (slot < 8);
}
