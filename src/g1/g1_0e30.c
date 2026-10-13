struct reading { int a; int b; int c; };
extern int d_771c[];
extern int d_7722[];
extern int d_9676[];
extern int d_967c[];
extern char d_a0fa;
extern int d_c297;
extern char d_cc81;
extern char d_d56b;
void pascal g2_44f5(int a0);
void pascal g2_01f5(int a0, int far* a1, int far* a2);
void pascal g2_1340(int a0, int a1);
void pascal g2_37b6(char far* a0, int a1, int a2);
void pascal g2_2870(int a0, int a1);
struct reading g1_0c52(int a0) { struct reading a1; return a1; }
/*@body*/
void g1_0e30(register int a0, int a1)
{
    int dx, dy;
    int x1, y1, x2, y2;
    struct reading text;
    register int i;

    for (;;) {
        do {
            text = g1_0c52(a0);
        } while (text.b == 1 || text.c == 1);
        g2_44f5(a1);
        while (d_a0fa == 0x24) {
        }
        i = 0x0f;
        do {
            if (++i == 0x17)
                i = 0x0f;
            g2_01f5(a0, &x1, &y1);
            text = g1_0c52(a0);
            g2_1340(a1 + 9, 0x0b);
            if (d_a0fa != 0)
                return;
        } while (text.b != 1 && text.c != 1);
        do {
            text = g1_0c52(a0);
        } while (text.b == 1 || text.c == 1);
        g2_37b6(" Hold the joystick in the", a1, 0x0d);
        g2_37b6(" bottom right and press a", a1, 0x0e);
        g2_37b6(" button.", a1, 0x0f);
        do {
            if (++i == 0x17)
                i = 0x0f;
            g2_01f5(a0, &x2, &y2);
            text = g1_0c52(a0);
            g2_1340(a1 + 9, 0x0f);
            if (d_a0fa != 0)
                return;
        } while (text.b != 1 && text.c != 1);
        do {
            text = g1_0c52(a0);
        } while (text.b == 1 || text.c == 1);
        dx = (x2 - x1) / 6;
        dy = (y2 - y1) / 6;
        d_9676[a0] = x1 + dx;
        d_771c[a0] = x2 - dx;
        d_967c[a0] = y1 + dy;
        d_7722[a0] = y2 - dy;
        g2_37b6(" Should button 1 (S)hoot", a1, 0x11);
        g2_37b6(" or (J)ump?", a1, 0x12);
        g2_2870(a1 + 0x0c, 0x12);
        if (d_a0fa == 1)
            return;
        if (d_a0fa == 0x1f)
            d_c297 = 1;
        else
            d_c297 = 0;
        d_cc81 = 1;
        d_d56b = 1;
        while (d_a0fa == 0x1f || d_a0fa == 0x24) {
        }
        return;
    }
}
