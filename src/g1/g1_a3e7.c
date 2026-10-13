extern int d_009d;
extern int d_009f;
extern int d_053c;
extern int d_05cc;
extern int d_06fe;
extern char d_5553;
extern char d_5555;
extern int d_7f04;
extern int d_9d96;
extern int d_a0b9;
extern char far *d_a0fb;
extern int d_b3d4;
extern char d_c68c;
struct g1_a3e7_record { int field[2]; };
extern struct g1_a3e7_record d_726b[];
char pascal g1_326e(int a0, int a1) {}
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void asm_0424(char far *bitmap, int row, int offset);
void g2_1821(void);
void g2_3b79(void);
void g2_1a82(void);
/*@body*/
void g1_a3e7(void)
{
    register int i;

    if (d_7f04 == -1)
        return;
    if (g1_326e(d_9d96, d_a0b9) != 0)
        return;

    if (d_7f04 == 0) {
        asm_0424(d_a0fb + 0x46a0,
                 d_9d96 - d_009d,
                 ((d_a0b9 - d_009f) >> 3) + 0x10);
        return;
    }

    d_06fe += 0xa0;
    if (d_06fe == 0x500)
        d_06fe = 0;

    asm_0424(d_a0fb + d_06fe + 0x41a0,
             d_9d96 - d_009d,
             ((d_a0b9 - d_009f) >> 3) + 0x10);

    if (g1_3513(d_9d96, d_a0b9) != 0 && d_5553 != 0) {
        d_5553 = 0;
        g2_1821();
    }

    if (g1_3513(d_9d96, d_a0b9) != 0 && d_b3d4 != 0 && d_c68c != 0) {
        for (i = 0; i < d_05cc; ++i)
            d_726b[i].field[2] = 0;

        d_7f04 = 0;
        g2_3b79();
        g1_0042(0x1f);
        d_053c = 0;
        d_b3d4 = 0;
    }

    if (g1_3513(d_9d96, d_a0b9) != 0 &&
        d_b3d4 == 0 && d_c68c != 0 &&
        d_7f04 != 0 && d_5555 != 0)
        g2_1a82();
}
