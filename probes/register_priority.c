/* Rule REGISTER-PRIORITY: Turbo C 2.0 gives SI to the register variable with
   the most uses and DI to the next; ties keep declaration order. */
extern int g;

void a_more(int x, int y)
{
    register int a;
    register int b;
    a = x;
    b = y;
    g = a; g = a + 1; g = a + 2; g = b;
}

void b_more(int x, int y)
{
    register int a;
    register int b;
    a = x;
    b = y;
    g = a; g = b + 1; g = b + 2; g = b;
}

void tie(int x, int y)
{
    register int a;
    register int b;
    a = x;
    b = y;
    g = a; g = b;
}
