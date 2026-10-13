extern char d_cc81;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_37b6(char far *a0, int a1, int a2);
/*@body*/
void g2_2473(void)
{
    g2_3d8c(7, 0, 1);
    if (d_cc81 != 0) {
        g2_37b6("\040\040\040\040\040Press a button..\040\040\040", 7, 1);
    } else {
        g2_37b6("\040\040\040\040\040\040Press any key.\040\040\040\040", 7, 1);
    }
}
