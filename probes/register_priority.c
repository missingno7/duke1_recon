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

/* Loop weighting: a use inside a for/while/do counts 3x per nesting level.
   With syntactic loops the inner counter j outranks the outer i ... */
extern int n, h[];

void loops_for(void)
{
    register int i;
    register int j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            h[j] = 1;
}

/* ... label loops are not weighted: i and j both have 4 uses, declaration order wins. */
void loops_label(void)
{
    register int i;
    register int j;
    i = 0;
    goto otest;
obody:
    h[i] = 2;
    j = 0;
    goto itest;
ibody:
    h[j] = 1;
    j++;
itest:
    if (j < n)
        goto ibody;
    i++;
otest:
    if (i < n)
        goto obody;
}
