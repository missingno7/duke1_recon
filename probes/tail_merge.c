/* Rule TAIL-MERGE: with -O, Turbo C 2.0 cross-jumps identical instruction
   tails: the second branch's matching suffix (k = 0; f(20); return) is
   emitted once and the first branch jumps into it. */
extern int g, j, k;
void f(int);

void m(int s)
{
    if (s == 4) { g = 1; j = 2; k = 0; f(20); return; }
    if (s == 5) { g = 2; j = 0; k = 0; f(20); return; }
    f(1);
}
