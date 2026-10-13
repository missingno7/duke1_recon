/* Rule LAZY-CLEANUP: in a function with a BP frame but no locals and no saved
   SI/DI, Turbo C 2.0 follows every cdecl call (even with no arguments) with
   `mov sp, bp`; a pascal callee needs no cleanup and gets none. */
void cf(void) {}
void pascal pf(void) {}
extern int g;

void use_cdecl(int a)
{
    g = a;
    cf();
}

void use_pascal(int a)
{
    g = a;
    pf();
}
