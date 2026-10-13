extern int d_0099;
extern int d_05c4;
struct g1_7647_record { int state, value1, value2, count; };
extern struct g1_7647_record d_798c[];
char pascal g1_326e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
void pascal g1_0b85(long a0) {}
void pascal g1_0042(int a0) {}
void pascal g1_2e64(int a0, int a1) {}
void pascal g1_75b9(int a0, int a1, int a2) {}
int g1_3513(int a0, int a1) { return 0; }
char g1_1247(void) { return 0; }
unsigned char g1_12ce(void) { return 0; }
/*@body*/
void g1_7647(void)
{
    register int i;
    struct g1_7647_record far *p;

    for (i = 0; i < d_05c4; i++) {
        p = &d_798c[i];
        if (p->state != 0 &&
            (p->state <= 3 || p->state == 5 || p->state == 9 ||
             p->state == 15 || p->state == 25))
            p->count++;

        if (p->count == 4)
            p->count = 0;

        if (g1_326e(p->value1, p->value2) != 0 &&
            g1_326e(p->value1, p->value2 - 128) != 0)
            continue;

        if (g1_3558(p->value1, p->value2) != 0 ||
            g1_3558(p->value1, p->value2 - 128) != 0) {
            if (p->state == 1 || p->state == 2)
                g1_0b85(1000L);
            p->state = 3;
            g1_0042(18);
            g1_2e64(p->value1, p->value2 - 192);
        }

        if (p->state >= 3)
            p->state++;
        if (p->state == 26)
            p->state = 0;
        g1_75b9(p->count, p->value1, p->value2);

        if (p->state == 1) {
            if (g1_3513(p->value1 - 2, p->value2 - 64) ||
                g1_3513(p->value1 - 4, p->value2 - 64) ||
                g1_3513(p->value1 - 6, p->value2 - 64)) {
                if (g1_1247())
                    d_0099--;
            }
        }

        if (p->state == 2) {
            if (g1_3513(p->value1 + 2, p->value2 - 64) ||
                g1_3513(p->value1 + 4, p->value2 - 64) ||
                g1_3513(p->value1 + 6, p->value2 - 64)) {
                if (g1_12ce())
                    d_0099++;
            }
        }
    }
}




