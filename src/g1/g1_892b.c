#include <dos.h>
struct g1_892b_record { int offset; int x; unsigned int y; };
extern struct g1_892b_record d_7f06_[];
extern int d_009d;
extern int d_009f;
extern int d_05d4;
extern char far *d_637a_;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) {}
/*@body*/
void g1_892b(void)
{
    register unsigned int i;
    struct g1_892b_record far *p;
    for (i = 0; i < d_05d4; ++i) {
        p = &d_7f06_[i];
        if (g1_326e(p->x, p->y) == 0)
            asm_0424((d_637a_ + p->offset),
                    p->x - d_009d,
                    ((p->y - d_009f) >> 3) + 16);
    }
}







