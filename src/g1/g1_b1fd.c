extern int d_009d;
extern int d_009f;
extern int d_9d92;
extern int d_9d94;
extern char d_5c6b;
extern char far *d_a0fb;
extern int d_a677;
extern char d_c68c;

char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void g1_b118(void) {}
void g2_0f2a(void);
void asm_0424(char far *bitmap, int a0, int a1);

/*@body*/
void g1_b1fd(void)
{
    if (d_a677 != 0) {
        if (g1_326e(d_9d92, d_9d94) == 0) {
            if (d_5c6b == 1 && g1_3513(d_9d92, d_9d94) != 0) {
                d_5c6b = 0;
                g2_0f2a();
            }
            if (g1_3513(d_9d92, d_9d94) != 0 && d_c68c != 0) {
                g1_0042(0x1c);
                g1_b118();
            }
            asm_0424(d_a0fb + 0x4ce0,
                     d_9d92 - d_009d,
                     ((d_9d94 - d_009f) >> 3) + 0x10);
        }
    }
}
