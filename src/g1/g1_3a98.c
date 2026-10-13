/* goto kept: both loops are label loops.  Turbo C weights each use of a register variable
   by 3 per enclosing for/while/do (rule REGISTER-PRIORITY); with syntactic loops the inner
   counter j outranks i and takes SI (measured: v_for, og_for).  The original has i in SI and
   j in DI, which only equal (unweighted) priorities with i declared first reproduce. */
struct Record {
    int reserved;
    int y;
    int x;
    int height;
    int state;
};
extern struct Record d_c299[];
/* g1_3a98 translation-unit declarations from skeleton2.c */
extern int d_0099;      /* accepted type */
extern char d_0439;      /* accepted type */
extern int d_0526;      /* DATA, accessed as [2] byte(s) */
extern int d_064e;      /* DATA, accessed as [2] byte(s) */
extern unsigned int far* d_7729;      /* accepted type */
int g1_35ee(int a0, int a1, int a2) { return 0; }    /* accepted signature; stub for push cs; call near */
char g1_1247(void) { return 0; }    /* accepted signature; stub for push cs; call near */
unsigned char g1_12ce(void) { return 0; }    /* accepted signature; stub for push cs; call near */
/*@body*/
void g1_3a98(void)
{
    register int i;
    register int j;
    struct Record far *record;
    int height;

    ++d_064e;
    if (d_064e == 4)
        d_064e = 0;
    i = 0;
    goto otest;
obody:
    {
        record = &d_c299[i];
        height = record->height;
        j = 0;
        goto test;
    body:
        *(d_7729 + record->y + record->x + (j >> 1) - 2) =
            0x1c00 + ((d_064e & 1) << 5);
        ++j;
    test:
        if (j < height)
            goto body;

        if (record->state == 1) {
            *(d_7729 + record->y + record->x - 2) =
                0x1b80 + (d_064e << 5);
            *(d_7729 + record->y + record->x + (height >> 1) - 2) =
                0x1c40 + (d_064e << 5);
        }

        if (record->state == 0) {
            *(d_7729 + record->y + record->x - 2) =
                0x1be0 - (d_064e << 5);
            *(d_7729 + record->y + record->x + (height >> 1) - 2) =
                0x1ca0 - (d_064e << 5);
        }

        if (g1_35ee(record->y - 2, record->y + height + 2,
                    record->x - 0x20)) {
            if (record->state == 0 && g1_1247())
                --d_0099;
            if (record->state == 1 && g1_12ce())
                ++d_0099;
        }

        if (d_0439 != 0) {
            if (g1_35ee(record->y - 2, record->y + height + 2,
                        record->x + 0x60)) {
                if (record->state == 1 && g1_1247())
                    --d_0099;
                if (record->state == 0 && g1_12ce())
                    ++d_0099;
            }
        }
    }
    i++;
otest:
    if (i < d_0526)
        goto obody;
}
