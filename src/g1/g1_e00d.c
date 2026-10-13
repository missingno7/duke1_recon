#include <stdlib.h>
extern void far *d_5a0d_;
extern char far *d_5ec4_;
extern char far *d_637a_;
extern char far *d_6b54_;
extern unsigned int far *d_7729_;
extern void far *d_9684_;
extern char far *d_a0ef_;
extern char far *d_a0fb_;
void pascal g2_01a9(int a0);
void g2_1f24(void);
void pascal g2_0036(int a0);
void g2_3114(void);
void g2_3af3(void);
void pascal g1_10fb(char far *a0, int a1, int a2) {}
void g1_295e(char far *a0, void far *a1, unsigned int a2) {}
void g1_de71(char far *a0, char far *a1) {}
void g1_dee9(char far *a0, char far *a1) {}
#if EPISODE == 1
#define F_BORDER0 "border.dn1"
#define F_FONT1 "font1.dn1"
#define F_FONT2 "font2.dn1"
#define F_NUMBERS "numbers.dn1"
#define F_OBJECT0 "object0.dn1"
#define F_OBJECT1 "object1.dn1"
#define F_OBJECT2 "object2.dn1"
#define F_USERDEMO "USERDEMO.DN1"
#define F_MYDEMO "MY_DEMO.DN1"
#define F_MAN0 "man0.dn1"
#define F_MAN1 "man1.dn1"
#define F_MAN2 "man2.dn1"
#define F_MAN3 "man3.dn1"
#define F_BACK0 "back0.dn1"
#define F_BACK1 "back1.dn1"
#define F_BACK2 "back2.dn1"
#define F_BACK3 "back3.dn1"
#define F_SOLID0 "solid0.dn1"
#define F_SOLID1 "solid1.dn1"
#define F_SOLID2 "solid2.dn1"
#define F_SOLID3 "solid3.dn1"
#define F_ANIM0 "anim0.dn1"
#define F_ANIM1 "anim1.dn1"
#define F_ANIM2 "anim2.dn1"
#define F_ANIM3 "anim3.dn1"
#define F_ANIM4 "anim4.dn1"
#define F_ANIM5 "anim5.dn1"
#elif EPISODE == 2
#define F_BORDER0 "border.dn2"
#define F_FONT1 "font1.dn2"
#define F_FONT2 "font2.dn2"
#define F_NUMBERS "numbers.dn2"
#define F_OBJECT0 "object0.dn2"
#define F_OBJECT1 "object1.dn2"
#define F_OBJECT2 "object2.dn2"
#define F_USERDEMO "USERDEMO.dn2"
#define F_MYDEMO "MY_DEMO.dn2"
#define F_MAN0 "man0.dn2"
#define F_MAN1 "man1.dn2"
#define F_MAN2 "man2.dn2"
#define F_MAN3 "man3.dn2"
#define F_BACK0 "back0.dn2"
#define F_BACK1 "back1.dn2"
#define F_BACK2 "back2.dn2"
#define F_BACK3 "back3.dn2"
#define F_SOLID0 "solid0.dn2"
#define F_SOLID1 "solid1.dn2"
#define F_SOLID2 "solid2.dn2"
#define F_SOLID3 "solid3.dn2"
#define F_ANIM0 "anim0.dn2"
#define F_ANIM1 "anim1.dn2"
#define F_ANIM2 "anim2.dn2"
#define F_ANIM3 "anim3.dn2"
#define F_ANIM4 "anim4.dn2"
#define F_ANIM5 "anim5.dn2"
#else
#define F_BORDER0 "border.dn3"
#define F_FONT1 "font1.dn3"
#define F_FONT2 "font2.dn3"
#define F_NUMBERS "numbers.dn3"
#define F_OBJECT0 "object0.dn3"
#define F_OBJECT1 "object1.dn3"
#define F_OBJECT2 "object2.dn3"
#define F_USERDEMO "USERDEMO.dn3"
#define F_MYDEMO "MY_DEMO.DN3"
#define F_MAN0 "man0.dn3"
#define F_MAN1 "man1.dn3"
#define F_MAN2 "man2.dn3"
#define F_MAN3 "man3.dn3"
#define F_BACK0 "back0.dn3"
#define F_BACK1 "back1.dn3"
#define F_BACK2 "back2.dn3"
#define F_BACK3 "back3.dn3"
#define F_SOLID0 "solid0.dn3"
#define F_SOLID1 "solid1.dn3"
#define F_SOLID2 "solid2.dn3"
#define F_SOLID3 "solid3.dn3"
#define F_ANIM0 "anim0.dn3"
#define F_ANIM1 "anim1.dn3"
#define F_ANIM2 "anim2.dn3"
#define F_ANIM3 "anim3.dn3"
#define F_ANIM4 "anim4.dn3"
#define F_ANIM5 "anim5.dn3"
#endif
/*@body*/
void g1_e00d(void)
{
    g1_10fb(F_BORDER0, 0x3000, 0x1e00);
    d_7729_ = malloc(0x5dc0);
    d_6b54_ = malloc(0x1194);
    d_a0fb_ = malloc(0x5dca);
    d_a0ef_ = malloc(0x1f41);
    d_5ec4_ = malloc(0x84d1);
    d_637a_ = malloc(0xbb81);
    d_9684_ = malloc(0x4650);
    d_5a0d_ = malloc(0x4650);

    if (!d_6b54_ || !d_5ec4_ || !d_637a_ || !d_a0fb_)
        exit(0);
    if (!d_9684_ || !d_5a0d_)
        exit(0);
    if (!d_9684_ || !d_5a0d_)
        exit(0);
    if (!d_a0ef_)
        exit(0);
    if (!d_7729_)
        exit(0);

    g1_295e(F_FONT1, d_6b54_, 0x7d0);
    g1_295e(F_FONT2, d_6b54_ + 0x7d0, 0x7d0);
    g2_01a9(5);
    g2_1f24();
    g2_0036(5);
    g1_295e(F_NUMBERS, d_a0ef_, 0x1f40);
    g1_295e(F_OBJECT0, d_a0fb_, 0x1f40);
    g1_295e(F_OBJECT1, d_a0fb_ + 0x1f40, 0x1f40);
    g1_295e(F_OBJECT2, d_a0fb_ + 0x3e80, 0x1f40);
    g1_de71(F_USERDEMO, d_9684_);
    g1_dee9(F_MYDEMO, d_5a0d_);
    g1_295e(F_MAN0, d_5ec4_, 0x1e00);
    g1_295e(F_MAN1, d_5ec4_ + 0x1e00, 0x1e00);
    g1_295e(F_MAN2, d_5ec4_ + 0x3c00, 0x1e00);
    g1_295e(F_MAN3, d_5ec4_ + 0x5a00, 0x1e00);
    g1_10fb(F_BACK0, 0, 0x1e00);
    g1_10fb(F_BACK1, 0x600, 0x1e00);
    g1_10fb(F_BACK2, 0xc00, 0x1e00);
    g1_10fb(F_BACK3, 0x1200, 0x1e00);
    g2_01a9(5);
    g2_3114();
    g1_10fb(F_SOLID0, 0x1800, 0x1e00);
    g1_10fb(F_SOLID1, 0x1e00, 0x1e00);
    g2_3af3();
    g2_0036(5);
    g1_10fb(F_SOLID2, 0x2400, 0x1e00);
    g1_10fb(F_SOLID3, 0x2a00, 0x1e00);
    g1_10fb(F_BORDER0, 0x3000, 0x1e00);
    g1_295e(F_ANIM0, d_637a_, 0x1e00);
    g1_295e(F_ANIM1, d_637a_ + 0x1e00, 0x1e00);
    g1_295e(F_ANIM2, d_637a_ + 0x3c00, 0x1e00);
    g1_295e(F_ANIM3, d_637a_ + 0x5a00, 0x1e00);
    g1_295e(F_ANIM4, d_637a_ + 0x7800, 0x1e00);
    g1_295e(F_ANIM5, d_637a_ + 0x9600, 0x1e00);
    g2_01a9(5);
}

