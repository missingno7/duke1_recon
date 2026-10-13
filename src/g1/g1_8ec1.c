struct g1_8ec1_record { int x, y, used; };
extern struct g1_8ec1_record d_b3d6[];
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_05c2;
extern int d_06f7;
extern int d_4ed4;
extern char far *d_637a;
extern char far *d_a0fb;
extern int d_c68d;
extern int d_c68f;
extern int d_c8e9;
extern int d_d56e;
extern int d_d572;
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g1_0042(int a0) {}
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_0b85(long a0) {}
void pascal g1_2fe7(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
void g1_0a0e(void) {}
/*@body*/
void g1_8ec1(void)
{
    register int i;
    register int event;

    event = 0;
    d_06f7 += 0xa0;
    if (d_06f7 == 0x320)
        d_06f7 = 0;
    if (g1_326e(d_c68d, d_c68f) != 0) {
        if (d_d572 < 2)
            return;
        d_d572 = 0;
        for (i = 0; i < d_05c2; ++i)
            d_b3d6[i].used = 0;
        return;
    }

    if (d_c8e9 != 0 && d_d572 == 0)
        return;

    if (g1_3558(d_c68d, d_c68f) != 0) {
        --d_d56e;
        g1_314c(d_c68d, d_c68f);
        if (d_d56e == 0)
            d_c8e9 = 1;
        event = 1;
        g1_0042(0xa);
    }
    if (g1_3558(d_c68d, d_c68f - 0x80) != 0) {
        --d_d56e;
        g1_314c(d_c68d, d_c68f - 0x80);
        if (d_d56e == 0)
            d_c8e9 = 1;
        event = 1;
        g1_0042(0xa);
    }
    if (g1_3558(d_c68d, d_c68f - 0x100) != 0) {
        --d_d56e;
        g1_314c(d_c68d, d_c68f - 0x100);
        if (d_d56e == 0)
            d_c8e9 = 1;
        event = 1;
        g1_0042(0xa);
    }

    if (d_c8e9 == 0) {
        g1_0042(0x24);
        if (event == 0) {
            asm_0424(d_a0fb + d_06f7 + 0x3840,
                     d_c68d - d_009d,
                     ((d_c68f - d_009f) >> 3) + 0x10);
            if (g1_326e(d_c68d, d_c68f - 0x80) == 0)
                asm_0424(d_a0fb + d_06f7 + 0x3840,
                         d_c68d - d_009d,
                         (d_c68f - d_009f) >> 3);
            if (g1_326e(d_c68d, d_c68f - 0x100) == 0)
                asm_0424(d_a0fb + d_06f7 + 0x3840,
                         d_c68d - d_009d,
                         ((d_c68f - d_009f) >> 3) - 0x10);
        } else {
            asm_0424(d_637a + 0x9f60,
                     d_c68d - d_009d,
                     ((d_c68f - d_009f) >> 3) + 0x10);
            if (g1_326e(d_c68d, d_c68f - 0x80) == 0)
                asm_0424(d_637a + 0x9f60,
                         d_c68d - d_009d,
                         (d_c68f - d_009f) >> 3);
            if (g1_326e(d_c68d, d_c68f - 0x100) == 0)
                asm_0424(d_637a + 0x9f60,
                         d_c68d - d_009d,
                         ((d_c68f - d_009f) >> 3) - 0x10);
        }
        if (g1_3513(d_c68d, d_c68f - 0x40) != 0) {
            if (d_4ed4 > 0) {
                d_4ed4 = 0;
                g1_0a0e();
            }
        }
        return;
    }

    asm_0424(d_a0fb + 0x3840,
             d_c68d - d_009d,
             ((d_c68f - d_009f) >> 3) + 0x10);
    if (g1_326e(d_c68d, d_c68f - 0x80) == 0)
        asm_0424(d_a0fb + 0x3840,
                 d_c68d - d_009d,
                 (d_c68f - d_009f) >> 3);
    if (g1_326e(d_c68d, d_c68f - 0x100) == 0)
        asm_0424(d_a0fb + 0x3840,
                 d_c68d - d_009d,
                 ((d_c68f - d_009f) >> 3) - 0x10);
    ++d_d572;
    if (d_0437 == 0)
        g1_2e64(d_c68d - 1, d_c68f);
    if (d_0437 == 0x40)
        g1_2e64(d_c68d + 1, d_c68f);
    if (d_d572 == 0x20) {
        d_d572 = 0;
        for (i = 0; i < d_05c2; ++i)
            d_b3d6[i].used = 0;
        g1_0b85(0x4e20L);
        g1_0042(0x11);
        return;
    }
    if (d_0437 == 0)
        return;

    switch (d_d572) {
    case 2:
        g1_2b86(1, d_c68d - 1, d_c68f);
        break;
    case 8:
        g1_2b86(1, d_c68d - 2, d_c68f - 0x80);
        break;
    case 10:
        g1_2b86(1, d_c68d + 1, d_c68f + 0x100);
        break;
    case 13:
        g1_2b86(1, d_c68d, d_c68f + 0x80);
        g1_2b86(1, d_c68d - 1, d_c68f + 0x180);
        g1_2b86(1, d_c68d, d_c68f - 0x180);
        g1_2b86(3, d_c68d + 2, d_c68f);
        g1_2b86(3, d_c68d, d_c68f + 0x80);
        break;
    case 15:
        g1_2b86(1, d_c68d + 2, d_c68f - 0x80);
        break;
    case 17:
        g1_2b86(1, d_c68d + 1, d_c68f + 0x100);
        g1_2b86(1, d_c68d + 2, d_c68f);
        g1_2b86(1, d_c68d - 3, d_c68f - 0x100);
        g1_314c(d_c68d - 1, d_c68f);
        break;
    case 18:
        g1_314c(d_c68d + 3, d_c68f - 0x100);
        g1_2b86(1, d_c68d + 1, d_c68f + 0x100);
        break;
    case 23:
        g1_2fe7(d_c68d, d_c68f + 0x40);
        g1_2fe7(d_c68d - 1, d_c68f - 0x40);
        g1_2b86(3, d_c68d, d_c68f + 0x80);
        g1_314c(d_c68d + 2, d_c68f);
        g1_314c(d_c68d - 1, d_c68f + 0x180);
        g1_2b86(1, d_c68d - 1, d_c68f + 0x180);
        g1_2b86(3, d_c68d, d_c68f - 0x180);
        g1_2b86(3, d_c68d + 2, d_c68f - 0x80);
        g1_2b86(1, d_c68d + 1, d_c68f + 0x100);
        break;
    case 24:
        g1_314c(d_c68d + 1, d_c68f + 0x80);
        g1_314c(d_c68d - 2, d_c68f - 0x100);
        g1_2b86(1, d_c68d + 2, d_c68f);
        g1_2b86(3, d_c68d - 3, d_c68f - 0x100);
        g1_314c(d_c68d - 1, d_c68f);
        g1_314c(d_c68d + 3, d_c68f - 0x100);
        g1_2b86(1, d_c68d - 1, d_c68f);
        g1_2b86(3, d_c68d - 2, d_c68f - 0x80);
        g1_2b86(1, d_c68d + 1, d_c68f + 0x100);
        break;
    case 29:
        g1_2fe7(d_c68d + 3, d_c68f - 0x80);
        g1_2fe7(d_c68d + 2, d_c68f + 0x100);
        g1_2b86(1, d_c68d, d_c68f + 0x80);
        g1_314c(d_c68d + 2, d_c68f);
        g1_314c(d_c68d - 1, d_c68f + 0x180);
        g1_2b86(3, d_c68d - 1, d_c68f + 0x180);
        g1_2b86(1, d_c68d, d_c68f - 0x180);
        g1_2b86(3, d_c68d + 2, d_c68f - 0x80);
        g1_2b86(1, d_c68d + 1, d_c68f + 0x100);
        break;
    case 31:
        g1_2fe7(d_c68d - 2, d_c68f - 0x180);
        g1_314c(d_c68d + 1, d_c68f + 0x80);
        g1_314c(d_c68d, d_c68f);
        g1_2b86(3, d_c68d + 2, d_c68f);
        g1_2b86(3, d_c68d - 3, d_c68f - 0x100);
        g1_314c(d_c68d - 1, d_c68f);
        g1_314c(d_c68d + 3, d_c68f - 0x100);
        g1_2b86(1, d_c68d - 1, d_c68f);
        g1_2b86(1, d_c68d - 2, d_c68f - 0x80);
        g1_2b86(3, d_c68d + 1, d_c68f + 0x100);
        g1_2a40(0x780, d_c68d - 1, d_c68f);
        g1_2a40(0x780, d_c68d + 1, d_c68f);
        break;
    }
}
