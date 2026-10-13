/* Busy-wait until the timer-interrupt tick counter reaches n (pascal). */
extern int d_02fb;
/*@body*/
void pascal g1_e92e(register int n)
{
    d_02fb = 0;
    while (d_02fb < n)
        ;
}
