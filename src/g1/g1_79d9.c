extern int d_009d;
extern int d_009f;
extern int d_05c8;
extern char far *d_a0fb;
struct g1_79d9_record { int state, x, y, flag; };
extern struct g1_79d9_record d_a357[];
void asm_0424(char far *bitmap, int row, int offset);
char pascal g1_326e(int a0, int a1) {}
int g1_3714(int a0, int a1) {}
int g1_3513(int a0, int a1) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
void pascal g1_0042(int a0) {}
char pascal g1_3558(int a0, int a1) {}
void pascal g1_314c(int a0, int a1) {}
/*@body*/
void g1_79d9(void)
{
    register int i;
    struct g1_79d9_record far *p;

    for (i = 0; i < d_05c8; ++i) {
        p = &d_a357[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (g1_3513(p->x, p->y) != 0 && p->flag != 0) {
            p->state = 0;
            g1_2a40(0x500, p->x, p->y);
            g1_0b85(0x7d0L);
            g1_0042(0x10);
            continue;
        }
        if (p->flag == 0 && g1_3558(p->x, p->y) != 0) {
            g1_314c(p->x, p->y);
            p->flag = 1;
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(0x1f4L);
                g1_2a40(0x280, p->x, p->y);
            }
        }
        if (p->flag == 0)
            asm_0424(d_a0fb + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        else
            asm_0424(d_a0fb + 0x24e0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
    }
}