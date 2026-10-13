extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_5000;
extern int d_5149;
extern int d_52db;
extern int d_5307;
extern char d_555c;
extern char far *d_a0fb;
extern char d_c68c;
extern int d_cc82;
extern int d_d13d;
extern int d_d140;
void asm_0424(char far *bitmap, int row, int offset);
void g2_178a(void);
char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void pascal g1_1b8a(int a0, int a1, int a2) {}
/*@body*/
void g1_a53a(void)
{
    if (d_5307 == 0)
        return;

    if (g1_326e(d_d13d - 2, d_d140) == 0) {
        asm_0424(d_a0fb + 0x4880,
                 d_d13d - d_009d - 2,
                 ((d_d140 - d_009f) >> 3) + 0x10);
    }

    if (g1_326e(d_d13d + 2, d_d140) == 0) {
        asm_0424(d_a0fb + 0x4920,
                 d_d13d - d_009d + 2,
                 ((d_d140 - d_009f) >> 3) + 0x10);
    }

    if (g1_326e(d_d13d, d_d140) != 0) {
        d_52db = 0;
        return;
    }

    if (g1_3513(d_d13d, d_d140) != 0 && d_555c != 0) {
        d_555c = 0;
        g2_178a();
    }

    if (g1_3513(d_d13d, d_d140) != 0) {
        if (d_c68c != 0 && d_5149 == 0) {
            if (d_cc82 != 0) {
                d_5149 = 1;
                d_5000 = 1;
                g1_0042(5);
            } else {
                d_52db = 1;
            }
        }
    }

    if (d_5149 == 0 && d_0437 == 0) {
        asm_0424(d_a0fb + 0x4740,
                 d_d13d - d_009d,
                 ((d_d140 - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb + 0x47e0,
                 d_d13d - d_009d,
                 ((d_d140 - d_009f) >> 3) + 0x10);
    }

    if (d_52db != 0) {
        if (d_0437 == 0)
            g1_1b8a(1, d_d13d + 2, d_d140 - 36);
        if (d_0437 == 0x40)
            g1_1b8a(2, d_d13d - 2, d_d140 - 36);
    }
}


