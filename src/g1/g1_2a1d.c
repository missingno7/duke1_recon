/* Clear the first word of every 8-byte record in table d_d4c3_[0..d_0518). */
struct s8 { int a, b, c, d; };
extern struct s8 d_d4c3_[];
extern int d_0518;
/*@body*/
void pascal g1_2a1d(void)
{
    register int i;

    for (i = 0; i < d_0518; i++)
        d_d4c3_[i].a = 0;
}
