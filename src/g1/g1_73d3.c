extern unsigned int far *d_7729;
extern int d_b62e;
extern int d_b632;
extern int d_c281;
extern int d_d136;
extern int d_d155;
extern int d_d4b9;
extern int d_d4bb;
int g1_35ee(int a0, int a1, int a2) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2b86(int a0, int a1, int a2) {}
/*@body*/
void g1_73d3(void)
{
    register int si;

    if (d_c281 == 0)
        return;
    if (g1_35ee(d_b62e - 2, d_b62e + d_d136, d_b632 - 32) != 0) {
        if (d_d155 == 2) {
            for (si = 0; si < (d_d136 >> 1); si++) {
                *((d_7729 + d_d4b9 + si) + (d_d4bb << 7) - 2) =
                    *((d_7729 + d_d4b9 + si) + (d_d4bb << 7) - 130);
                if (si % 2 != 0)
                    g1_314c(d_b62e * 2 + si * 2, d_b632);
                else
                    g1_2b86(1, d_b62e * 2 + si * 2, d_b632);
            }
            d_c281 = 0;
            d_d155 = 0;
            d_d155 = 1;
            return;
        }
        d_d155 = 1;
        return;
    }
    if (d_d155 == 1)
        d_d155 = 2;
}
