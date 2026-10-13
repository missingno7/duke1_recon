/* What does -Z (register load suppression) change? */
extern int a, b, c;
extern char ch;
void z1(void) { a = b; c = b; }
void z2(int x) { a = x; b = a + 1; }
void z3(void) { a = 0; b = 0; c = a; }
int z4(int *p) { *p = 5; return *p; }
void z5(void) { ch = 3; a = ch; }
