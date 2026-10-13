struct g1_9698_record { int x; int y; };
extern struct g1_9698_record d_9688[];
extern int d_009d;
extern int d_009f;
extern int d_05da;
extern char d_6379;
extern char far *d_a0fb;
extern int d_a0fd;
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_9698(void)
{
    register int i;
    struct g1_9698_record far *p;

    for (i = 0; i < d_05da; ++i) {
        p = &d_9688[i];
        if (g1_326e(p->x, p->y) == 0) {
            if (g1_3513(p->x, p->y)) {
                d_6379 = 1;
                asm_0424(d_a0fb + 0x3c00,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            } else {
                asm_0424(d_a0fb + 0x3b60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
        }
    }
}
