extern int d_0095;
extern int d_039d;
extern char d_5318;
void pascal g2_01a9(int a0);
void pascal g1_ec3d(void) {}
void pascal g1_fd15(void) {}
void pascal g1_fc85(void) {}
/*@body*/
void main(int argc, char **argv)
{
    if (argv[1][0] == 'a' && argv[1][1] == 's' && argv[1][2] == 'p') {
        d_0095 = 1;
        if (argv[2][0] == 'g')
            d_039d = 1;
    }
    g1_ec3d();
    for (;;) {
        g1_fd15();
        g1_fc85();
        g2_01a9(15);
        d_5318 = 0;
    }
}
