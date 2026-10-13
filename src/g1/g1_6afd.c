#include <dos.h>
struct g1_6afd_record { int x; int y; };
extern struct g1_6afd_record d_70db_[];
extern int d_009d;
extern int d_009f;
extern int d_05ba;
extern int d_06e5;
void asm_0315(int x, int row, int source);
char pascal g1_326e(int x, int y) {}
/*@body*/
void g1_6afd(void)
{
    register int i;
    struct g1_6afd_record far *p;

    outport(0x3ce, 0x105);
    d_06e5 += 0x28;
    if (d_06e5 > 0x28)
        d_06e5 = 0;
    for (i = 0; i < d_05ba; ++i) {
        p = &d_70db_[i];
        if (g1_326e(p->x, p->y) == 0)
            asm_0315(p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10,
                     d_06e5);
    }
}
