struct g1_9757_row { int state, x, y; };
extern struct g1_9757_row d_c915[];
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_05dc;
extern int d_06f9;
extern char far *d_a0fb;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
/*@body*/
void g1_9757(void)
{
    register int i;
    struct g1_9757_row far *p;

    d_06f9 += 0xa0;
    if (d_06f9 == 0x1e0)
        d_06f9 = 0;
    for (i = 0; i < d_05dc; i++) {
        p = &d_c915[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (p->state == 1 && g1_3558(p->x, p->y)) {
            g1_314c(p->x, p->y);
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(0x1f4L);
                g1_2a40(0x280, p->x, p->y);
            }
            p->state = 2;
        }
        if (p->state == 2 && g1_3513(p->x, p->y) != 0) {
            p->state = 0;
            g1_0042(0x10);
            switch (d_0437) {
            case 0:
                g1_0b85(0x64L);
                g1_2a40(0, p->x, p->y);
                break;
            case 0x20:
                g1_0b85(0x1f4L);
                g1_2a40(0x280, p->x, p->y);
                break;
            case 0x40:
                g1_0b85(0x7d0L);
                g1_2a40(0x500, p->x, p->y);
                break;
            case 0x60:
                g1_0b85(0x1388L);
                g1_2a40(0x640, p->x, p->y);
                break;
            default:
                continue;
            }
            continue;
        }
        if (p->state == 1) {
            asm_0424(d_a0fb + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb + d_06f9 + 0x3ca0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}
