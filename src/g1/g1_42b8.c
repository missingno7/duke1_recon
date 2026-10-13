extern int d_009d;
extern int d_009f;
extern int d_052e;
extern int d_a0f8;
extern char far *d_a0fb;
extern int d_a67b;
extern int d_a67e;

char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3714(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0b85(long value) {}
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_314c(int a0, int a1) {}
void pascal g2_1ffa(char far *bitmap);
void asm_0424(char far *bitmap, int row, int offset);
/*@body*/
void g1_42b8(void)
{
    if (d_a0f8 != 0)
        return;
    if (g1_326e(d_a67b, d_a67e) != 0)
        return;
    if (g1_3714(d_a67b, d_a67e + 0x80) == 0)
        d_a67e += 0x80;
    if (g1_3513(d_a67b, d_a67e) != 0 && d_052e != 0) {
        d_a0f8 = 1;
        g2_1ffa(d_a0fb + 0xb40);
        g1_2a40(0x3c0, d_a67b, d_a67e);
        g1_0b85(1000L);
        return;
    }

    if (d_052e == 0 && g1_3558(d_a67b, d_a67e) != 0) {
        g1_314c(d_a67b, d_a67e);
        d_052e = 1;
        if (g1_3714(d_a67b, d_a67e + 0x80) == 0) {
            g1_0b85(500L);
            g1_2a40(0x280, d_a67b, d_a67e);
        }
    }

    if (d_052e == 0) {
        asm_0424(d_a0fb,
                 d_a67b - d_009d,
                 ((d_a67e - d_009f) >> 3) + 0x10);
        return;
    }
    asm_0424(d_a0fb + 0xb40,
             d_a67b - d_009d,
             ((d_a67e - d_009f) >> 3) + 0x10);
}

