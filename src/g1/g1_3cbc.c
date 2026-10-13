extern int d_009d;
extern int d_009f;
extern int d_0528;
extern int d_052a;
extern int d_052c;
extern int d_798a_;
extern char far *d_a0fb_;
char pascal g1_326e(int a0, int a1) {}
int g1_3714(int a0, int a1) {}
int g1_3513(int a0, int a1) {}
void pascal g1_2a40(int a0, int a1, int a2) {}
void pascal g1_0b85(long value) {}
void pascal g1_0042(int a0) {}
char pascal g1_3558(int a0, int a1) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g2_1ffa(char far *bitmap);
void asm_0424(char far *bitmap, int x, int y);
/*@body*/
void g1_3cbc(void)
{
    if (d_798a_ != 0)
        return;

    if (g1_326e(d_0528, d_052a) != 0)
        return;

    if (g1_3714(d_0528, d_052a + 0x80) == 0)
        d_052a += 0x80;

    if (g1_3513(d_0528, d_052a) != 0 && d_052c != 0) {
        d_798a_ = 1;
        g1_2a40(0x3c0, d_0528, d_052a);
        g1_0b85(0x3e8L);
        g2_1ffa(d_a0fb_ + 0x640);
        g1_0042(0x0c);
        return;
    }

    if (d_052c == 0) {
        if (g1_3558(d_0528, d_052a) != 0) {
            g1_314c(d_0528, d_052a);
            d_052c = 1;
            if (g1_3714(d_0528, d_052a + 0x80) == 0) {
                g1_0b85(0x1f4L);
                g1_2a40(0x280, d_0528, d_052a);
            }
        }
    }

    if (d_052c == 0) {
        asm_0424(d_a0fb_,
                 d_0528 - d_009d,
                 ((d_052a - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb_ + 0x640,
                 d_0528 - d_009d,
                 ((d_052a - d_009f) >> 3) + 0x10);
    }
}

