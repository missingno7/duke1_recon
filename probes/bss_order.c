/* Rule BSS-ORDER: Turbo C 2.0 emits a unit's uninitialised (tentative) globals
   into _BSS sorted by the symbol hash (first char + 4*last char + 32*length)
   mod 1024, ties in order of first appearance of the name in the unit. */
extern int azb;                 /* first appearance of azb: before axb, ayb */
int axb; int ayb; int azb;      /* same hash 585: order azb, axb, ayb */
char zz;                        /* 122 + 488 + 64 = 674: last */
int ab;                         /* 97 + 392 + 64 = 553 */
int axxxxxxxxxxxxxxxxxb;        /* 97 + 392 + 32*20 = 1129 -> bucket 105, first */
