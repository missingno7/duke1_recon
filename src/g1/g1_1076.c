struct reading {
    int a;
    int b;
    int c;
};
struct reading g1_0c52(int mode) { struct reading r; return r; }
/*@body*/
void g1_1076(void)
{
    struct reading r;

    do {
        r = g1_0c52(1);
    } while (r.b == 1 || r.c == 1);
}
