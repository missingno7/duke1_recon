extern char d_a0fa;      /* accepted type */
extern char d_4509;
void g2_3114(void) {}    /* accepted signature; stub for push cs; call near */
void pascal g2_37b6(char far* a0, int a1, int a2) {}    /* accepted signature; stub for push cs; call near */
/*@body*/
void g2_3fed(void)
{
    while (d_a0fa == 0x17)
        ;
    g2_3114();
    g2_37b6((char far *)&d_4509, 0x0e, 0);
}
