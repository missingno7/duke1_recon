extern int d_0099;
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_05cc;
extern int d_06ef;
extern char far *d_a0fb;
extern char d_d13f;
extern char d_d4c0;
struct g1_7cfa_record { int x; int y; };
extern struct g1_7cfa_record d_726b[];
void asm_0424(char far *bitmap, int x, int y);
char pascal g1_326e(int a0, int a1) {}
char pascal g1_3558(int a0, int a1) {}
int g1_3513(int a0, int a1) {}
unsigned char g1_12ce(void) {}
char g1_1247(void) {}
void pascal g1_0042(int a0) {}
/*@body*/
void g1_7cfa(void)
{
    register int i;
    struct g1_7cfa_record far *p;

    d_06ef += 0xa0;
    if (d_06ef == 0x280)
        d_06ef = 0;
    for (i = 0; i < d_05cc; ++i) {
        p = &d_726b[i];
        if (p[1].x == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        g1_3558(p->x, p->y);
        if (g1_3513(p->x + 1, p->y) != 0 &&
            d_d13f != 0 && g1_12ce() != 0)
            ++d_0099;
        if (g1_3513(p->x - 1, p->y) != 0 &&
            d_d4c0 != 0 && g1_1247() != 0)
            --d_0099;
        asm_0424(d_a0fb + d_06ef + 0x28a0,
                 p->x - d_009d,
                 ((p->y - d_009f) >> 3) + 0x10);
        if (d_0437 == 0)
            g1_0042(0x15);
    }
}
