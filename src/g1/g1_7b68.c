struct g1_7b68_record { int state, x, y, flag; };
extern struct g1_7b68_record d_9818[];
extern int d_009d;
extern int d_009f;
extern int d_05ca;
extern char far *d_a0fb;
void asm_0424(char far* a0, int a1, int a2);    /* accepted signature */
char pascal g1_326e(int a0, int a1) { return 0; }    /* accepted signature; stub for push cs; call near */
int g1_3714(int a0, int a1) { return 0; }    /* accepted signature; stub for push cs; call near */
int g1_3513(int a0, int a1) { return 0; }    /* accepted signature; stub for push cs; call near */
void pascal g1_2a40(int a0, int a1, int a2) {}    /* accepted signature; stub for push cs; call near */
void pascal g1_0b85(long a0) {}    /* accepted signature; stub for push cs; call near */
void pascal g1_0042(int a0) {}    /* accepted signature; stub for push cs; call near */
char pascal g1_3558(int a0, int a1) { return 0; }    /* accepted signature; stub for push cs; call near */
void pascal g1_314c(int a0, int a1) {}    /* accepted signature; stub for push cs; call near */
/*@body*/
void g1_7b68(void)
{
    register int i;
    struct g1_7b68_record far *p;

    for (i = 0; i < d_05ca; ++i) {
        p = &d_9818[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (g1_3513(p->x, p->y) != 0 && p->flag != 0) {
            p->state = 0;
            g1_2a40(0x640, p->x, p->y);
            g1_0b85(5000L);
            g1_0042(0x10);
            continue;
        }
        if (p->flag == 0 && g1_3558(p->x, p->y) != 0) {
            g1_314c(p->x, p->y);
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, p->x, p->y);
            }
            p->flag = 1;
        }
        if (p->flag == 0)
            asm_0424(d_a0fb + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        else
            asm_0424(d_a0fb + 0x2580,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
    }
}



