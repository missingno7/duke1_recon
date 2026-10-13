/* goto kept: the original places the shared g1_2e64 tail inside the 0xFE branch and jumps
   back to it from the 0xFF branch; the structured form (receipt-structured-equal-size.json)
   moves the shared call after the 0xFF renderer. */
extern int d_0099;
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_0544;
extern int d_0546[];
extern int d_0548[];
extern int d_0576[];
extern int d_0578[];
extern int d_05a6;
extern int d_05a8;
extern char d_6379;
extern char far *d_637a;
struct G1_4874_item { int type; int x; int y; int step; };
extern struct G1_4874_item d_637f[];
void asm_0424(char far *a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
char pascal g1_3558(int a0, int a1) { return 0; }
int g1_3513(int a0, int a1) { return 0; }
void pascal g1_2b86(int a0, int a1, int a2) {}
void pascal g1_0b85(long a0) {}
void pascal g1_0042(int a0) {}
int g1_3714(int a0, int a1) { return 0; }
void pascal g1_29d0(int a0, int a1) {}
int g1_367e(int a0, int a1) { return 0; }
void pascal g1_1b8a(int a0, int a1, int a2) {}
void pascal g1_314c(int a0, int a1) {}
void pascal g1_2e64(int a0, int a1) {}
/*@body*/
void g1_4874(void)
{
    register int i;
    struct G1_4874_item far *obj;

    ++d_05a8;
    if (d_05a8 == 10)
        d_05a8 = 0;
    d_05a6 += 160;
    if (d_05a6 == 640)
        d_05a6 = 0;

    for (i = 0; i < d_0544; ++i) {
        obj = &d_637f[i];
        if (obj->type == 0xfe) {
            if (g1_3714(obj->x, obj->y + 128)) {
                g1_314c(obj->x, obj->y);
                g1_2b86(1, obj->x, obj->y);
                obj->type = 0;
                continue;
            }
            if (obj->step <= 20) {
                obj->x += d_0546[obj->step];
                obj->y += d_0548[obj->step];
                obj->step += 2;
            } else {
                obj->y += 128;
            }
            if (g1_326e(obj->x, obj->y)) {
                obj->type = 0;
                continue;
            }
            asm_0424(d_637a + 0x3c0,
                     obj->x - d_009d,
                     ((obj->y - d_009f) >> 3) + 16);
            asm_0424(d_637a,
                     obj->x - d_009d,
                     (obj->y - d_009f) >> 3);
        shared_animation_finish:
            g1_2e64(obj->x, obj->y - 128);
            continue;
        }

        if (obj->type == 0xff) {
            if (g1_3714(obj->x, obj->y + 128)) {
                g1_314c(obj->x, obj->y);
                g1_2b86(1, obj->x, obj->y);
                obj->type = 0;
                continue;
            }
            if (obj->step < 20) {
                obj->x += d_0576[obj->step];
                obj->y += d_0578[obj->step];
                obj->step += 2;
            } else {
                obj->y += 128;
            }
            if (g1_326e(obj->x, obj->y)) {
                obj->type = 0;
                continue;
            }
            asm_0424(d_637a + 0x3c0,
                     obj->x - d_009d,
                     ((obj->y - d_009f) >> 3) + 16);
            asm_0424(d_637a + 0x320,
                     obj->x - d_009d,
                     (obj->y - d_009f) >> 3);
            goto shared_animation_finish;
        }

        if (obj->type == 0)
            continue;
        if (g1_326e(obj->x, obj->y))
            continue;
        if (g1_326e(obj->x, obj->y - 128))
            continue;

        if (g1_3558(obj->x, obj->y - 128) ||
            g1_3513(obj->x, obj->y - 128)) {
            if (g1_3513(obj->x, obj->y))
                d_6379 = 1;
            if (d_0437 == 0)
                obj->type = 0xfe;
            else if (d_0437 == 0x20)
                obj->type = 0xfe;
            else
                obj->type = 0xff;
            g1_2b86(1, obj->x, obj->y);
            obj->step = 0;
            g1_0b85(200L);
            g1_0042(18);
            continue;
        }

        if (!g1_3714(obj->x, obj->y + 128))
            obj->y += 8;
        if (g1_3714(obj->x, obj->y + 128)) {
            obj->y -= 8;
            if (!g1_3714(obj->x, obj->y + 128) && d_05a6 == 0)
                g1_29d0(obj->x, obj->y);
        }

        if (d_05a6 == 0) {
            if (obj->x > d_0099 + d_009d) {
                if (obj->type > 1) {
                    --obj->type;
                } else if (!g1_367e(obj->x - 1, obj->y - 5)) {
                    --obj->x;
                    if (d_05a8 == 0)
                        g1_1b8a(1, obj->x - 1, obj->y - 160);
                }
            }
            if (obj->x < d_0099 + d_009d) {
                if (obj->type < 6) {
                    ++obj->type;
                } else if (!g1_367e(obj->x + 2, obj->y - 5)) {
                    ++obj->x;
                    if (d_05a8 == 0)
                        g1_1b8a(2, obj->x + 1, obj->y - 160);
                }
            }
        }

        asm_0424(d_637a + d_05a6 + 0x3c0,
                 obj->x - d_009d,
                 ((obj->y - d_009f) >> 3) + 16);
        asm_0424(d_637a + (obj->type - 1) * 0xa0,
                 obj->x - d_009d,
                 (obj->y - d_009f) >> 3);
    }
}
