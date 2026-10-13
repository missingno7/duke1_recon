#include <dos.h>
extern void interrupt far (*d_5556_)(void);
void g2_25cd(void);
void asm_0258(int page);
void asm_05eb(int page);
void asm_05f7(int page);
void g2_2104(char far *filename);
void g2_24b1(void);
void pascal g2_3980(char far *filename);
void pascal g2_3a38(char far *filename);
void pascal g2_3252(char far *filename);
void pascal g2_365d(char far *filename);
void pascal g2_33ab(char far *filename);
void pascal g2_3504(char far *filename);
void pascal g2_30b0(char far *filename);
void interrupt g1_15f4(void) {}
void g2_1e97(void);
void g1_e83e(void) {}
void g1_e00d(void) {}
void pascal g1_e89d(char far *filename) {}
/*@body*/
void pascal g1_ec3d(void)
{
    g1_e83e();
    g2_25cd();
    asm_0258(0);
    asm_05eb(0);
    asm_05f7(0);
#if EPISODE == 1
    g2_2104("KEYS.DN1");
#elif EPISODE == 2
    g2_2104("KEYS.dn2");
#else
    g2_2104("KEYS.DN3");
#endif
    g2_24b1();
    g1_e00d();
#if EPISODE == 1
    g2_3980("duke1.dn1");
    g2_3a38("duke1-b.dn1");
    g2_3252("dn.dn1");
    g2_365d("end.dn1");
    g2_33ab("badguy.dn1");
    g2_3504("duke.dn1");
    g2_30b0("credits.dn1");
#elif EPISODE == 2
    g2_3980("duke1.dn2");
    g2_3a38("duke1-b.dn2");
    g2_3252("dn.dn2");
    g2_365d("end.dn2");
    g2_33ab("badguy.dn2");
    g2_3504("duke.dn2");
    g2_30b0("credits.dn2");
#else
    g2_3980("duke1.dn3");
    g2_3a38("duke1-b.dn3");
    g2_3252("dn.dn3");
    g2_365d("end.dn3");
    g2_33ab("badguy.dn3");
    g2_3504("duke.dn3");
    g2_30b0("credits.dn3");
#endif
    disable();
    d_5556_ = getvect(9);
    setvect(9, g1_15f4);
    enable();
    g2_1e97();
#if EPISODE == 1
    g1_e89d("SPEED.DN1");
#elif EPISODE == 2
    g1_e89d("SPEED.dn2");
#else
    g1_e89d("SPEED.DN3");
#endif
}
