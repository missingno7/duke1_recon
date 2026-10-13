struct g1_7163_record { int state, x, y; };
extern struct g1_7163_record d_c01e[];
extern int d_009d;
extern int d_009f;
extern int d_05c0;
extern char d_637e;
extern char far *d_a0fb;
void asm_0424(char far *a0, int a1, int a2);
void g2_15c9(void);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0042(int a0) {}
void g1_0acc(void) {}
/*@body*/
void g1_7163(void)
{
    register int i;
    struct g1_7163_record far *p;

    for (i = 0; i < d_05c0; i++) {
        p = &d_c01e[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (g1_3513(p->x, p->y)) {
            if (p->state > 1 && d_637e != 0) {
                d_637e = 0;
                g2_15c9();
            }
            if (p->state == 2) {
                p->state = 0;
                g1_0b85(100L);
                g1_2a40(0, p->x, p->y);
                g1_0042(1);
                g1_0acc();
                continue;
            }
            if (p->state == 3) {
                p->state = 0;
                g1_0b85(200L);
                g1_2a40(0x140, p->x, p->y);
                g1_0042(1);
                g1_0acc();
                g1_0acc();
                continue;
            }
        }
        if (p->state != 3 && g1_3558(p->x, p->y)) {
            if (p->state == 1) {
                g1_314c(p->x, p->y);
                if (g1_3714(p->x, p->y + 0x80) == 0) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
                p->state = 2;
            } else if (p->state == 2)
                p->state = 3;
        }
        if (p->state == 1) {
            asm_0424(d_a0fb + 0x3f20, (p->x - d_009d), (((p->y - d_009f) >> 3) + 0x10));
        } else {
            if (p->state == 2) {
                asm_0424(d_a0fb + 0x1b80, (p->x - d_009d), (((p->y - d_009f) >> 3) + 0x10));
            }
            if (p->state == 3) {
                asm_0424(d_a0fb + 0x1c20, (p->x - d_009d), (((p->y - d_009f) >> 3) + 0x10));
            }
        }
        if (p->state > 1 && d_637e != 0 && g1_3513(p->x, p->y)) {
            d_637e = 0;
            g2_15c9();
        }
    }
}




