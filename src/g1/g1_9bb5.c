extern int d_009d;
extern int d_009f;
extern char d_06fd;
extern char far *d_637a;
void asm_0424(char far* a0, int a1, int a2);
char pascal g1_326e(int a0, int a1) { return 0; }
/*@body*/
void pascal g1_9bb5(int a2, register int a1, register int a0)
{
    ++d_06fd;
    if (d_06fd == 3)
        d_06fd = 0;

    if (g1_326e(a1, a0 - 0x100) == 0)
        asm_0424(d_637a + 0x8480, a1 - d_009d,
                 ((a0 - d_009f) >> 3) - 0x10);
    if (g1_326e(a1 + 4, a0 - 0x100) == 0)
        asm_0424(d_637a + 0x85c0, a1 - d_009d + 4,
                 ((a0 - d_009f) >> 3) - 0x10);
    if (g1_326e(a1, a0 - 0x80) == 0)
        asm_0424(d_637a + 0x8660, a1 - d_009d,
                 (a0 - d_009f) >> 3);
    if (g1_326e(a1 + 2, a0 - 0x80) == 0)
        asm_0424(d_637a + 0x8700, a1 - d_009d + 2,
                 (a0 - d_009f) >> 3);
    if (g1_326e(a1 + 4, a0 - 0x80) == 0)
        asm_0424(d_637a + 0x87a0, a1 - d_009d + 4,
                 (a0 - d_009f) >> 3);
    if (g1_326e(a1, a0) == 0)
        asm_0424(d_637a + 0x8840, a1 - d_009d,
                 ((a0 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 2, a0) == 0)
        asm_0424(d_637a + 0x88e0, a1 - d_009d + 2,
                 ((a0 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 4, a0) == 0)
        asm_0424(d_637a + 0x8980, a1 - d_009d + 4,
                 ((a0 - d_009f) >> 3) + 0x10);

    switch (d_06fd) {
    case 0:
        if (g1_326e(a1 + 2, a0 - 0x80) == 0)
            asm_0424(d_637a + 0x8700, a1 - d_009d + 2,
                     (a0 - d_009f) >> 3);
        if (g1_326e(a1 + 4, a0 - 0x80) == 0)
            asm_0424(d_637a + 0x87a0, a1 - d_009d + 4,
                     (a0 - d_009f) >> 3);
        break;
    case 1:
        if (g1_326e(a1 + 2, a0 - 0x80) == 0)
            asm_0424(d_637a + 0x8c00, a1 - d_009d + 2,
                     (a0 - d_009f) >> 3);
        if (g1_326e(a1 + 4, a0 - 0x80) == 0)
            asm_0424(d_637a + 0x8d40, a1 - d_009d + 4,
                     (a0 - d_009f) >> 3);
        break;
    case 2:
        if (g1_326e(a1 + 2, a0 - 0x80) == 0)
            asm_0424(d_637a + 0x8ca0, a1 - d_009d + 2,
                     (a0 - d_009f) >> 3);
        if (g1_326e(a1 + 4, a0 - 0x80) == 0)
            asm_0424(d_637a + 0x8de0, a1 - d_009d + 4,
                     (a0 - d_009f) >> 3);
        break;
    }
    switch (a2) {
    case 0:
    case 2:
        if (g1_326e(a1 + 2, a0 - 0x100) == 0)
            asm_0424(d_637a + 0x8520, a1 - d_009d + 2,
                     ((a0 - d_009f) >> 3) - 0x10);
        break;
    case 1:
        if (g1_326e(a1 + 2, a0 - 0x100) == 0)
            asm_0424(d_637a + 0x8a20, a1 - d_009d + 2,
                     ((a0 - d_009f) >> 3) - 0x10);
        break;
    case 3:
        if (g1_326e(a1 + 2, a0 - 0x100) == 0)
            asm_0424(d_637a + 0x8ac0, a1 - d_009d + 2,
                     ((a0 - d_009f) >> 3) - 0x10);
        break;
    }
}





