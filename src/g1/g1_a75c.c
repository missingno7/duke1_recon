struct g1_a75c_record { int state, x, y, flag; };
extern struct g1_a75c_record d_a0bf[];
extern int d_009d;
extern int d_009f;
extern int d_5309;
extern int d_530c;
extern char far *d_a0fb;
extern int d_d149[];
extern int d_d14b;
extern int d_d14d;
extern int d_d57a;
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
void g1_a75c(void)
{
    register int i;
    struct g1_a75c_record far *p;

    for (i = 0; i < d_5309; i++) {
        p = &d_a0bf[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (p->flag == 0 && g1_3558(p->x, p->y) != 0) {
            g1_314c(p->x, p->y);
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, p->x, p->y);
            }
            p->flag = 1;
        }
        if (p->flag != 0) {
            if (g1_3513(p->x, p->y) != 0) {
                if (p->state != 'E') {
                    d_d149[d_d57a++] = p->state;
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                    g1_0042(0x10);
                } else if (d_d57a == 3 && d_d149[0] == 'D' &&
                           d_d14b == 'U' && d_d14d == 'K') {
                    g1_0b85(10000L);
                    g1_2a40(0x780, p->x, p->y);
                    g1_0042(0x25);
                    d_530c = 1;
                } else {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                    g1_0042(0x10);
                }
                p->state = 0;
            }
        }
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (p->flag == 0) {
            asm_0424(d_a0fb, p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            if (p->state == 'D')
                asm_0424(d_a0fb + 0x49c0, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (p->state == 'U')
                asm_0424(d_a0fb + 0x4a60, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (p->state == 'K')
                asm_0424(d_a0fb + 0x4b00, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (p->state == 'E')
                asm_0424(d_a0fb + 0x4ba0, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}
