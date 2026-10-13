struct g1_c0c7_record {
    int offset;
    int x;
    int y;
    int alternate;
};
extern struct g1_c0c7_record d_b9de[];
extern int d_009d;
extern int d_009f;
extern int d_0437;
extern int d_5319;
extern char far *d_a0fb;
extern int d_a0fd;
void asm_0424(char far *bitmap, int x, int y);
char pascal g1_326e(int x, int y) { return 0; }
/*@body*/
void g1_c0c7(void)
{
    register int i;
    struct g1_c0c7_record far *p;

    for (i = 0; i < d_5319; ++i) {
        p = &d_b9de[i];
        if (p->offset != 0 && g1_326e(p->x, p->y) == 0) {
            if (p->alternate != 0) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    p->offset += 0xa0;
                if (p->offset == 0x5a0) {
                    p->offset = 0;
                    continue;
                }
                asm_0424(d_a0fb + p->offset + 0x4f60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            } else {
                asm_0424(d_a0fb + 0x5000,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
        }
    }
}






