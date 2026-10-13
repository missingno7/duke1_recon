extern int d_009d;
extern int d_009f;
extern int d_9d92_;
extern int d_9d94_;
extern char d_5c6b_;
extern char far *d_a0fb_;
extern int d_a677_;
extern char d_c68c_;

char pascal g1_326e(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_0042(int a0) {}
void g1_b118(void) {}
void g2_0f2a(void);
void asm_0424(char far *bitmap, int a0, int a1);

/*@body*/
void g1_b1fd(void)
{
    if (d_a677_ != 0) {
        if (g1_326e(d_9d92_, d_9d94_) == 0) {
            if (d_5c6b_ == 1 && g1_3513(d_9d92_, d_9d94_) != 0) {
                d_5c6b_ = 0;
                g2_0f2a();
            }
            if (g1_3513(d_9d92_, d_9d94_) != 0 && d_c68c_ != 0) {
                g1_0042(0x1c);
                g1_b118();
            }
            asm_0424(d_a0fb_ + 0x4ce0,
                     d_9d92_ - d_009d,
                     ((d_9d94_ - d_009f) >> 3) + 0x10);
        }
    }
}
