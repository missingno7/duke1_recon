struct g1_4638_entry { int state, position2, position4; };
extern struct g1_4638_entry d_9b3a[];
extern int d_009d;
extern int d_009f;
extern int d_0542;
extern char d_6379;
extern char far *d_a0fb;
void asm_0424(char far *bitmap, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
int g1_3513(int a0, int a1) { return 0; }
/*@body*/
void g1_4638(void)
{
    register int i;
    struct g1_4638_entry far *p;

    for (i = 0; i < d_0542; ++i) {
        p = &d_9b3a[i];
        if (p->state != 0) {
            ++p->state;

            if (p->state >= 15) {
            if (p->state == 15 &&
                g1_326e(p->position2, p->position4) == 0)
                g1_0042(0x2b);

            if (p->state < 25) {
                if (p->state % 2 != 0 &&
                    g1_326e(p->position2, p->position4) == 0) {
                    asm_0424(d_a0fb + 0x1220,
                             p->position2 - d_009d,
                             ((p->position4 - d_009f) >> 3) + 0x10);
                }
            } else if (p->state < 45) {
                if (g1_326e(p->position2, p->position4) == 0 &&
                    g1_326e(p->position2 - 6, p->position4) == 0) {
                    asm_0424(d_a0fb + 0x12c0 + (p->state % 2) * 0xa0,
                             p->position2 - d_009d,
                             ((p->position4 - d_009f) >> 3) + 0x10);
                    asm_0424(d_a0fb + 0x12c0 + (p->state % 2) * 0xa0,
                             p->position2 - d_009d - 2,
                             ((p->position4 - d_009f) >> 3) + 0x10);
                    asm_0424(d_a0fb + 0x1400 + (p->state % 2) * 0xa0,
                             p->position2 - d_009d - 4,
                             ((p->position4 - d_009f) >> 3) + 0x10);

                    if (g1_3513(p->position2, p->position4) != 0 ||
                        g1_3513(p->position2 - 2, p->position4) != 0 ||
                        g1_3513(p->position2 - 4, p->position4) != 0)
                        d_6379 = 1;
                }
            } else if (p->state > 65) {
                p->state = 1;
            }
            }
        }
    }
}
