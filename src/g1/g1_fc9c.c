#include <conio.h>
#include <dos.h>
#include <stdlib.h>
extern void far *d_9684_;
extern void far *d_5a0d_;
extern void interrupt far (*d_5556_)(void);
void g2_205f(char far *filename);
void g2_1e1b(void);
void g2_2f04(void);
void g2_1319(void);
void g1_df57(char far *filename, void far *buffer) {}
void g1_dfb2(char far *filename, void far *buffer) {}
void pascal g1_e8ed(char far *filename) {}
/*@body*/
void g1_fc9c(void)
{
    textmode(3);
#if EPISODE == 1
    g2_205f("KEYS.DN1");
    g1_df57("USERDEMO.DN1", d_9684_);
    g1_dfb2("MY_DEMO.DN1", d_5a0d_);
    g1_e8ed("SPEED.DN1");
#elif EPISODE == 2
    g2_205f("KEYS.dn2");
    g1_df57("USERDEMO.dn2", d_9684_);
    g1_dfb2("MY_DEMO.dn2", d_5a0d_);
    g1_e8ed("SPEED.dn2");
#else
    g2_205f("KEYS.DN3");
    g1_df57("USERDEMO.dn3", d_9684_);
    g1_dfb2("MY_DEMO.DN3", d_5a0d_);
    g1_e8ed("SPEED.DN3");
#endif
    g2_1e1b();
    g2_2f04();
    disable();
    setvect(9, d_5556_);
    g2_1319();
    enable();
    _exit(0);
}
