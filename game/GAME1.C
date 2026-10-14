#include <dos.h>
#include <stdio.h>
#include <string.h>
#define DRAW3(n, x, y) (((void (near *)(int, int, int))g1_17f5)((n), (x), (y)))
#include <stdlib.h>
#undef abs
#define G1_4D42_ROW(i) (*((struct G1_4D42_RECORD *)&d_0650[(i) * 6]))
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
#include <alloc.h>
#include <conio.h>
struct g1_0008_row { char field[7]; };
struct reading { int a; int b; int c; };
struct t_cb6d { int state, x, y, marker; };
struct t_52dd { int used, x, y, marker; };
struct row0613 { unsigned char cells[12]; };
struct t_c8eb { int used, value1, value2; };
struct s8 { int a, b, c, d; };
struct t_b63c { int state, x, y, kind; };
struct t_d1cf { int used, x, y; };
struct t_551e { int state, value1, value2; };
struct t_5320 { int f[15]; };
struct g1_376f_record { int state, x, y; };
struct g1_3882_record { int used, x, y; };
struct Record { int reserved; int y; int x; int height; int state; };
struct g1_3e06_record { int state, x, y; };
struct g1_43fa_record { int state, x, y; };
struct g1_4638_entry { int state, position2, position4; };
struct G1_4874_item { int type; int x; int y; int step; };
struct G1_4D42_RECORD { int f0, f1, f2, f3, f4, f5; };
struct g1_4f91_record { int state, x, y, marker; };
struct g1_54e1_record { int state, x, y; };
struct g1_5b0b_record { int state, x, y; };
struct g1_5d6f_record { int active, x, y, state; };
struct g1_5f0c_record { int state, x, y, field3; };
struct g1_6445_record { int state; int x; int y; int kind; int flag8; int flag10; };
struct g1_6afd_record { int x; int y; };
struct g1_6b82_record { int state, x, y; };
struct g1_6e71_record { int state, x, y; };
struct g1_7163_record { int state, x, y; };
struct t_b3d6 { int x, y, used; };
struct g1_7647_record { int state, value1, value2, count; };
struct g1_784b_record { int active, x, y, state; };
struct g1_79d9_record { int state, x, y, flag; };
struct g1_7b68_record { int state, x, y, flag; };
struct t_726b { int x, y; };
struct g1_8069_record { int f0, f2, f4, f6, f8, fa; };
struct g1_8506_record { int state, x, y; };
struct g1_87bf_record { int state, x, y; };
struct g1_892b_record { int offset; int x; unsigned int y; };
struct g1_899e_record { int state, x; unsigned int y; };
struct record { int state; int x; int y; };
struct g1_9698_record { int x; int y; };
struct g1_9757_row { int state, x, y; };
struct g1_9986_record { int state, x, y; };
struct g1_a218_record { int state, x, y; };
struct g1_a30a_record { int used; int x; int y; };
struct g1_a75c_record { int state, x, y, flag; };
struct g1_aac2_record { int state, x, y, kind; };
struct g1_af94_record { int state, x, y; };
struct s_bccb { int a, b, c; };
struct t_b9de { int offset, x, y, alternate; };
struct g1_c1b2_record { int kind; int x; int y; };
struct cell_pair { unsigned int first, second; };

/* data: bss.c */
/* G1 BSS definitions in ascending DN1 address order. The six-byte g1_0c52 struct-return static precedes these globals at 0x4eca. */

int d_4ed0_;
int d_4ed2_;
int d_4ed4_;
int d_4ed6_;
int d_4ed8_;
int d_4eda_[100];
long d_4fa2_[1];
long d_4fa6_[1];
long d_4faa_[1];
long d_4fae_[1];
long d_4fb2_[7];
char d_4fce_[24];
char d_4fe6_[26];
int d_5000_;
int d_5002_;
int d_5004_;
int d_5006_;
char d_5008_[10][11];
/* UNREFERENCED: [0x5076,0x5081), 11 bytes after the 110-byte d_5008_[10][11] table; no accepted symbol starts or direct or based DS references land here. */
char d_5076_[11];
int d_5081_[100];
int d_5149_;
void (far *d_514b_[100])(void);
int d_52db_;
struct t_52dd d_52dd_[5];
int d_5305_;
int d_5307_;
int d_5309_;
char d_530b_;
int d_530c_;
char d_530e_;
char d_530f_;
int d_5310_;
int d_5312_;
int d_5314_;
int d_5316_;
char d_5318_;
int d_5319_;
char d_531b_;
int d_531c_;
int d_531e_;
struct t_5320 d_5320_[17];
struct t_551e d_551e_[7];
int d_5548_;
int d_554a_;
char d_554c_;
int d_554d_;
char d_554f_;
char d_5550_;
char d_5551_;
char d_5552_;
char d_5553_;
char d_5554_;
char d_5555_;
void interrupt far (*d_5556_)(void);
char d_555a_;
char d_555b_;
char d_555c_;
struct g1_6445_record d_555d_[100];
void far *d_5a0d_;
char d_5a11_;
struct g1_6b82_record d_5a12_[100];
char d_5c6a_;
char d_5c6b_;
struct g1_a30a_record d_5c6c_[100];
char far *d_5ec4_;
char d_5ec8_;
struct g1_8069_record d_5ec9_[100];
char d_6379_;
char far *d_637a_;
char d_637e_;
struct G1_4874_item d_637f_[100];
struct g1_376f_record d_669f_[100];
char d_68f7_;
long d_68f8_;
struct g1_87bf_record d_68fc_[100];
char far *d_6b54_;
struct s_bccb d_6b58_[15];
struct g1_3e06_record d_6bb2_[100];
char d_6e0a_;
struct g1_9986_record d_6e0b_[100];
struct g1_899e_record d_7063_[20];
struct g1_6afd_record d_70db_[100];
struct t_726b d_726b_[100];
struct g1_aac2_record d_73fb_[100];
char d_771b_;
int d_771c_[3];
int d_7722_[3];
char d_7728_;
unsigned int far *d_7729_;
char d_772d_;
struct g1_43fa_record d_772e_[100];
char far *d_7986_;
int d_798a_;
struct g1_7647_record d_798c_[100];
struct g1_8506_record d_7cac_[100];
int d_7f04_;
struct g1_892b_record d_7f06_[1000];
int d_9676_[3];
int d_967c_[3];
int d_9682_;
void far *d_9684_;
struct g1_9698_record d_9688_[100];
struct g1_7b68_record d_9818_[100];
int d_9b38_;
struct g1_4638_entry d_9b3a_[100];
int d_9d92_;
int d_9d94_;
int d_9d96_;
char d_9d98_;
struct g1_784b_record d_9d99_[100];
int d_a0b9_;
char far *d_a0bb_;
struct g1_a75c_record d_a0bf_[6];
char far *d_a0ef_;
char d_a0f3_;

extern struct g1_0008_row d_00a1[];
void pascal g2_37b6(char far* a0, int a1, int a2);
extern char d_4fce_[];
extern char d_530b_;
extern char d_531b_;
extern char d_a8d8_;
extern char d_d579_;
void pascal g2_1f5a(int a);
void g1_0e30(int a, int b);
extern char d_a0fa_;
void pascal g2_3d8c(int a0, int a1, int a2);
void pascal g2_148f(int a0);
void pascal g2_2870(int a0, int a1);
void pascal g2_4009(int a0);
void pascal g2_1058(int a0);
void pascal g2_10f0(int a0);
void g1_006f(int a0);
extern char d_554c_;
void pascal g2_12ad(int a0);
extern int d_0099;
extern int d_009b;
extern int d_009d;
extern int d_009f;
extern char d_02fa;
extern int d_4ed4_;
extern char d_5553_;
extern char d_5554_;
extern char d_5555_;
extern char d_555a_;
extern char d_555b_;
extern char d_555c_;
extern char d_5a11_;
extern char d_5c6a_;
extern char d_5c6b_;
extern char d_5ec8_;
extern char d_637e_;
extern char d_68f7_;
extern long d_68f8_;
extern int d_798a_;
extern int d_a0f8_;
extern int d_c295_;
extern int d_cc82_;
void pascal g2_1241(int a0);
void pascal g1_0151(char a0);
extern char d_0094;
extern int d_02fb;
void pascal g2_1a0d(int a0);
void pascal g2_1bb0(int a0);
void g2_0d39(void);
void g2_0d97(void);
void pascal g2_1d40(int a0);
void pascal g2_1ee1(int a0);
char pascal g1_0351(int a0);
void pascal g1_008a(int a0);
extern int d_0095;
extern char d_530e_;
extern char d_cc81_;
extern char d_d135_;
extern char d_d56b_;
void g2_3114(void);
void pascal g2_01a9(int a0);
void g2_32b6(void);
void pascal g2_0036(int a0);
void g2_3fe1(void);
void g2_02f4(void);
void g2_315d(void);
int pascal g2_3d1e(int a0);
void pascal g2_38be(int a0);
void g2_0e19(void);
void g2_062c(void);
void g2_0491(void);
void pascal g1_0008(char a0, int a1, int a2);
extern long d_4fa2_[];
extern char d_5008_[10][11];
void g2_23f7(void);
void pascal g1_0042(int a0);
void pascal g1_0874(volatile int a0, volatile int a1, char far *a2);
extern int d_03a1;
extern char d_6e0a_;
extern char far *d_a0fb_;
void asm_05eb(int a0);
void asm_0424(char far *a0, int a1, int a2);
void g1_0a0e(void);
void asm_05eb(int page);
void asm_0424(char far *bitmap, int row, int offset);
void pascal g2_2789(long a0, int a1, int a2);
extern int d_771c_[];
extern int d_7722_[];
extern int d_9676_[];
extern int d_967c_[];
extern int d_c297_;
extern char d_c68c_;
extern char d_d134_;
extern char d_d13f_;
extern char d_d4c0_;
void pascal g2_01f5(int mode, int far *x, int far *y);
void pascal g2_44f5(int a0);
void pascal g2_01f5(int a0, int far* a1, int far* a2);
void pascal g2_1340(int a0, int a1);
struct reading g1_0c52(int a0);
struct reading g1_0c52(int mode);
extern char d_d138_;
extern char far *d_7986_;
extern char far *d_cc7d_;
extern unsigned int far *d_7729_;
extern char d_0439;
extern char d_043b;
extern char d_0611;
extern char d_0644;
extern char d_d576_;
extern int d_0437;
extern unsigned int far* d_7729_;
void asm_02ad(int a0, int a1);
extern char d_02f4;
extern char d_02f5;
extern char d_02f6;
extern char d_02f7;
extern char d_02f8;
extern char d_02f9;
extern int d_039d;
extern char d_0643;
extern int d_4ed2_;
extern int d_5002_;
extern void interrupt far (*d_5556_)(void);
extern char d_771b_;
extern char d_7728_;
extern char d_772d_;
extern char d_a67d_;
extern char d_a8d9_;
extern char d_c683_;
extern int d_d139_;
extern int d_d13b_;
extern char d_d148_;
extern char far *d_5ec4_;
extern char d_d4bf_;
extern struct t_cb6d d_cb6d_[];
extern int d_0646;
extern char d_530f_;
int g1_367e(int a0, int a1);
void pascal g1_2b86(int a0, int a1, int a2);
char pascal g1_326e(int a0, int a1);
extern struct t_52dd d_52dd_[];
extern int d_051c;
extern int d_0648;
extern char d_6379_;
int g1_3513(int a0, int a1);
unsigned char g1_12ce(void);
char g1_1247(void);
extern char d_043a;
extern int d_060e;
extern char d_0610;
extern char d_0612;
extern char d_9d98_;
extern char d_a0f3_;
extern int d_a679_;
extern unsigned int d_d144_;
extern int d_d247_;
extern struct row0613 d_0613[];
void g1_a53a(void);
void g1_892b(void);
void g1_87bf(void);
void g1_6292(void);
void g1_b1fd(void);
void g1_ba39(void);
void g1_3882(void);
void g1_a3e7(void);
void g1_bdd9(void);
void pascal g1_29d0(int a0, int a1);
void g1_14af(void);
void g1_17f5(int a0, int a1, int a2, int a3);
char g1_143e(void);
void pascal g1_18d4(int a0, int a1, int a2);
char g1_1352(void);
extern struct t_c8eb d_c8eb_[];
extern int d_051e;
extern struct s8 d_d4c3_[];
extern int d_0518;
extern int d_064a;
extern char far *d_a0ef_;
extern struct t_b63c d_b63c_[];
extern int d_0522;
extern char far *d_637a_;
void asm_0424(char far *bitmap, int a0, int a1);
extern struct t_d1cf d_d1cf_[];
extern int d_0520;
extern struct t_551e d_551e_[];
extern int d_051a;
extern int d_0412[];
void pascal g1_3034(int a0, int a1, int a2);
extern struct t_5320 d_5320_[];
extern int d_043e;
extern int d_064c;
extern int d_0440[];
extern int d_0476[];
extern int d_04ac[];
extern int d_04e2[];
extern int abs(int);
void pascal g1_2e64(int a0, int a1);
void pascal g1_0b85(long a0);
extern struct g1_376f_record d_669f_[];
extern int d_043c;
int g1_3714(int a0, int a1);
char pascal g1_3558(int a0, int a1);
void pascal g1_314c(int a0, int a1);
void pascal g1_2a40(register int a0, int a1, int a2);
extern struct g1_3882_record d_a8da_[];
extern int d_0524;
extern int d_d646_[];
void g2_0fc1(void);
int g1_363b(int a0, int a1);
extern struct Record d_c299_[];
extern int d_0526;
extern int d_064e;
int g1_35ee(int a0, int a1, int a2);
extern int d_0528;
extern int d_052a;
extern int d_052c;
void pascal g1_2a40(int a0, int a1, int a2);
void pascal g1_0b85(long value);
void pascal g2_1ffa(char far *bitmap);
void asm_0424(char far *bitmap, int x, int y);
extern struct g1_3e06_record d_6bb2_[];
extern int d_01fe[];
extern int d_053e;
extern int d_4ed8_;
extern int d_052e;
extern int d_a67b_;
extern int d_a67e_;
extern struct g1_43fa_record d_772e_[];
extern int d_0540;
extern struct g1_4638_entry d_9b3a_[];
extern int d_0542;
void asm_0424(char far *bitmap, int a1, int a2);
extern int d_0544;
extern int d_0546[];
extern int d_0576[];
extern int d_05a6;
extern int d_05a8;
extern struct G1_4874_item d_637f_[];
void pascal g1_1b8a(int a0, int a1, int a2);
extern int d_0650[];
extern struct g1_4f91_record d_b6bc_[];
extern int d_05aa;
extern int d_0698[];
extern int d_5081_[];
void pascal g1_4d42(int a0, int a1, int a2);
void pascal g1_2fe7(int a0, int a1);
extern struct g1_54e1_record d_a0ff_[];
extern int d_05ac;
extern int d_06dc;
extern int d_06de;
extern int d_d57e_[];
void pascal g1_5427(int a0, int a1, int a2);
extern int d_0530;
extern int d_0532;
extern int d_0534;
extern int d_0536;
extern int d_0538;
extern int d_053a;
extern int d_053c;
extern int d_b3d4_;
extern void g2_1f9c(void);
extern void asm_0424(char far *bitmap, int row, int offset);
extern struct g1_5b0b_record d_abec_[];
extern int d_05ae;
extern int d_05b0;
extern int d_05b2;
extern int d_4eda_[];
void pascal g1_59cf(int a0, int a1, int a2);
extern struct g1_5d6f_record d_ab32_[];
extern int d_05b4;
void g1_0adc(void);
extern struct g1_5f0c_record d_b0b4_[];
extern int d_05b6;
extern int d_06e0;
extern char d_0436;
extern char d_06e2;
extern int d_d4bd_;
extern int d_d4c1_;
extern int d_d570_;
void g2_16f3(void);
void pascal g1_6183(int a0, int a1, int a2);
extern struct g1_6445_record d_555d_[];
extern int d_05b8;
extern int d_02fd[];
extern int d_034d[];
extern int d_06e3;
extern int d_5310_;
extern char far* d_637a_;
extern int d_abd2_;
extern int d_abd4_[];
extern int d_abe6_;
extern int d_b09c_[];
extern int d_b0ae_;
extern int d_b636_;
extern int d_d249_[];
void asm_0424(char far* a0, int a1, int a2);
extern struct g1_6afd_record d_70db_[];
extern int d_05ba;
extern int d_06e5;
void asm_0315(int x, int row, int source);
char pascal g1_326e(int x, int y);
extern struct g1_6b82_record d_5a12_[];
extern int d_05bc;
extern int d_06e7;
void g2_1534(void);
void g1_0acc(void);
extern struct g1_6e71_record d_d261_[];
extern int d_05be;
extern int d_06e9;
extern int d_06eb;
extern struct g1_7163_record d_c01e_[];
extern int d_05c0;
void g2_15c9(void);
extern int d_b62e_;
extern int d_b632_;
extern int d_c281_;
extern int d_d136_;
extern int d_d155_;
extern int d_d4b9_;
extern int d_d4bb_;
extern struct t_b3d6 d_b3d6_[];
extern int d_05c2;
extern int d_06ed;
extern char pascal g1_326e(int a0, int a1);
extern int g1_3513(int a0, int a1);
extern void pascal g1_0042(int a0);
extern int d_05c4;
extern struct g1_7647_record d_798c_[];
void pascal g1_75b9(int a0, int a1, int a2);
extern struct g1_784b_record d_9d99_[];
extern int d_05c6;
char pascal g1_3558(int a0, register int a1);
extern int d_05c8;
extern struct g1_79d9_record d_a357_[];
extern struct g1_7b68_record d_9818_[];
extern int d_05ca;
extern int d_05cc;
extern int d_06ef;
extern struct t_726b d_726b_[];
void asm_0424(char far *bitmap, int row, int column);
void pascal g1_0042(int value);
extern struct g1_8069_record d_5ec9_[];
extern int d_05ce;
extern int d_06f1;
void pascal g1_7f4a(int a0, int a1, int a2);
void pascal g1_7dff(int a0, int a1, int a2);
extern struct g1_8506_record d_7cac_[];
extern int d_05d0;
extern int d_06f3;
extern struct g1_87bf_record d_68fc_[];
extern int d_05d2;
extern int d_4ed6_;
extern struct g1_892b_record d_7f06_[];
extern int d_05d4;
extern struct g1_899e_record d_7063_[];
extern int d_05d6;
extern int d_06f5;
void g2_165e(void);
extern struct record d_c691_[];
extern int d_05d8;
extern int d_531c_;
extern int d_06f7;
extern int d_c68d_;
extern int d_c68f_;
extern int d_c8e9_;
extern int d_d56e_;
extern int d_d572_;
extern struct g1_9698_record d_9688_[];
extern int d_05da;
extern struct g1_9757_row d_c915_[];
extern int d_05dc;
extern int d_06f9;
extern struct g1_9986_record d_6e0b_[];
extern int d_05de;
extern int d_06fb;
extern char d_06fd;
extern int d_c279_;
extern int d_c27b_;
extern int d_c28b_;
extern int d_c28d_;
extern int d_c684_;
extern int d_c686_;
extern int d_c68a_;
void g2_18b8(void);
void pascal g1_9bb5(int a0, int a1, int a2);
extern int d_c688_;
extern struct g1_a218_record d_ae44_[];
extern int d_05e0;
extern int d_05e2[];
extern struct g1_a30a_record d_5c6c_[];
extern int d_5004_;
extern int d_06fe;
extern int d_7f04_;
extern int d_9d96_;
extern int d_a0b9_;
void g2_1821(void);
void g2_3b79(void);
void g2_1a82(void);
extern int d_5000_;
extern int d_5149_;
extern int d_52db_;
extern int d_5307_;
extern int d_d13d_;
extern int d_d140_;
void g2_178a(void);
extern int d_5316_;
extern int d_d574_;
extern int d_d577_;
void pascal g1_2b86(register int a0, int a1, int a2);
extern struct g1_a75c_record d_a0bf_[];
extern int d_5309_;
extern int d_530c_;
extern int d_d149_[];
extern int d_d14b_;
extern int d_d14d_;
extern int d_d57a_;
extern struct g1_aac2_record d_73fb_[];
extern int d_0600;
extern int d_5312_;
void pascal g1_aa1b(int a0, int a1, int a2);
extern struct g1_af94_record d_a680_[];
extern int d_05fe;
extern int d_0700;
void pascal g1_af06(int a0, int a1, int a2);
extern char far *d_0ba1[];
void pascal g2_37b6(char far *a0, int a1, int a2);
void asm_05f7(int page);
extern int d_9d92_;
extern int d_9d94_;
extern int d_a677_;
void g1_b118(void);
void g2_0f2a(void);
extern int d_0602;
extern int d_0604;
extern int d_0606;
extern int d_0608;
extern int d_060a;
extern int d_060c;
extern int d_0702[];
extern int d_554a_;
extern int d_b630_;
extern int d_b634_;
extern int d_b9dc_;
extern int d_c283_;
extern int d_c293_;
extern int d_d142_;
extern int d_d56c_;
void pascal g1_b292(int a0, int a1, int a2);
extern int d_d146_;
extern int d_071a;
extern int d_071c;
extern int d_071e;
extern int d_5314_;
extern int d_c276_;
extern int d_c289_;
extern int d_c681_;
void pascal g1_b926(int a0, int a1, int a2);
extern char d_554f_;
extern char d_5550_;
extern char d_5551_;
extern char d_5552_;
extern struct s_bccb d_6b58_[];
extern int d_d70e_;
void pascal g1_bb9f(void);
extern int d_0720;
extern int d_5319_;
extern int d_5548_;
extern struct t_b9de d_d157_[];
extern struct t_b9de d_b9de_[];
void g2_0e98(void);
void g2_1b19(void);
extern struct g1_c1b2_record d_cc84_[];
extern int d_531e_;
extern void (far *d_514b_[])(void);
extern int d_554d_;
extern int d_0100[];
extern int d_5006_;
extern int d_d57c_;
void g1_c1b2(void);
void g1_a30a(void);
void g1_9986(void);
void g1_9757(void);
void g1_79d9(void);
void g1_7b68(void);
void g1_6b82(void);
void g1_7163(void);
void g1_784b(void);
void g1_c0c7(void);
void g1_bccb(void);
void g1_b595(void);
void g1_af94(void);
void g1_aac2(void);
void g1_a75c(void);
void g1_a6f4(void);
void g1_5887(void);
void g1_a218(void);
void g1_a125(void);
void g1_a032(void);
void g1_9698(void);
void g1_8ec1(void);
void g1_8b5b(void);
void g1_899e(void);
void g1_8506(void);
void g1_8069(void);
void g1_7cfa(void);
void g1_573d(void);
void g1_7647(void);
void g1_74c2(void);
void g1_73d3(void);
void g1_6e71(void);
void g1_6947(void);
void g1_6445(void);
void g1_5f0c(void);
void g1_5d6f(void);
void g1_5b0b(void);
void g1_54e1(void);
void g1_4f91(void);
void g1_4874(void);
void g1_4638(void);
void g1_43fa(void);
void g1_42b8(void);
void g1_3e06(void);
void g1_3cbc(void);
void g1_3a98(void);
void g1_376f(void);
void pascal g1_c243(void (far *a0)(void));
extern int d_040e;
extern char d_c278_;
extern int d_0410;
extern void far *d_5a0d_;
extern char far *d_6b54_;
extern void far *d_9684_;
void g2_1f24(void);
void g2_3af3(void);
void pascal g1_10fb(char far *a0, int a1, int a2);
void g1_295e(char far *a0, void far *a1, unsigned int a2);
void g1_de71(char far *a0, char far *a1);
void g1_dee9(char far *a0, char far *a1);
extern char far *d_0b47[];
void pascal g1_1b51(void);
void g1_de26(char far* a0);
void pascal g1_10fb(char far* a0, int a1, int a2);
void pascal g1_2a1d(void);
void pascal g1_c287(unsigned int a0);
extern char d_0098;
extern char d_03a3;
extern char far *d_03a4[];
extern char d_5318_;
extern int d_9682_;
extern int d_9b38_;
extern char far* d_a0fb_;
void pascal g2_219d(char a0);
void pascal g2_0009(int a0);
void pascal g2_1ffa(char far* a0);
void g2_2ab9(void);
void g2_1454(void);
void g2_29a2(void);
void pascal g1_e3e0(char far *a0);
extern int d_4ed0_;
void g2_3568(void);
void g2_44a5(void);
void pascal g2_452b(int a0);
void g2_36c1(void);
void g2_340f(void);
void g2_4334(void);
void g2_4394(void);
void g2_43f5(void);
void g2_4444(void);
void g2_2473(void);
void pascal g1_e92e(int a0);
void g2_25cd(void);
void asm_0258(int page);
void g2_2104(char far *filename);
void g2_24b1(void);
void pascal g2_3980(char far *filename);
void pascal g2_3a38(char far *filename);
void pascal g2_3252(char far *filename);
void pascal g2_365d(char far *filename);
void pascal g2_33ab(char far *filename);
void pascal g2_3504(char far *filename);
void pascal g2_30b0(char far *filename);
void interrupt g1_15f4(void);
void g2_1e97(void);
void g1_e83e(void);
void g1_e00d(void);
void pascal g1_e89d(char far *filename);
extern int d_039f;
extern char far* d_03a4[];
extern int d_040c;
extern int d_0b9f;
extern int d_5305_;
extern void far* d_5a0d_;
extern void far* d_9684_;
void g2_3f68(void);
void g2_3cdc(void);
void asm_05f7(int a0);
void pascal g2_11f2(int a0);
void g2_14e6(void);
void g2_3c9a(void);
void g2_1f9c(void);
void g1_290f(void);
void g1_10a5(void);
void g1_1e77(void);
void g1_2a93(void);
void g1_32a5(void);
void g1_2f4c(void);
void g1_2eb1(void);
void g1_1933(void);
void g1_1bf6(void);
void g1_30c9(void);
void g1_2bd9(void);
void g1_6afd(void);
void g1_e947(void);
void g1_0928(void);
void g1_e655(void);
void pascal g1_e3e0(char far* text);
void pascal g1_037e(int a0);
void g1_ecf4(void);
void g2_205f(char far *filename);
void g2_1e1b(void);
void g2_2f04(void);
void g2_1319(void);
void g1_df57(char far *filename, void far *buffer);
void g1_dfb2(char far *filename, void far *buffer);
void pascal g1_e8ed(char far *filename);
extern char d_0b46;
void g2_3bd7(void);
void g2_3c38(void);
int pascal g1_049f(int a0);
unsigned char pascal g1_0126(int a0);
void g1_fc9c(void);
void pascal g1_ec3d(void);
void pascal g1_fd15(void);
void pascal g1_fc85(void);

/* data: prefix.c */
/* G1 initialised data, DGROUP 0x0094..0x03a3, in definition order (rule DATA-LAYOUT).
   Proven with tail.c by `python tools/tubuild.py G1_TEXT --data`. */
char d_0094 = 0x00;

int d_0095 = 0;

char d_0097 = 0x00;

char d_0098 = 0x00;

int d_0099 = 16;

int d_009b = 64;

int d_009d = 0;

int d_009f = 0;

struct g1_0008_row d_00a1[85] = {
    { 0x4e, 0x55, 0x4c, 0x4c, 0x00, 0x00, 0x00 },
    { 0x45, 0x53, 0x43, 0x00, 0x00, 0x00, 0x00 },
    { 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x42, 0x4b, 0x53, 0x50, 0x00, 0x00, 0x00 },
    { 0x54, 0x41, 0x42, 0x00, 0x00, 0x00, 0x00 },
    { 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x45, 0x4e, 0x54, 0x52, 0x00, 0x00, 0x00 },
    { 0x43, 0x54, 0x52, 0x4c, 0x00, 0x00, 0x00 },
    { 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4c, 0x53, 0x48, 0x46, 0x54, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x52, 0x53, 0x48, 0x46, 0x54, 0x00, 0x00 },
    { 0x50, 0x52, 0x54, 0x53, 0x43, 0x00, 0x00 },
    { 0x41, 0x4c, 0x54, 0x00, 0x00, 0x00, 0x00 },
    { 0x53, 0x50, 0x41, 0x43, 0x45, 0x00, 0x00 },
    { 0x43, 0x41, 0x50, 0x4c, 0x4b, 0x00, 0x00 },
    { 0x46, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x46, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00 },
    { 0x4e, 0x55, 0x4d, 0x4c, 0x4b, 0x00, 0x00 },
    { 0x53, 0x43, 0x52, 0x4c, 0x4b, 0x00, 0x00 },
    { 0x48, 0x4f, 0x4d, 0x45, 0x00, 0x00, 0x00 },
    { 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x47, 0x55, 0x50, 0x00, 0x00, 0x00 },
    { 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x45, 0x4e, 0x44, 0x00, 0x00, 0x00, 0x00 },
    { 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0x47, 0x44, 0x4e, 0x00, 0x00, 0x00 },
    { 0x49, 0x4e, 0x53, 0x00, 0x00, 0x00, 0x00 },
    { 0x44, 0x45, 0x4c, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

char d_02f4 = 0x48;

char d_02f5 = 0x50;

char d_02f6 = 0x4b;

char d_02f7 = 0x4d;

char d_02f8 = 0x38;

char d_02f9 = 0x1d;

char d_02fa = 0x00;

int d_02fb = 0;

int d_02fd[40] = {
    0, -1, -1, -2, -2, -2, -1, -1,
    0, 1, 1, 2, 2, 2, 1, 1,
    1, 1, 1, 1, 1, 2, 1, 1,
    0, -1, -1, -2, -2, -2, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

int d_034d[40] = {
    1, 1, 1, 1, 0, -1, -1, -1,
    -2, -1, -1, -1, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 0, -1, -1,
    -2, -1, -1, -1, 0, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0
};

int d_039d = 0;

int d_039f = 0;

int d_03a1 = 0;

char d_03a3 = 0x00;

/* g1_0008 */
void pascal g1_0008(char a0, int a1, int a2)
{
    char text[2];

    text[0] = d_00a1[(unsigned char)a0].field[0];
    text[1] = 0;
    g2_37b6(text, a1, a2);
}

/* g1_0042 */
void pascal g1_0042(int a0)
{
    disable();
    if (d_4fce_[a0] >= d_d579_) {
        d_d579_ = d_4fce_[a0];
        d_530b_ = 1;
        d_531b_ = a0;
        d_a8d8_ = 0;
    }
    enable();
}

/* g1_006f */
void g1_006f(int a)
{
    g2_1f5a(a);
    g1_0e30(1, a);
}

/* g1_008a */
void pascal g1_008a(register int a0)
{
    g2_3d8c(a0, 2, 4);
    outport(0x3ce, 5);
    g2_148f(a0);
    delay(100);
    do {
        g2_2870(a0 + 0x18, 0x0c);
        if (d_a0fa_ == 0x24) {
            g1_006f(a0);
            return;
        }
        if (d_a0fa_ == 0x25) {
            g2_4009(a0);
            return;
        }
        if (d_a0fa_ == 0x1f) {
            g2_1058(a0);
            return;
        }
        if (d_a0fa_ == 0x23) {
            g2_10f0(a0);
            return;
        }
    } while (d_a0fa_ != 0x1c && d_a0fa_ != 1 && d_a0fa_ != 0x39);
}

/* g1_0126 */
unsigned char pascal g1_0126(int a0)
{
    g2_12ad(a0);
    if (d_a0fa_ >= 2 && d_a0fa_ <= 10) {
        d_554c_ = d_a0fa_ + 0x2f;
        return 1;
    }
    return 0;
}

/* g1_0151 */
void pascal g1_0151(char a0)
{
    FILE *stream;
    char *name;
#if EPISODE == 1
    name = "saved .dn1";
#elif EPISODE == 2
    name = "saved .dn2";
#else
    name = "saved .dn3";
#endif
    name[5] = a0;
    stream = fopen(name, "wb");
    putw(d_009d, stream);
    putw(d_009f, stream);
    putw(d_0099, stream);
    putw(d_009b, stream);
    putw(d_02fa, stream);
    putw(d_c295_, stream);
    putw(d_798a_, stream);
    putw(d_a0f8_, stream);
    putw(d_4ed4_, stream);
    putw(d_cc82_, stream);
    putw(d_5a11_, stream);
    putw(d_5c6b_, stream);
    putw(d_5554_, stream);
    putw(d_637e_, stream);
    putw(d_5ec8_, stream);
    putw(d_555a_, stream);
    putw(d_555b_, stream);
    putw(d_68f7_, stream);
    putw(d_555c_, stream);
    putw(d_5553_, stream);
    putw(d_5555_, stream);
    putw(d_5c6a_, stream);
    fprintf(stream, "%ld\n", d_68f8_);
    fclose(stream);
}

/* g1_0351 */
char pascal g1_0351(int a0)
{
    g2_1241(a0);
    if (d_a0fa_ >= 2 && d_a0fa_ <= 10) {
        g1_0151(d_a0fa_ + 0x2f);
        return 1;
    }
    return 0;
}

/* g1_037e */
void pascal g1_037e(register int a0)
{
    outport(0x3ce, 0x105);
    for (;;) {
        g2_3d8c(a0, 1, 5);
        outport(0x3ce, 5);
        g2_1a0d(a0);
        delay(100);
        for (;;) {
            g2_2870(0x1a, 0x0c);
            if (d_a0fa_ == 1 || d_a0fa_ == 0x39 || d_a0fa_ == 0x1c) {
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x1f) {
                if (d_02fa % 2 == 0) {
                    g2_1bb0(a0);
                    d_02fb = 0;
                    return;
                }
                if (g1_0351(a0)) {
                    g2_0d39();
                    d_02fb = 0;
                    return;
                }
                g2_0d97();
                break;
            }
            if (d_a0fa_ == 0x23) {
                g2_1d40(a0);
                while (d_a0fa_ == 0x23)
                    ;
                g2_2870(a0 + 0x18, 0x14);
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x17) {
                g2_1ee1(a0);
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 1 || d_a0fa_ == 0x10 || d_a0fa_ == 0x39) {
                d_a0fa_ = 0;
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x22) {
                g1_008a(a0);
                d_02fb = 0;
                return;
            }
            if (d_a0fa_ == 0x44) {
                d_0094 = 1;
                d_02fb = 0;
                return;
            }
        }
    }
}

/* g1_049f */
int pascal g1_049f(register int a0)
{
    unsigned long ticks;
    unsigned char button1;
    unsigned char button2;

    ticks = 0;
    button1 = inportb(0x201) & 0x10;
    button2 = inportb(0x201) & 0x20;
    if (d_d56b_ == 0) {
        button1 = 1;
        button2 = 1;
    }
    g2_3114();

    for (;;) {
        g2_01a9(20);
        g2_32b6();
        g2_0036(20);
        ticks = 0;
        d_a0fa_ = 0;
        while (d_a0fa_ == 0 && button1 != 0 && button2 != 0) {
            if (d_d56b_ != 0) {
                button1 = inportb(0x201) & 0x10;
                button2 = inportb(0x201) & 0x20;
            }
            if (d_02fb % 2 != 0) {
                ++ticks;
                if (ticks == 0x16e360UL) {
                    d_a0fa_ = 0;
                    return 5;
                }
                if (ticks == 0xf4240UL) {
                    g2_01a9(20);
                    g2_3fe1();
                    g2_02f4();
                    g2_0036(20);
                }
                if (ticks == 0x7a120UL) {
                    g2_01a9(20);
                    g2_315d();
                    g2_0036(20);
                }
            }
        }

        if ((d_a0fa_ == 0x10 || d_a0fa_ == 1) && ticks < 0x7a120UL) {
            while (d_a0fa_ == 0x10) {
            }
            if (g2_3d1e(7) != 0)
                return 0;
        }
        ticks = 0;
        outport(0x3ce, 0x105);
        for (;;) {
            while (button1 == 0 || button2 == 0) {
                if (d_d56b_ != 0) {
                    button1 = inportb(0x201) & 0x10;
                    button2 = inportb(0x201) & 0x20;
                }
            }
            ticks = 0;
            g2_3d8c(a0, 2, 8);
            outport(0x3ce, 5);
            g2_38be(a0);
            g2_0036(15);
            L_064b:
            d_a0fa_ = 0;
            goto L_067b;

            L_0652:
            ++ticks;
            if (ticks <= 0xbbaee0UL)
                goto L_067b;
            d_a0fa_ = 0;
            g2_01a9(20);
            return 5;

            L_067b:
            if (d_d56b_ != 0) {
                button1 = inportb(0x201) & 0x10;
                button2 = inportb(0x201) & 0x20;
            }
            if (d_a0fa_ == 0 && button1 != 0 && button2 != 0)
                goto L_0652;
            if (d_a0fa_ == 0x1f || d_a0fa_ == 0x39 || d_a0fa_ == 0x1c)
                return 1;
            if (button1 == 0 || button2 == 0) {
                while (button1 == 0 || button2 == 0) {
                    if (d_d56b_ != 0) {
                        button1 = inportb(0x201) & 0x10;
                        button2 = inportb(0x201) & 0x20;
                    }
                }
                if (d_cc81_ == 0 && d_d56b_ != 0)
                    g1_006f(a0);
                if (d_cc81_ == 0)
                    continue;
                g2_01a9(20);
                return 1;
            }

            if (d_a0fa_ == 0xc0 && d_d135_ != 0 && d_0095 != 0)
                return 4;
            if (d_a0fa_ == 0x2e) {
                while (d_a0fa_ == 0x2e) {
                }
                g2_01a9(15);
                g2_315d();
                g2_0036(15);
                d_a0fa_ = 0;
                while (d_a0fa_ == 0) {
                }
            } else if (d_a0fa_ == 0x23) {
                g2_1d40(a0);
                while (d_a0fa_ == 0x23) {
                }
                g2_2870(a0 + 0x18, 20);
            } else if (d_a0fa_ == 0x2f) {
                if (d_530e_ != 0) {
                    g2_0e19();
                } else {
                    return 2;
                }
            } else if (d_a0fa_ == 0x13) {
                return 3;
            } else if (d_a0fa_ == 0x19) {
                return 5;
            } else if (d_a0fa_ == 0x17) {
                g2_01a9(15);
                g2_062c();
            } else if (d_a0fa_ == 1 || d_a0fa_ == 0x10) {
                while (d_a0fa_ == 0x10) {
                }
                if (g2_3d1e(7) != 0)
                    return 0;
            } else if (d_a0fa_ == 0x22) {
                g1_008a(a0);
            } else if (d_a0fa_ == 0x14) {
                break;
            } else if (d_a0fa_ == 0x18) {
                g2_01a9(15);
                g2_3fe1();
                g2_02f4();
                g2_2870(0x27, 0x18);
                g2_3114();
                g2_0491();
                g2_2870(0x27, 0x18);
            } else {
                goto L_064b;
            }
            g2_01a9(15);
            g2_32b6();
        }
    }
}

/* g1_0874 */
void pascal g1_0874(volatile int a2, volatile int a1, char far *a0)
{
    register int i = 0;

    d_a0fa_ = 0;
    for (;;) {
        g2_2870(a2 + i + 1, a1);
        if (d_a0fa_ == 0x1c) {
            a0[i] = 0;
            return;
        }
        if (d_a0fa_ == 0x0e) {
            if (i > 0)
                --i;
        } else if (i < 10) {
            if ((d_a0fa_ >= 0x10 && d_a0fa_ <= 0x19) ||
                (d_a0fa_ >= 0x2c && d_a0fa_ <= 0x32) ||
                (d_a0fa_ >= 0x1e && d_a0fa_ <= 0x26)) {
                a0[i] = d_00a1[(unsigned char)d_a0fa_].field[0];
                ++i;
                g1_0008(d_a0fa_, a2 + i, a1);
            } else if (d_a0fa_ == 0x39) {
                a0[i] = ' ';
                ++i;
            }
        }
    }
}

/* g1_0928 */
void g1_0928(void)
{
    register int entry;
    register int slot;

    slot = 0;
    goto test;
    do {
        if ((unsigned long)d_4fa2_[slot] < (unsigned long)d_68f8_) {
            entry = 10;
            while (entry > slot) {
                d_4fa2_[entry] = d_4fa2_[entry - 1];
                strcpy(d_5008_[entry], d_5008_[entry - 1]);
                --entry;
            }
            d_5008_[slot][0] = 0;
            d_4fa2_[slot] = d_68f8_;
            g2_3d8c(7, 2, 5);
            g1_0042(0x18);
            g2_23f7();
            while (d_a0fa_ == 0x15) {
            }
            g1_0874(0x0e, 0x0b, d_5008_[slot]);
            return;
        }
        ++slot;
test:
        ;
    } while (slot < 8);
}

/* g1_0a0e */
void g1_0a0e(void)
{
    register int i;
    for (i = 0; i < 8; ++i) {
        asm_05eb(d_6e0a_);
        asm_0424(d_a0fb_ + 0x26c0, i + 0x1e, 0x3c);
        if (d_4ed4_ - 1 > i)
            asm_0424(d_a0fb_ + 0x2620, i + 0x1e, 0x3c);
        asm_05eb(!d_6e0a_);
        asm_0424(d_a0fb_ + 0x26c0, i + 0x1e, 0x3c);
        if (d_4ed4_ - 1 > i)
            asm_0424(d_a0fb_ + 0x2620, i + 0x1e, 0x3c);
        d_03a1 = 0;
    }
}

/* g1_0acc */
void g1_0acc(void)
{
    if (d_4ed4_ < 9)
        d_4ed4_++;
    g1_0a0e();
}

/* g1_0adc */
void g1_0adc(void)
{
    register int si;

    for (si = 0; si < d_c295_; si++) {
        asm_05eb(d_6e0a_);
        asm_0424(d_a0fb_ + 0x1ae0, 0x21, 0x60);
        asm_0424(d_a0fb_ + 0x500, si * 2 + 0x1e, 0x6c);
        asm_05eb(!d_6e0a_);
        asm_0424(d_a0fb_ + 0x1ae0, 0x21, 0x60);
        asm_0424(d_a0fb_ + 0x500, si * 2 + 0x1e, 0x6c);
    }
}

/* g1_0b85 */
void pascal g1_0b85(long value)
{
    outport(0x3ce, 5);
    d_68f8_ += value;
    if (d_68f8_ == 0L) {
        asm_05eb(0);
        g2_2789(0x00989680L, 0x25, 3);
        g2_2789(0L, 0x1e, 3);
        asm_05eb(1);
        g2_2789(0x00989680L, 0x25, 3);
        g2_2789(0L, 0x1e, 3);
    }
    asm_05eb(0);
    g2_2789(d_68f8_, 0x25, 3);
    asm_05eb(1);
    g2_2789(d_68f8_, 0x25, 3);
}

/* g1_0c52 */
struct reading g1_0c52(register int mode)
{
    int x;
    int y;
    int xdir;
    int ydir;
    struct reading state;
    register int sample;

    x = 0;
    y = 0;
    xdir = 0;
    ydir = 0;

    g2_01f5(mode, &x, &y);
    if ((x > 500) | (y > 500)) {
        x = d_9676_[mode] + 1;
        y = d_967c_[mode] + 1;
    }

    if (d_771c_[mode] < x)
        xdir = 1;
    else if (d_9676_[mode] > x)
        xdir = -1;

    if (d_7722_[mode] < y)
        ydir = 1;
    else if (d_967c_[mode] > y)
        ydir = -1;

    switch (ydir * 3 + xdir) {
    case -4: d_c68c_ = 1; d_d13f_ = 1; d_d4c0_ = 0; d_d134_ = 0; break;
    case -3: d_c68c_ = 1; d_d13f_ = 0; d_d4c0_ = 0; d_d134_ = 0; break;
    case -2: d_c68c_ = 1; d_d13f_ = 0; d_d4c0_ = 1; d_d134_ = 0; break;
    case -1: d_c68c_ = 0; d_d13f_ = 1; d_d4c0_ = 0; d_d134_ = 0; break;
    case  0: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 0; d_d134_ = 0; break;
    case  1: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 1; d_d134_ = 0; break;
    case  2: d_c68c_ = 0; d_d13f_ = 1; d_d4c0_ = 0; d_d134_ = 1; break;
    case  3: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 0; d_d134_ = 1; break;
    case  4: d_c68c_ = 0; d_d13f_ = 0; d_d4c0_ = 1; d_d134_ = 1; break;
    }

    sample = inportb(0x201);
    if (mode == 1) {
        state.b = ((sample & 0x10) == 0) ? 1 : 0;
        state.c = ((sample & 0x20) == 0) ? 1 : 0;
    } else {
        state.b = ((sample & 0x40) == 0) ? 1 : 0;
        state.c = ((sample & 0x80) == 0) ? 1 : 0;
    }
    if (d_c297_ != 0) {
        sample = state.b;
        state.b = state.c;
        state.c = sample;
    }

    return state;
}

/* data: tail.c */
/* G1 initialised data, DGROUP 0x03a4..0x0721.  Defined after g1_0151 and before g1_0e30 so the
   strings of the level-file table d_03a4 land at their original place in the literal pool. */
#if EPISODE == 1

char far *d_03a4[21] = {

    "worldal1.dn1",
    "worldal2.dn1",
    "worldal3.dn1",
    "worldal2.dn1",
    "worldal4.dn1",
    "worldal2.dn1",
    "worldal5.dn1",
    "worldal2.dn1",
    "worldal6.dn1",
    "worldal2.dn1",
    "worldal7.dn1",
    "worldal2.dn1",
    "worldal8.dn1",
    "worldal2.dn1",
    "worldal9.dn1",
    "worldal2.dn1",
    "worldala.dn1",
    "worldal2.dn1",
    "worldalb.dn1",
    "worldal2.dn1",
    "worldalc.dn1"

};

#elif EPISODE == 2

char far *d_03a4[21] = {

    "worldal1.dn2",
    "worldal2.dn2",
    "worldal3.dn2",
    "worldal2.dn2",
    "worldal4.dn2",
    "worldal2.dn2",
    "worldal5.dn2",
    "worldal2.dn2",
    "worldal6.dn2",
    "worldal2.dn2",
    "worldal7.dn2",
    "worldal2.dn2",
    "worldal8.dn2",
    "worldal2.dn2",
    "worldal9.dn2",
    "worldal2.dn2",
    "worldala.dn2",
    "worldal2.dn2",
    "worldalb.dn2",
    "worldal2.dn2",
    "worldalc.dn2"

};

#elif EPISODE == 3

char far *d_03a4[21] = {

    "worldal1.dn3",
    "worldal2.dn3",
    "worldal3.dn3",
    "worldal2.dn3",
    "worldal4.dn3",
    "worldal2.dn3",
    "worldal5.dn3",
    "worldal2.dn3",
    "worldal6.dn3",
    "worldal2.dn3",
    "worldal7.dn3",
    "worldal2.dn3",
    "worldal8.dn3",
    "worldal2.dn3",
    "worldal9.dn3",
    "worldal2.dn3",
    "worldala.dn3",
    "worldal2.dn3",
    "worldalb.dn3",
    "worldal2.dn3",
    "worldalc.dn3"

};

#endif

int d_03f8[10] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0
};

int d_040c = 0;

int d_040e = 0;

int d_0410 = 0;

int d_0412[18] = {
    -64, -32, -16, -8, 0, 8, 16, 16,
    32, 32, 32, 64, 64, 128, 128, 128,
    128, 128
};

char d_0436 = 0x00;

int d_0437 = 0;

char d_0439 = 0x00;

char d_043a = 0x04;

char d_043b = 0x00;

int d_043c = 0;

int d_043e = 10;

int d_0440[27] = {
    0, 0, -71, 0, -59, 0, -45, 0,
    -33, -1, -25, 0, -10, 0, -1, 0,
    13, 0, 16, -1, 19, 0, 31, 0,
    54, 0, 66
};

int d_0476[27] = {
    0, 0, -50, 1, -47, 0, -33, 1,
    -23, 0, -10, 1, 8, 0, 21, 0,
    33, 0, 46, 1, 19, 0, 29, 0,
    38, 0, 50
};

int d_04ac[27] = {
    0, 0, 1, -1, 8, -1, 17, -1,
    29, -1, 32, -1, 45, -1, 51, -1,
    65, -1, 79, -1, 79, -1, 99, -1,
    99, 0, 99
};

int d_04e2[27] = {
    0, 0, 1, 1, 3, 1, 7, 1,
    9, 1, 12, 1, 15, 1, 21, 1,
    25, 1, 29, 1, 36, 1, 40, 1,
    40, 0, 40
};

int d_0518 = 19;

int d_051a = 4;

int d_051c = 3;

int d_051e = 5;

int d_0520 = 10;

int d_0522 = 8;

int d_0524 = 0;

int d_0526 = 0;

int d_0528 = 0;

int d_052a = 0;

int d_052c = 0;

int d_052e = 0;

int d_0530 = 0;

int d_0532 = 0;

int d_0534 = 0;

int d_0536 = 0;

int d_0538 = 0;

int d_053a = 0;

int d_053c = 0;

int d_053e = 0;

int d_0540 = 0;

int d_0542 = 0;

int d_0544 = 0;

int d_0546[24] = {
    0, -64, 1, -32, 1, -16, 0, -1,
    0, 0, 1, 12, 1, 24, 0, 46,
    1, 128, 0, 128, 1, 256, 0, 0
};

int d_0576[24] = {
    0, -64, -1, -32, -1, -16, 0, -1,
    0, 0, -1, 12, -1, 24, 0, 46,
    -1, 128, -1, 128, -1, 256, 0, 0
};

int d_05a6 = 0;

int d_05a8 = 0;

int d_05aa = 0;

int d_05ac = 0;

int d_05ae = 0;

int d_05b0 = 0;

int d_05b2 = 0;

int d_05b4 = 0;

int d_05b6 = 0;

int d_05b8 = 0;

int d_05ba = 0;

int d_05bc = 0;

int d_05be = 0;

int d_05c0 = 0;

int d_05c2 = 0;

int d_05c4 = 0;

int d_05c6 = 0;

int d_05c8 = 0;

int d_05ca = 0;

int d_05cc = 0;

int d_05ce = 0;

int d_05d0 = 0;

int d_05d2 = 0;

int d_05d4 = 0;

int d_05d6 = 0;

int d_05d8 = 0;

int d_05da = 0;

int d_05dc = 0;

int d_05de = 0;

int d_05e0 = 0;

int d_05e2[14] = {
    128, 96, 64, 32, 8, 4, 1, -1,
    -4, -8, -32, -64, -96, -128
};

int d_05fe = 0;

int d_0600 = 0;

int d_0602 = 0;

int d_0604 = 0;

int d_0606 = 0;

int d_0608 = 0;

int d_060a = 0;

int d_060c = 10;

int d_060e = 0;

char d_0610 = 0x01;

char d_0611 = 0x00;

char d_0612 = 0x00;

struct row0613 d_0613[2] = {
    { { 0x0d, 0x0b, 0x09, 0x07, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { { 0x0f, 0x0d, 0x0b, 0x09, 0x07, 0x05, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00 } }
};

int d_062b[12] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};

char d_0643 = 0x00;

char d_0644 = 0x00;

/* not referenced by any code */
char d_0645 = 0x50;

int d_0646 = 0;

int d_0648 = 0;

int d_064a = 0;

int d_064c = 0;

int d_064e = 0;

int d_0650[36] = {
    -1, -1, 160, 320, 480, 640, -1, -1,
    160, 320, 800, 960, 1120, 1280, 1440, 1600,
    1760, 1920, -1, -1, 2080, 2240, 2400, 2560,
    -1, -1, 2080, 2240, 2720, 2880, 3040, 3200,
    3360, 3520, 3680, 3840
};

int d_0698[34] = {
    1, 256, 2, 128, 0, 64, 1, 32,
    0, 16, 1, 8, 0, 4, 1, 2,
    0, 1, 1, -1, 0, -2, 1, -4,
    0, -8, 1, -16, 0, -32, 1, -64,
    0, -128
};

int d_06dc = 0;

int d_06de = 0;

int d_06e0 = 0;

char d_06e2 = 0x00;

int d_06e3 = 0;

int d_06e5 = 0;

int d_06e7 = 0;

int d_06e9 = 0;

int d_06eb = 640;

int d_06ed = 0;

int d_06ef = 0;

int d_06f1 = 0;

int d_06f3 = 0;

int d_06f5 = 0;

int d_06f7 = 0;

int d_06f9 = 0;

int d_06fb = 0;

char d_06fd = 0x00;

int d_06fe = 0;

int d_0700 = 0;

int d_0702[12] = {
    128, 92, 64, 32, 16, 8, -8, -16,
    -32, -64, -92, -128
};

int d_071a = 0;

int d_071c = 0;

int d_071e = 0;

int d_0720 = 0;

/* g1_0e30 */
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
        while (d_a0fa_ == 0x24) {
        }
        i = 0x0f;
        do {
            if (++i == 0x17)
                i = 0x0f;
            g2_01f5(a0, &x1, &y1);
            text = g1_0c52(a0);
            g2_1340(a1 + 9, 0x0b);
            if (d_a0fa_ != 0)
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
            if (d_a0fa_ != 0)
                return;
        } while (text.b != 1 && text.c != 1);
        do {
            text = g1_0c52(a0);
        } while (text.b == 1 || text.c == 1);
        dx = (x2 - x1) / 6;
        dy = (y2 - y1) / 6;
        d_9676_[a0] = x1 + dx;
        d_771c_[a0] = x2 - dx;
        d_967c_[a0] = y1 + dy;
        d_7722_[a0] = y2 - dy;
        g2_37b6(" Should button 1 (S)hoot", a1, 0x11);
        g2_37b6(" or (J)ump?", a1, 0x12);
        g2_2870(a1 + 0x0c, 0x12);
        if (d_a0fa_ == 1)
            return;
        if (d_a0fa_ == 0x1f)
            d_c297_ = 1;
        else
            d_c297_ = 0;
        d_cc81_ = 1;
        d_d56b_ = 1;
        while (d_a0fa_ == 0x1f || d_a0fa_ == 0x24) {
        }
        return;
    }
}

/* g1_1053 */
int g1_1053(void)
{
    register int v = inportb(0x201);

    if (!(v & 0x10))
        return 1;
    if (!(v & 0x20))
        return 2;
    return 0;
}

/* g1_1076 */
void g1_1076(void)
{
    struct reading r;

    do {
        r = g1_0c52(1);
    } while (r.b == 1 || r.c == 1);
}

/* g1_10a5 */
void g1_10a5(void)
{
    char sample;

    sample = inportb(0x201);
    if (d_c297_ != 0) {
        d_d138_ = !(sample & 0x10);
        d_d135_ = !(sample & 0x20);
    } else {
        d_d138_ = !(sample & 0x20);
        d_d135_ = !(sample & 0x10);
    }
}

/* g1_10fb */
void pascal g1_10fb(char far *filename, register int offset, int count)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    if (filename[0] != 0) {
        d_7986_ = MK_FP(0xa000, 0);
        d_cc7d_ = MK_FP(0xa000, 0x4000);
        count /= 4;
        fgetc(stream);
        fgetc(stream);
        fgetc(stream);
        for (i = 0; i < count; ++i) {
            fgetc(stream);
            outport(0x3c4, 0x0102);
            *(d_cc7d_ + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0202);
            *(d_cc7d_ + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0402);
            *(d_cc7d_ + i + offset) = fgetc(stream);
            outport(0x3c4, 0x0802);
            *(d_cc7d_ + i + offset) = fgetc(stream);
        }
        fclose(stream);
    }
}

/* g1_1247 */
char g1_1247(void)
{
    unsigned int far *p0;
    unsigned int far *p2;
    unsigned int far *p1;

    p0 = d_7729_ + ((d_0099 + d_009d - 3) >> 1) + d_009f + (((d_009b - 16) >> 4) << 7);
    p1 = p0;
    p2 = p0 - 128;
    if ((d_009b >> 3) & 1)
        p1 += 128;
    if (p0[0] > 0x17ffU)
        return 0;
    if (p2[0] > 0x17ffU)
        return 0;
    if (p1[0] > 0x17ffU)
        return 0;
    return 1;
}

/* g1_12ce */
unsigned char g1_12ce(void)
{
    unsigned int far *p;
    unsigned int far *r;
    unsigned int far *q;

    p = d_7729_ + ((d_009d + d_0099) >> 1) + d_009f
        + (((d_009b - 16) >> 4) << 7);
    q = p;
    r = p - 128;
    if ((d_009b >> 3) & 1)
        q += 128;
    if (*p > 0x17ff || *r > 0x17ff || *q > 0x17ff)
        return 0;
    return 1;
}

/* g1_1352 */
char g1_1352(void)
{
    unsigned int far *p1;
    unsigned int far *p2;

    p1 = d_7729_ + ((d_0099 + d_009d - 2) >> 1) + d_009f
        + (((d_009b - 40) >> 4) << 7);
    p2 = p1;

    if ((d_0099 + d_009d) & 1)
        ++p2;

    if (*p1 >= 0x2ee0 || *p2 >= 0x2ee0 ||
        (*p1 >= 0x1b80 && *p1 <= 0x1ca0) ||
        (*p2 >= 0x1b80 && *p2 <= 0x1ca0)) {
        if (d_d576_ != 0)
            return 0;
        if (d_0611 != 0)
            return 0;
        if (d_0439 == 0)
            d_043b = 0;
        if (d_a0f8_ != 0) {
            d_0439 = 1;
            d_0644 = 1;
            g1_0042(0x1b);
        }
        else {
            g1_0042(0x26);
        }
        return 0;
    }

    d_0439 = 0;
    if (*p1 > 0x17ff || *p2 > 0x17ff) {
        if (d_0439 == 0)
            g1_0042(0x26);
        return 0;
    }
    return 1;
}

/* g1_143e */
char g1_143e(void)
{
    unsigned int far *p1;
    unsigned int far *p2;

    if (d_d576_)
        goto zero_result;

    p1 = d_7729_ + ((d_0099 + d_009d - 2) >> 1) + d_009f + ((d_009b >> 4) << 7);
    p2 = p1;
    if ((d_0099 + d_009d) & 1)
        p2++;

    if (*p1 > 0x17ff)
        goto zero_result;
    if (*p2 <= 0x17ff)
        goto one_result;

zero_result:
    return 0;

one_result:
    return 1;
}

/* g1_14af */
void g1_14af(void)
{
    register int si;
    register int di;
    unsigned int far *p;
    int offset;

    si = 0x282 - (d_009d & 1);
    di = 0;
    p = d_7729_ + (d_009d >> 1) + d_009f;
    offset = 0x4000;
    outport(0x3ce, 0x105);
    d_0437 += 0x20;
    if (d_0437 == 0x80)
        d_0437 = 0;
    do {
        if (d_009d & 1) {
            if (*p == 0 || p[1] == 0)
                asm_02ad(offset, si + 1);
            else if (*p == 0x20 || p[1] == 0x20)
                asm_02ad(offset + 0x4100, si + 1);
        } else {
            if (*p == 0)
                asm_02ad(offset, si);
            else if (*p == 0x20)
                asm_02ad(offset + 0x4100, si);
        }
        if (*p > 0x20) {
            if (*p < 0x5e0)
                asm_02ad(*p + d_0437, si);
            else
                asm_02ad(*p, si);
        }
        ++p;
        si += 2;
        if (++di == 14) {
            si += 0x264;
            p += 0x72;
            di = 0;
        } else {
            offset += 0x20;
        }
    } while (si < 0x191c);
    outport(0x3ce, 5);
}

/* g1_15f4 */
void interrupt g1_15f4(void)
{
    d_a0fa_ = inportb(0x60);

    if (d_5002_ == 0 && d_4ed2_ == 0 && d_cc81_ == 0 &&
        d_c683_ == 0 && d_d139_ == 0 && d_d13b_ == 0) {
        if (d_a0fa_ == d_02f4) d_c68c_ = 1;
        if (d_a0fa_ == (d_02f4 | 0x80)) d_c68c_ = 0;
        if (d_a0fa_ == d_02f5) d_d134_ = 1;
        if (d_a0fa_ == (d_02f5 | 0x80)) d_d134_ = 0;
        if (d_a0fa_ == d_02f6) d_d13f_ = 1;
        if (d_a0fa_ == (d_02f6 | 0x80)) d_d13f_ = 0;
        if (d_a0fa_ == d_02f7) d_d4c0_ = 1;
        if (d_a0fa_ == (d_02f7 | 0x80)) d_d4c0_ = 0;
        if (d_a0fa_ == d_02f9) d_d138_ = 1;
        if (d_a0fa_ == (d_02f9 | 0x80)) d_d138_ = 0;
        if (d_a0fa_ == d_02f8) d_d135_ = 1;
        if (d_a0fa_ == (d_02f8 | 0x80)) d_d135_ = 0;
    }

    if (d_a0fa_ == 0x33) d_0643 = 1;
    if (d_a0fa_ == 0xb3) d_0643 = 0;
    if (d_a0fa_ == 0x34) d_d148_ = 1;
    if (d_a0fa_ == 0xb4) d_d148_ = 0;
    if (d_a0fa_ == 0x0e) d_a67d_ = 1;
    if (d_a0fa_ == 0x8e) d_a67d_ = 0;
    if (d_a0fa_ == 0x51) d_a8d9_ = 1;
    if (d_a0fa_ == 0xd1) d_a8d9_ = 0;
    if (d_a0fa_ == 0x22) d_7728_ = 1;
    if (d_a0fa_ == 0xa2) d_7728_ = 0;
    if (d_a0fa_ == 0x18) d_772d_ = 1;
    if (d_a0fa_ == 0x98) d_772d_ = 0;
    if (d_a0fa_ == 0x20) d_771b_ = 1;
    if (d_a0fa_ == 0xa0) d_771b_ = 0;

    if (d_039d != 0)
        d_5556_();

    outportb(0x61, inportb(0x61) | 0x80);
    outportb(0x61, inportb(0x61) & 0x7f);
    outportb(0x20, 0x20);
}

/* g1_17f5 */
void g1_17f5(int a0, int a1, int a2, int a3)
{
    register int offset;

    offset = a0 * 4 * 0xa0;
    if (d_4ed2_ >= 4)
        return;
    if (d_5002_ != 0)
        return;
    if (d_d4bf_ > 0)
        --d_d4bf_;
    if (a2 >= 0x20 && d_d4bf_ % 2 == 0) {
        asm_0424((d_5ec4_+ offset), a1 - 1, a2 - 0x10);
        asm_0424((d_5ec4_+ offset + 0xa0), a1 + 1, a2 - 0x10);
    }
    if (a2 >= 0x10) {
        if (d_d4bf_ % 2 == 0) {
            asm_0424((d_5ec4_+ offset + 0x140), a1 - 1, a2);
            asm_0424((d_5ec4_+ offset + 0x1e0), a1 + 1, a2);
        }
    } else {
        d_0644 = 1;
    }
}

/* g1_18d4 */
void pascal g1_18d4(register int a0, int a1, int a2)
{
    register int i;
    struct t_cb6d far *p;

    for (i = 0; i < d_c295_; ++i) {
        p = &d_cb6d_[i];
        if (p->state == 0) {
            g1_0042(6);
            p->marker = 1;
            p->state = a2 + 1;
            p->x = a0;
            p->y = a1;
            return;
        }
    }
}

/* g1_1933 */
void g1_1933(void)
{
    register int i;
    struct t_cb6d far *p;

    d_0646 += 0xa0;
    if (d_0646 == 0x140)
        d_0646 = 0;

    for (i = 0; i < d_c295_; ++i) {
        p = &d_cb6d_[i];

        if (p->state == 0)
            continue;

        if (p->state == 1) {
            p->x -= 2;
            d_530f_ = 1;
            if (g1_367e(p->x + 1, p->y)) {
                p->state = 0;
                g1_2b86(1, p->x + 1, p->y + 0x40);
                continue;
            }
            if (!g1_326e(p->x, p->y)) {
                if (p->marker == 0)
                    asm_0424(d_a0fb_ + d_0646 + 0x3c0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
            } else {
                p->state = 0;
            }
            if (p->marker != 0) {
                p->marker = 0;
                asm_0424(d_a0fb_ + 0x1cc0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x13);
            }
        }

        if (p->state == 5) {
            p->x += 2;
            d_530f_ = 1;
            if (g1_367e(p->x, p->y)) {
                p->state = 0;
                g1_2b86(1, p->x - 1, p->y + 0x40);
                continue;
            }
            if (!g1_326e(p->x, p->y)) {
                if (p->marker == 0)
                    asm_0424(d_a0fb_ + d_0646 + 0x500,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
            } else {
                p->state = 0;
            }
            if (p->marker != 0) {
                p->marker = 0;
                asm_0424(d_a0fb_ + 0x1d60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x13);
            }
        }
    }
    d_530f_ = 0;
}

/* g1_1b51 */
void pascal g1_1b51(void)
{
    register int i;

    for (i = 0; i < d_051c; i++) {
        d_52dd_[i].used = 0;
        d_52dd_[i].marker = 0;
    }
}

/* g1_1b8a */
void pascal g1_1b8a(register int a0, int a1, int a2)
{
    register int i;
    struct t_52dd far *p;
    for (i = 0; i < d_051c; ++i) {
        p = &d_52dd_[i];
        if (p->used == 0) {
            p->used = a0;
            p->x = a1;
            p->y = a2;
            p->marker = 1;
            if (g1_326e(p->x, p->y) == 0)
                g1_0042(11);
            return;
        }
    }
}

/* g1_1bf6 */
void g1_1bf6(void)
{
    register int i;
    struct t_52dd far *p;

    d_0648 += 0xa0;
    if (d_0648 == 0x140)
        d_0648 = 0;

    for (i = 0; i < d_051c; ++i) {
        p = &d_52dd_[i];
        if (p->used == 0)
            continue;

        if (p->used == 1) {
            if (g1_3513(p->x, p->y)) {
                if (d_6379_ != 0)
                    goto success_update;
                if (d_d4bf_ != 0)
                    goto success_update;
                if (g1_1247() == 0)
                    goto success_update;
                --d_0099;
                goto success_update;
            } else {
                --p->x;
                if (g1_367e(p->x, p->y) != 0)
                    goto clear_record;
                if (g1_367e(p->x, p->y + 0x40) != 0)
                    goto clear_record;
                if (g1_326e(p->x, p->y) == 0) {
                    if (p->marker != 0) {
                        p->marker = 0;
                        asm_0424(d_a0fb_ + 0x1e00,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x13);
                    } else {
                        asm_0424(d_a0fb_ + d_0648 + 0x1860,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x13);
                    }
                } else {
                    p->used = 0;
                }
            }
        }

        if (p->used == 2) {
            if (g1_3513(p->x, p->y)) {
                if (d_6379_ == 0 && d_d4bf_ == 0 && g1_12ce())
                    ++d_0099;
success_update:
                p->used = 0;
                d_6379_ = 1;
            } else {
                ++p->x;
                if (g1_367e(p->x + 1, p->y) != 0)
                    goto clear_record;
                if (g1_367e(p->x + 1, p->y + 0x40) != 0)
                    goto clear_record;
                if (g1_326e(p->x, p->y) != 0)
                    goto clear_record;
                if (p->marker != 0) {
                    p->marker = 0;
                    asm_0424(d_a0fb_ + 0x1ea0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
                } else {
                    asm_0424(d_a0fb_ + d_0648 + 0x19a0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x13);
                }
            }
        }
        goto loop_continue;
clear_record:
        p->used = 0;
loop_continue:
        ;
    }
}

/* g1_1e77 */
void g1_1e77(void)
{
    if (d_6379_ != 0 && d_d4bf_ != 0)
        d_6379_ = 0;
    if (d_03a1 == 0) {
        if (g1_143e() != 0 && d_0610 != 0) {
            d_0610 = 0;
            d_0611 = 1;
        }
        if (d_0610 == 0 && d_0439 == 0) {
            if (d_a679_ != 0)
                ++d_d144_;
            if (d_d144_ == 14) {
                d_d144_ = 0;
                d_a679_ = 0;
            }
            if (g1_1352() == 0 && d_a679_ != 0) {
                d_a679_ = 0;
                d_d144_ = 0;
            }
            if (d_0611 == 0 && d_0612 < 9 && g1_1352() != 0) {
                    d_009b -= d_0613[d_798a_].cells[d_0612];
                    ++d_0612;
                    d_0644 = 0;
                    if (g1_143e() == 0) {
                        d_0610 = 1;
                        d_0644 = 1;
                        d_009b = (d_009b >> 4) << 4;
                        g1_29d0(d_0099 + d_009d,
                                (((d_009b - 16) >> 4) << 7) + d_009f);
                        g1_0042(14);
                        d_a679_ = 0;
                        d_d144_ = 0;
                    }
            } else {
                d_0611 = 1;
            }
        if (d_0611 != 0) {
            if (g1_143e() == 0) {
                d_0610 = 1;
                d_0644 = 1;
                d_0611 = 0;
                d_a679_ = 0;
                d_d144_ = 0;
                d_009b = (d_009b >> 4) << 4;
                g1_29d0(d_0099 + d_009d,
                        (((d_009b - 16) >> 4) << 7) + d_009f);
                g1_0042(14);
            } else {
                d_009b += 8;
            }
        if (g1_143e() == 0) {
            d_009b = (d_009b >> 4) << 4;
            g1_29d0(d_0099 + d_009d,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
            g1_0042(14);
            d_a679_ = 0;
            d_d144_ = 0;
            d_0644 = 1;
        }
        if (d_009b >= 0x84) {
            d_009b += 8;
            d_0644 = 1;
            if (g1_143e() == 0) {
                d_0610 = 1;
                d_0612 = 0;
                d_0611 = 0;
                d_009b = (d_009b >> 4) << 4;
                g1_29d0(d_0099 + d_009d,
                        (((d_009b - 16) >> 4) << 7) + d_009f);
                g1_0042(14);
            }
        }
        }
        }
        if (d_c68c_ != 0 && d_0439 != 0 && d_d576_ == 0) {
            d_009b -= 16;
            if (g1_1352() != 0) {
                d_009b -= 16;
                if (g1_1352() != 0) {
                    d_d576_ = 3;
                    d_0439 = 0;
                }
                d_009b += 16;
            } else {
                d_d576_ = 0;
                d_0439 = 1;
            }
            d_009b += 16;
        }
        if (d_d134_ != 0 && d_0439 != 0) {
            d_043b = 0;
            d_0439 = 0;
        }
        if ((d_0439 == 0 || d_d135_ == 0) && d_d4c0_ == 0 &&
            d_d13f_ != 0 && d_d576_ == 0) {
            if (d_043a == 0 && g1_1247() != 0)
                --d_0099;
            if (d_043a != 0) {
                d_043a = 0;
                d_043b = 0;
                d_a679_ = 0;
            } else if (d_0437 == 0 || d_0437 == 0x40) {
                if (g1_143e() == 0)
                    g1_0042(0x16);
                if (d_043b < 3)
                    ++d_043b;
                else
                    d_043b = 0;
            }
        }
        if (d_0099 == 11) {
            if (d_009d > 0) {
                --d_009d;
                ++d_0099;
            }
        } else if (d_0099 <= 10 && d_009d > 1) {
            d_009d -= 2;
            d_0099 += 2;
            if (d_009d == 1) {
                ++d_0099;
                --d_009d;
            }
        }
        if ((d_0439 == 0 || d_d135_ == 0) && d_d13f_ == 0 &&
            d_d4c0_ != 0 && d_d576_ == 0) {
            if (d_043a != 0 && g1_12ce() != 0)
                ++d_0099;
            if (d_043a == 0) {
                d_043a = 4;
                d_043b = 0;
                d_a679_ = 0;
            } else if (d_0437 == 0 || d_0437 == 0x40) {
                if (g1_143e() == 0)
                    g1_0042(0x16);
                if (d_043b < 3)
                    ++d_043b;
                else
                    d_043b = 0;
            }
        }
        if (d_0099 == 0x11) {
            if (d_009d < 0xe6) {
                ++d_009d;
                --d_0099;
            }
        } else if (d_0099 >= 0x12 && d_009d < 0xe6) {
            d_009d += 2;
            d_0099 -= 2;
            if (d_009d == 0xe5) {
                --d_0099;
                ++d_009d;
            }
        }
        if (d_0439 != 0) {
            d_009b = (d_009b >> 4) << 4;
            d_0611 = 1;
            d_0610 = 0;
            g1_1352();
        }
        if (d_d138_ != 0 && d_0610 != 0 && d_a0f3_ == 0 &&
            d_0439 == 0 && d_d576_ == 0) {
            d_0610 = 0;
            d_0612 = 0;
            d_0611 = 0;
            if (d_798a_ != 0 && d_0437 == 0) {
                if (d_d13f_ != 0 && g1_1247() != 0)
                    d_a679_ = 1;
                if (d_d4c0_ != 0 && g1_12ce() != 0)
                    d_a679_ = 2;
            }
            g1_0042(13);
        }
        if (d_d138_ != 0 && d_0439 == 0)
            d_a0f3_ = 1;
        else
            d_a0f3_ = 0;
    }
    g1_14af();
    g1_a53a(); g1_892b(); g1_87bf(); g1_6292();
    g1_b1fd(); g1_ba39(); g1_3882(); g1_a3e7(); g1_bdd9();
    if (d_03a1 != 0)
        return;
    if (d_0439 != 0 && d_d135_ == 0 && d_d576_ == 0 && d_6379_ == 0) {
        if (d_043a == 0)
            DRAW3(0x1c + d_043b, d_0099, d_009b);
        else
            DRAW3(0x20 + d_043b, d_0099, d_009b);
        if ((d_d13f_ == 0 && d_d4c0_ != 0) ||
            (d_d4c0_ == 0 && d_d13f_ != 0)) {
            if (d_0437 == 0x20 || d_0437 == 0x60)
                g1_0042(0x1b);
        }
    }
    if (d_0439 != 0 && d_d135_ != 0 && d_d576_ == 0 && d_6379_ == 0) {
        if (d_043a == 0)
            DRAW3(0x24, d_0099, d_009b);
        else
            DRAW3(0x25, d_0099, d_009b);
    }
    if (d_d135_ != 0 && d_d13f_ == 0 && d_d4c0_ == 0 && d_0439 == 0 &&
        d_d576_ == 0 && d_6379_ == 0)
        d_043b = 3;
    if (d_a679_ == 0 && d_d13f_ == 0 && d_d4c0_ == 0 && d_d135_ == 0 &&
        d_0439 == 0 && d_d576_ == 0 && d_6379_ == 0) {
        if (d_043a == 0)
            d_043b = 0x0c;
        else
            d_043b = 9;
    }
    if (((d_0611 == 0 && d_0610 != 0) || g1_143e() == 0) &&
        d_a679_ == 0 &&
        d_0439 == 0 && d_d576_ == 0 && d_6379_ == 0)
        DRAW3(d_043a + d_043b, d_0099, d_009b);
    if (d_0610 == 0 && g1_143e() != 0 && d_a679_ == 0 && d_0439 == 0 &&
        d_d576_ == 0 && d_6379_ == 0) {
        if (d_0611 == 0) {
            if (d_043a == 0)
                DRAW3(d_043a + 8, d_0099, d_009b);
            else
                DRAW3(d_043a + 5, d_0099, d_009b);
        } else if (d_043a == 0) {
            DRAW3(d_043a + 10, d_0099, d_009b);
        } else {
            DRAW3(d_043a + 7, d_0099, d_009b);
        }
    }
    if (d_d576_ != 0 && d_6379_ == 0) {
        --d_d576_;
        d_009b -= 16;
        if (d_043a == 0)
            DRAW3(0x28 - d_d576_, d_0099, d_009b);
        else
            DRAW3(0x2b - d_d576_, d_0099, d_009b);
        if (d_d576_ == 0)
            d_0644 = 1;
    }
    if (d_a679_ != 0 && d_0439 == 0 && d_d576_ == 0 && d_6379_ == 0) {
    if (d_a679_ == 1) {
        switch (d_d144_) {
            case 0: case 1: DRAW3(0x0e, d_0099, d_009b); break;
            case 2: case 3: DRAW3(0x0f, d_0099, d_009b); break;
            case 4: case 5: DRAW3(0x10, d_0099, d_009b); break;
            case 6: case 7: DRAW3(0x11, d_0099, d_009b); break;
            case 8: case 9: DRAW3(0x12, d_0099, d_009b); break;
            case 10: case 11: DRAW3(0x13, d_0099, d_009b); break;
            case 12: case 13: DRAW3(0x14, d_0099, d_009b); break;
        }
    } else if (d_a679_ == 2) {
        switch (d_d144_) {
            case 0: case 1: DRAW3(0x15, d_0099, d_009b); break;
            case 2: case 3: DRAW3(0x16, d_0099, d_009b); break;
            case 4: case 5: DRAW3(0x17, d_0099, d_009b); break;
            case 6: case 7: DRAW3(0x18, d_0099, d_009b); break;
            case 8: case 9: DRAW3(0x19, d_0099, d_009b); break;
            case 10: case 11: DRAW3(0x1a, d_0099, d_009b); break;
            case 12: case 13: DRAW3(0x1b, d_0099, d_009b); break;
        }
    }
    }
    if (d_d135_ != 0 && d_9d98_ == 0 && d_6379_ == 0) {
        if (d_060e == 0)
            g1_18d4(d_0099 + d_009d,
                    (((d_009b - 0x1d) >> 4) << 7) + d_009f, d_043a);
        if (d_0439 != 0) {
            if (d_043a != 0)
                d_043b = 5;
            else
                d_043b = 8;
        }
    }
    if (d_d135_ != 0) d_9d98_ = 1; else d_9d98_ = 0;
    if (d_6379_ == 0 || d_d4bf_ != 0) return;
    d_d247_ = 0;
    if (d_03a1 == 0) { --d_4ed4_; g1_0a0e(); }
    g1_0042(15);
    d_6379_ = 0; d_d4bf_ = 0x15; d_0612 = 0; d_0610 = 0;
    d_0439 = 0; d_0611 = 1; d_a679_ = 0; d_d144_ = 0;
    if (d_043a == 0)
        DRAW3(0x2c, d_0099, d_009b);
    else
        DRAW3(0x2d, d_0099, d_009b);
}

/* g1_290f */
void g1_290f(void)
{
    if (d_5002_ == 0 && d_0644 != 0) {
        if (d_009b < 100 && d_009f > 0) {
            d_009f -= 128;
            d_009b += 16;
            if (d_009b >= 100)
                d_0644 = 0;
        } else if (d_009b > 112) {
            d_009f += 128;
            d_009b -= 16;
            if (d_009b <= 112)
                d_0644 = 0;
        }
    }
}

/* g1_295e */
void g1_295e(char far *filename, void far *buffer, unsigned int count)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    fgetc(stream);
    fgetc(stream);
    fgetc(stream);
    fread(buffer, count, 1, stream);
    fclose(stream);
}

/* g1_29d0 */
void pascal g1_29d0(register int a0, int a1)
{
    register int i;
    struct t_c8eb far *p;

    for (i = 0; i < d_051e; ++i) {
        p = &d_c8eb_[i];
        if (p->used == 0) {
            p->used = 1;
            p->value1 = a0;
            p->value2 = a1;
            break;
        }
    }
}

/* g1_2a1d */
void pascal g1_2a1d(void)
{
    register int i;

    for (i = 0; i < d_0518; i++)
        d_d4c3_[i].a = 0;
}

/* g1_2a40 */
void pascal g1_2a40(register int a0, int a1, int a2)
{
    register int i;
    struct s8 far *p;

    for (i = 0; i < d_0518; i++) {
        p = &d_d4c3_[i];
        if (p->a == 0) {
            p->a = 1;
            p->b = a1;
            p->c = a2;
            p->d = a0;
            break;
        }
    }
}

/* g1_2a93 */
void g1_2a93(void)
{
    register int i;
    struct s8 far *p;

    d_064a += 0xa0;
    if (d_064a > 0xa0)
        d_064a = 0;

    for (i = 0; i < d_0518; ++i) {
        p = &d_d4c3_[i];
        if (g1_326e(p->b, p->c) != 0) {
            if (p->d < 0x8c0) {
                p->a = 0;
                continue;
            }
        }
        if (p->a == 0)
            continue;

        p->c -= 8;
        if (g1_326e(p->b, p->c) == 0) {
            asm_0424(d_a0ef_ + p->d + d_064a,
                     p->b - d_009d,
                     ((p->c - d_009f) >> 3) + 0x10);
        }
        ++p->a;
        if (p->d < 0x8c0 && p->a == 0x28)
            p->a = 0;
        if (p->d >= 0x8c0 && p->a == 0x2bc)
            p->a = 0;
    }
}

/* g1_2b86 */
void pascal g1_2b86(register int a0, int a1, int a2)
{
    register int i;
    struct t_b63c far *p;

    for (i = 0; i < d_0522; i++) {
        p = &d_b63c_[i];
        if (p->state == 0) {
            p->state = 1;
            p->x = a1;
            p->y = a2;
            p->kind = a0;
            break;
        }
    }
}

/* g1_2bd9 */
void g1_2bd9(void)
{
    register int i;
    struct t_b63c far *p;

    for (i = 0; i < d_0522; ++i) {
        p = &d_b63c_[i];
        if (p->state != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (p->kind == 3) {
                    ++p->state;
                    if (p->state == 2) {
                        asm_0424(d_637a_ + 0x8160,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x10);
                    }
                    if (p->state == 4) {
                        if (g1_326e(p->x - 1, p->y - 0x40) == 0)
                            asm_0424(d_637a_ + 0x8200,
                                     p->x - d_009d - 1,
                                     ((p->y - d_009f) >> 3) + 8);
                        if (g1_326e(p->x + 1, p->y - 0x40) == 0)
                            asm_0424(d_637a_ + 0x82a0,
                                     p->x - d_009d + 1,
                                     ((p->y - d_009f) >> 3) + 8);
                        if (g1_326e(p->x - 1, p->y + 0x40) == 0)
                            asm_0424(d_637a_ + 0x8340,
                                     p->x - d_009d - 1,
                                     ((p->y - d_009f) >> 3) + 0x18);
                        if (g1_326e(p->x + 1, p->y + 0x40) == 0)
                            asm_0424(d_637a_ + 0x83e0,
                                     p->x - d_009d + 1,
                                     ((p->y - d_009f) >> 3) + 0x18);
                        p->state = 0;
                    }
                } else {
                    if (p->kind == 1) {
                        asm_0424(d_637a_ + p->state * 0xa0 + 0x19a0,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x10);
                    } else {
                        if (g1_3513(p->x, p->y) != 0)
                            d_6379_ = 1;
                        asm_0424(d_637a_ + p->state * 0xa0 + 0x37a0,
                                 p->x - d_009d,
                                 ((p->y - d_009f) >> 3) + 0x10);
                    }
                    ++p->state;
                    if (p->state == 7)
                        p->state = 0;
                }
            } else {
                p->state = 0;
            }
        }
    }
}

/* g1_2e64 */
void pascal g1_2e64(register int a0, int a1)
{
    register int i;
    struct t_d1cf far *p;

    for (i = 0; i < d_0520; i++) {
        p = &d_d1cf_[i];
        if (p->used == 0) {
            p->used = 1;
            p->x = a0;
            p->y = a1;
            break;
        }
    }
}

/* g1_2eb1 */
void g1_2eb1(void)
{
    register int i;
    struct t_d1cf far *p;

    for (i = 0; i < d_0520; i++) {
        p = &d_d1cf_[i];
        if (p->used != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                asm_0424(d_a0fb_ + p->used * 0xa0 + 0x14a0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                p->used++;
                if (p->used == 6)
                    p->used = 0;
            } else {
                p->used = 0;
            }
        }
    }
}

/* g1_2f4c */
void g1_2f4c(void)
{
    register int i;
    struct t_c8eb far *p;

    for (i = 0; i < d_051e; ++i) {
        p = &d_c8eb_[i];
        if (p->used != 0) {
            if (g1_326e(p->value1, p->value2) == 0) {
                asm_0424(d_a0fb_ + p->used * 0xa0 + 0xb40,
                         p->value1 - d_009d,
                         ((p->value2 - d_009f) >> 3) + 0x10);
                ++p->used;
                if (p->used != 6)
                    continue;
            }
            p->used = 0;
        }
    }
}

/* g1_2fe7 */
void pascal g1_2fe7(register int a0, int a1)
{
    register int i;
    struct t_551e far *p;

    for (i = 0; i < d_051a; i++) {
        p = &d_551e_[i];
        if (p->state == 0) {
            p->state = 1;
            p->value1 = a0;
            p->value2 = a1;
            break;
        }
    }
}

/* g1_3034 */
void pascal g1_3034(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x140 + 0x5b40;
    if (g1_326e(a1, a2) == 0) {
        asm_0424((d_637a_+ offset),
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
    if (g1_326e(a1 + 2, a2) == 0) {
        asm_0424((d_637a_+ offset + 0xa0),
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
}

/* g1_30c9 */
void g1_30c9(void)
{
    register int i;
    struct t_551e far *p;

    for (i = 0; i < d_051a; i++) {
        p = &d_551e_[i];
        if (p->state != 0) {
            p->state++;
            p->value2 += d_0412[p->state - 2];
            if (p->state < 16) {
                g1_3034((p->state - 2) / 3, p->value1, p->value2);
            }
            if (p->state == 18)
                p->state = 0;
        }
    }
}

/* g1_314c */
void pascal g1_314c(int a0, int a1)
{
    register int i;
    struct t_5320 far *p;

    d_064c++;
    if (d_064c > 3)
        d_064c = 0;
    for (i = 0; i < d_043e; i++) {
        p = &d_5320_[i];
        if (p->f[0] == 0) {
            p->f[0] = 1;
            p->f[1] = a0;
            p->f[2] = a1;
            p->f[3] = a0 + 1;
            p->f[4] = a1;
            p->f[5] = a0;
            p->f[6] = a1 + 8;
            p->f[7] = a0 + 1;
            p->f[8] = a1 + 8;
            switch (d_064c) {
            case 0:
                p->f[9] = 0xa0;
                p->f[10] = 0x140;
                p->f[11] = 0x1e0;
                p->f[12] = 0x280;
                break;
            case 1:
                p->f[9] = 0x280;
                p->f[10] = 0xa0;
                p->f[11] = 0x140;
                p->f[12] = 0x1e0;
                break;
            case 2:
                p->f[9] = 0x140;
                p->f[10] = 0x280;
                p->f[11] = 0x1e0;
                p->f[12] = 0xa0;
                break;
            case 3:
                p->f[9] = 0x1e0;
                p->f[10] = 0x280;
                p->f[11] = 0x140;
                p->f[12] = 0xa0;
                break;
            }
            g1_0042(10);
            return;
        }
    }
}

/* g1_326e */
char pascal g1_326e(int a0, int a1)
{
    if (a0 >= d_009d &&
        d_009d + 29 > a0 &&
        d_009f - 64 <= a1 &&
        d_009f + 1280 > a1)
        return 0;
    return 1;
}

/* g1_32a5 */
void g1_32a5(void)
{
    register int i;
    struct t_5320 far *p;

    for (i = 0; i < d_043e; ++i) {
        p = &d_5320_[i];
        if (p->f[0] != 0) {
            if (p->f[0] != 0) {
                p->f[1] += d_0440[p->f[0]];
                p->f[2] += (d_0440 + 1)[p->f[0]];
                p->f[3] += d_0476[p->f[0]];
                p->f[4] += (d_0476 + 1)[p->f[0]];
                p->f[5] += d_04ac[p->f[0]];
                p->f[6] += (d_04ac + 1)[p->f[0]];
                p->f[7] += d_04e2[p->f[0]];
                p->f[8] += (d_04e2 + 1)[p->f[0]];

                if (g1_326e(p->f[1], p->f[2]) == 0 &&
                    g1_326e(p->f[1], p->f[2] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[9],
                             p->f[1] - d_009d,
                             ((p->f[2] - d_009f) >> 3) + 0x10);
                }
                if (g1_326e(p->f[3], p->f[4]) == 0 &&
                    g1_326e(p->f[3], p->f[4] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[10],
                             p->f[3] - d_009d,
                             ((p->f[4] - d_009f) >> 3) + 0x10);
                }
                if (g1_326e(p->f[5], p->f[6]) == 0 &&
                    g1_326e(p->f[5], p->f[6] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[11],
                             p->f[5] - d_009d,
                             ((p->f[6] - d_009f) >> 3) + 0x10);
                }
                if (g1_326e(p->f[7], p->f[8]) == 0 &&
                    g1_326e(p->f[7], p->f[8] + 0x80) == 0) {
                    asm_0424(d_a0fb_ + p->f[12],
                             p->f[7] - d_009d,
                             ((p->f[8] - d_009f) >> 3) + 0x10);
                }
                p->f[0] += 2;
                if (p->f[0] == 0x17)
                    p->f[0] = 0;
            }
        }
    }
}

/* g1_3513 */
int g1_3513(int a0, int a1)
{
    register int v = d_009b;

    v >>= 4;
    v <<= 7;
    v += d_009f;
    v -= a1;
    v++;
    v++;

    if (abs(d_0099 + d_009d - a0) < 2 && v > 16 && v < 384)
        return 1;
    return 0;
}

/* g1_3558 */
char pascal g1_3558(int a0, register int a1)
{
    register int i;
    struct t_cb6d far *p;

    for (i = 0; i < d_c295_; i++) {
        p = &d_cb6d_[i];
        if (p->state != 0) {
            if (abs(p->x - a0) < 2 &&
                p->y - a1 < 128 &&
                p->y - a1 >= -128) {
                if (p->state == 1) {
                    p->state = 0;
                    return 1;
                }
                if (p->state == 5) {
                    p->state = 0;
                    return 2;
                }
                p->state = 0;
            }
        }
    }
    return 0;
}

/* g1_35ee */
int g1_35ee(register int a0, int a1, int a2)
{
    register int index;
    index = ((d_009b >> 4) << 7) + d_009f - a2 + 2;
    if (((d_0099 + d_009d - a0) > a0) &&
        ((d_0099 + d_009d - a0) < a1) &&
        (index > 0) &&
        (index < 0x180))
        return 1;
    return 0;
}

/* g1_363b */
int g1_363b(int a0, int a1)
{
    register int v = d_009b;

    v >>= 4;
    v <<= 7;
    v += d_009f;
    v -= a1;
    v++;
    v++;

    if (abs(d_0099 + d_009d - a0) == 0 && v > 0 && v < 384)
        return 1;
    return 0;
}

/* g1_367e */
int g1_367e(register int a0, register int a1)
{
    int far *p;

    p = d_7729_ + (a0 >> 1) + ((a1 >> 7) << 7) - 1;
    if (d_530f_ != 0) {
        if (*p == 0x1800) {
            *p = 0x17e0;
            g1_2e64(a0, a1);
        } else if (p[128] == 0x1800) {
            p[128] = 0x17e0;
            g1_2e64(a0, a1 + 128);
        } else {
            goto check;
        }
        g1_0042(42);
        g1_0b85(10L);
        return 1;
    }
check:
    if (*p > 0x17ff)
        return 1;
    return 0;
}

/* g1_3714 */
int g1_3714(int a0, int a1)
{
    unsigned int far *p;
    unsigned int far *q;

    p = d_7729_ + (a0 >> 1) + ((a1 >> 7) << 7) - 1;
    q = p;
    if (a0 & 1)
        q++;
    if (*p > 0x17ff || *q > 0x17ff)
        return 1;
    return 0;
}

/* g1_376f */
void g1_376f(void)
{
    register int i;
    struct g1_376f_record far *p;

    for (i = 0; i < d_043c; ++i) {
        p = &d_669f_[i];
        if (p->state != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x80;
                if (g1_3558(p->x, p->y) != 0) {
                    p->state = 0;
                    g1_314c(p->x, p->y);
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(500L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                } else if (g1_326e(p->x, p->y) == 0) {
                    asm_0424(d_a0fb_,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                }
            }
        }
    }
}

/* g1_3882 */
void g1_3882(void)
{
    register int si;
    struct g1_3882_record far *p;

    for (si = 0; si < d_0524; ++si) {
        p = &d_a8da_[si];
        if (g1_326e(p->x, p->y) == 0) {
            if (g1_363b(p->x, p->y - 0x20)) {
                if (d_555b_) {
                    d_555b_ = 0;
                    g2_0fc1();
                }
                if (!d_0439) {
                    if (d_c68c_) {
                        if (g1_1352()) {
                            if (!d_d134_) {
                                ++p->used;
                                p->y -= 0x80;
                                *((d_7729_ + p->y) + (p->x >> 1) - 1) = 0x1ae0;
                                d_009b -= 0x10;
                                g1_0042(0x14);
                                if (d_009b <= 0x40)
                                    d_0644 = 1;
                                d_0439 = 0;
                                asm_0424(d_a0fb_ + 0x320,
                                         p->x - d_009d,
                                         ((p->y - d_009f) >> 3) + 0x10);
                            }
                        }
                    }
                }
draw_second:
                asm_0424(d_a0fb_ + 0x320,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            } else if (p->used > 1) {
                --p->used;
                *((d_7729_ + p->y) + (p->x >> 1) - 1) = d_d646_[si];
                p->y += 0x80;
                asm_0424(d_a0fb_ + 0x320,
                         p->x - d_009d,
                         (p->y - d_009f) >> 3);
                continue;
            } else if (p->used == 1) {
                goto draw_second;
            } else {
                continue;
            }
        } else if (p->used > 1) {
            p->used--;
            *((d_7729_ + p->y) + (p->x >> 1) - 1) = d_d646_[si];
            p->y += 0x80;
        }
    }
}

/* g1_3a98 */
void g1_3a98(void)
{
    register int i;
    register int j;
    struct Record far *record;
    int height;

    ++d_064e;
    if (d_064e == 4)
        d_064e = 0;
    i = 0;
    goto otest;
obody:
    {
        record = &d_c299_[i];
        height = record->height;
        j = 0;
        goto test;
    body:
        *(d_7729_ + record->y + record->x + (j >> 1) - 2) =
            0x1c00 + ((d_064e & 1) << 5);
        ++j;
    test:
        if (j < height)
            goto body;

        if (record->state == 1) {
            *(d_7729_ + record->y + record->x - 2) =
                0x1b80 + (d_064e << 5);
            *(d_7729_ + record->y + record->x + (height >> 1) - 2) =
                0x1c40 + (d_064e << 5);
        }

        if (record->state == 0) {
            *(d_7729_ + record->y + record->x - 2) =
                0x1be0 - (d_064e << 5);
            *(d_7729_ + record->y + record->x + (height >> 1) - 2) =
                0x1ca0 - (d_064e << 5);
        }

        if (g1_35ee(record->y - 2, record->y + height + 2,
                    record->x - 0x20)) {
            if (record->state == 0 && g1_1247())
                --d_0099;
            if (record->state == 1 && g1_12ce())
                ++d_0099;
        }

        if (d_0439 != 0) {
            if (g1_35ee(record->y - 2, record->y + height + 2,
                        record->x + 0x60)) {
                if (record->state == 1 && g1_1247())
                    --d_0099;
                if (record->state == 0 && g1_12ce())
                    ++d_0099;
            }
        }
    }
    i++;
otest:
    if (i < d_0526)
        goto obody;
}

/* g1_3cbc */
void g1_3cbc(void)
{
    if (d_798a_ != 0)
        return;

    if (g1_326e(d_0528, d_052a) != 0)
        return;

    if (g1_3714(d_0528, d_052a + 0x80) == 0)
        d_052a += 0x80;

    if (g1_3513(d_0528, d_052a) != 0 && d_052c != 0) {
        d_798a_ = 1;
        g1_2a40(0x3c0, d_0528, d_052a);
        g1_0b85(0x3e8L);
        g2_1ffa(d_a0fb_ + 0x640);
        g1_0042(0x0c);
        return;
    }

    if (d_052c == 0) {
        if (g1_3558(d_0528, d_052a) != 0) {
            g1_314c(d_0528, d_052a);
            d_052c = 1;
            if (g1_3714(d_0528, d_052a + 0x80) == 0) {
                g1_0b85(0x1f4L);
                g1_2a40(0x280, d_0528, d_052a);
            }
        }
    }

    if (d_052c == 0) {
        asm_0424(d_a0fb_,
                 d_0528 - d_009d,
                 ((d_052a - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb_ + 0x640,
                 d_0528 - d_009d,
                 ((d_052a - d_009f) >> 3) + 0x10);
    }
}

/* g1_3e06 */
void g1_3e06(void)
{
    register int i;
    struct g1_3e06_record far *p;

    d_4ed8_ = 1;
    for (i = 0; i < d_053e; ++i) {
        p = &d_6bb2_[i];
        if (p->state == 0)
            continue;

        d_4ed8_ = 0;
        if (g1_3558(p->x, p->y) != 0 && p->state == 1) {
            p->state = 2;
            g1_0042(0x1e);
            g1_0b85(200L);
        }

        if (p->state > 1 && p->state < 10) {
            if (p->state == 9) {
                *((&d_7729_[p->y] + (p->x >> 1)) + 0x7f) =
                    *((&d_7729_[p->y] + (p->x >> 1)) + 0xff);
                g1_314c(p->x, p->y + 0x80);
            }

            if (p->state == 3)
                g1_2b86(3, p->x, p->y + 0x80);

            if ((p->state & 1) != 0) {
                if (g1_326e(p->x, p->y + 0x80) == 0)
                    asm_0424(d_a0fb_ + 0xaa0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x20);
            }
            ++p->state;
        }

        if (p->state == 10) {
            p->y -= 0x80;
            if (p->y % 0x100 != 0) {
                if (g1_326e(p->x, p->y + 0x80) == 0)
                    asm_0424(d_a0fb_ + 0xa00,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x20);
                if (g1_326e(p->x, p->y + 0x100) == 0)
                    asm_0424(d_a0fb_ + 0xaa0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x30);
            }
        }

        if (g1_326e(p->x, p->y - 0x180) == 0)
            asm_0424(d_a0fb_ + 0x6e0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) - 0x20);
        if (g1_326e(p->x, p->y - 0xfe) == 0)
            asm_0424(d_a0fb_ + 0x780,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) - 0x10);
        if (g1_326e(p->x, p->y - 0x80) == 0)
            asm_0424(d_a0fb_ + 0x780,
                     p->x - d_009d,
                     (p->y - d_009f) >> 3);

        if (g1_326e(p->x, p->y) == 0)
            asm_0424(d_a0fb_ + 0x820,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (g1_326e(p->x - 2, p->y) == 0)
            asm_0424(d_a0fb_ + 0x8c0,
                     p->x - d_009d - 2,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (g1_326e(p->x + 2, p->y) == 0)
            asm_0424(d_a0fb_ + 0x960,
                     p->x - d_009d + 2,
                     ((p->y - d_009f) >> 3) + 0x10);

        if (g1_3714(p->x, p->y - 0x200) == 0)
            continue;
        if (p->state != 10)
            continue;

        g1_314c(p->x - 3, p->y - 0x200);
        g1_314c(p->x + 2, p->y - 0x180);
        g1_314c(p->x + 1, p->y - 0x180);
        g1_314c(p->x - 1, p->y - 0x100);
        g1_314c(p->x, p->y - 0x80);
        p->state = 0;
        *((&d_7729_[p->y] + (p->x >> 1)) - 0x201) =
            *((&d_7729_[p->y] + (p->x >> 1)) - 0x181);
    }
}

/* g1_42b8 */
void g1_42b8(void)
{
    if (d_a0f8_ != 0)
        return;
    if (g1_326e(d_a67b_, d_a67e_) != 0)
        return;
    if (g1_3714(d_a67b_, d_a67e_ + 0x80) == 0)
        d_a67e_ += 0x80;
    if (g1_3513(d_a67b_, d_a67e_) != 0 && d_052e != 0) {
        d_a0f8_ = 1;
        g2_1ffa(d_a0fb_ + 0xb40);
        g1_2a40(0x3c0, d_a67b_, d_a67e_);
        g1_0b85(1000L);
        return;
    }

    if (d_052e == 0 && g1_3558(d_a67b_, d_a67e_) != 0) {
        g1_314c(d_a67b_, d_a67e_);
        d_052e = 1;
        if (g1_3714(d_a67b_, d_a67e_ + 0x80) == 0) {
            g1_0b85(500L);
            g1_2a40(0x280, d_a67b_, d_a67e_);
        }
    }

    if (d_052e == 0) {
        asm_0424(d_a0fb_,
                 d_a67b_ - d_009d,
                 ((d_a67e_ - d_009f) >> 3) + 0x10);
        return;
    }
    asm_0424(d_a0fb_ + 0xb40,
             d_a67b_ - d_009d,
             ((d_a67e_ - d_009f) >> 3) + 0x10);
}

/* g1_43fa */
void g1_43fa(void)
{
    register int i;
    struct g1_43fa_record far *p;

    for (i = 0; i < d_0540; ++i) {
        p = &d_772e_[i];
        if (p->state == 0)
            continue;
        ++p->state;
        if (p->state >= 0x0f) {
            if (p->state == 0x0f && g1_326e(p->x, p->y) == 0)
                g1_0042(0x2b);
            if (p->state < 0x19) {
                if ((p->state % 2) == 0)
                    continue;
                if (g1_326e(p->x, p->y) != 0)
                    continue;
                asm_0424(d_a0fb_ + 0x0f00,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                continue;
            }
            if (p->state < 0x2d) {
                if (g1_326e(p->x, p->y) != 0)
                    continue;
                if (g1_326e(p->x + 6, p->y) != 0)
                    continue;
                asm_0424(d_a0fb_ + ((p->state % 2) * 0xa0) + 0xfa0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                asm_0424(d_a0fb_ + ((p->state % 2) * 0xa0) + 0xfa0,
                         p->x - d_009d + 2,
                         ((p->y - d_009f) >> 3) + 0x10);
                asm_0424(d_a0fb_ + ((p->state % 2) * 0xa0) + 0x10e0,
                         p->x - d_009d + 4,
                         ((p->y - d_009f) >> 3) + 0x10);
                if (g1_3513(p->x, p->y) != 0) {
                    d_6379_ = 1;
                    continue;
                }
                if (g1_3513(p->x + 2, p->y - 0x20) != 0) {
                    d_6379_ = 1;
                    continue;
                }
                if (g1_3513(p->x + 4, p->y) == 0)
                    continue;
                d_6379_ = 1;
            } else if (p->state > 0x41) {
                p->state = 1;
            }
        }
    }
}

/* g1_4638 */
void g1_4638(void)
{
    register int i;
    struct g1_4638_entry far *p;

    for (i = 0; i < d_0542; ++i) {
        p = &d_9b3a_[i];
        if (p->state != 0) {
            ++p->state;

            if (p->state >= 15) {
            if (p->state == 15 &&
                g1_326e(p->position2, p->position4) == 0)
                g1_0042(0x2b);

            if (p->state < 25) {
                if (p->state % 2 != 0 &&
                    g1_326e(p->position2, p->position4) == 0) {
                    asm_0424(d_a0fb_ + 0x1220,
                             p->position2 - d_009d,
                             ((p->position4 - d_009f) >> 3) + 0x10);
                }
            } else if (p->state < 45) {
                if (g1_326e(p->position2, p->position4) == 0 &&
                    g1_326e(p->position2 - 6, p->position4) == 0) {
                    asm_0424(d_a0fb_ + 0x12c0 + (p->state % 2) * 0xa0,
                             p->position2 - d_009d,
                             ((p->position4 - d_009f) >> 3) + 0x10);
                    asm_0424(d_a0fb_ + 0x12c0 + (p->state % 2) * 0xa0,
                             p->position2 - d_009d - 2,
                             ((p->position4 - d_009f) >> 3) + 0x10);
                    asm_0424(d_a0fb_ + 0x1400 + (p->state % 2) * 0xa0,
                             p->position2 - d_009d - 4,
                             ((p->position4 - d_009f) >> 3) + 0x10);

                    if (g1_3513(p->position2, p->position4) != 0 ||
                        g1_3513(p->position2 - 2, p->position4) != 0 ||
                        g1_3513(p->position2 - 4, p->position4) != 0)
                        d_6379_ = 1;
                }
            } else if (p->state > 65) {
                p->state = 1;
            }
            }
        }
    }
}

/* g1_4874 */
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
        obj = &d_637f_[i];
        if (obj->type == 0xfe) {
            if (g1_3714(obj->x, obj->y + 128)) {
                g1_314c(obj->x, obj->y);
                g1_2b86(1, obj->x, obj->y);
                obj->type = 0;
                continue;
            }
            if (obj->step <= 20) {
                obj->x += d_0546[obj->step];
                obj->y += (d_0546 + 1)[obj->step];
                obj->step += 2;
            } else {
                obj->y += 128;
            }
            if (g1_326e(obj->x, obj->y)) {
                obj->type = 0;
                continue;
            }
            asm_0424(d_637a_ + 0x3c0,
                     obj->x - d_009d,
                     ((obj->y - d_009f) >> 3) + 16);
            asm_0424(d_637a_,
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
                obj->y += (d_0576 + 1)[obj->step];
                obj->step += 2;
            } else {
                obj->y += 128;
            }
            if (g1_326e(obj->x, obj->y)) {
                obj->type = 0;
                continue;
            }
            asm_0424(d_637a_ + 0x3c0,
                     obj->x - d_009d,
                     ((obj->y - d_009f) >> 3) + 16);
            asm_0424(d_637a_ + 0x320,
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
                d_6379_ = 1;
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

        asm_0424(d_637a_ + d_05a6 + 0x3c0,
                 obj->x - d_009d,
                 ((obj->y - d_009f) >> 3) + 16);
        asm_0424(d_637a_ + (obj->type - 1) * 0xa0,
                 obj->x - d_009d,
                 (obj->y - d_009f) >> 3);
    }
}

/* g1_4d42 */
void pascal g1_4d42(int a2, int p1, register int a0)
{
    register int a1 = p1;
    if (d_0650[a2 * 6] > 0 && g1_326e(a1, a0 - 256) == 0)
        asm_0424(d_637a_ + d_0650[a2 * 6] + 0x5a0,
                 a1 - d_009d,
                 ((a0 - d_009f) >> 3) - 16);

    if (d_0650[a2 * 6] > 0 && g1_326e(a1 + 2, a0 - 256) == 0)
        asm_0424(d_637a_ + G1_4D42_ROW(a2).f1 + 0x5a0,
                 a1 - d_009d + 2,
                 ((a0 - d_009f) >> 3) - 16);

    if (g1_326e(a1, a0 - 128) == 0)
        asm_0424(d_637a_ + G1_4D42_ROW(a2).f2 + 0x5a0,
                 a1 - d_009d,
                 (a0 - d_009f) >> 3);

    if (g1_326e(a1 + 2, a0 - 128) == 0)
        asm_0424(d_637a_ + G1_4D42_ROW(a2).f3 + 0x5a0,
                 a1 - d_009d + 2,
                 (a0 - d_009f) >> 3);

    if (g1_326e(a1, a0) == 0)
        asm_0424(d_637a_ + G1_4D42_ROW(a2).f4 + 0x5a0,
                 a1 - d_009d,
                 ((a0 - d_009f) >> 3) + 16);

    if (g1_326e(a1 + 2, a0) == 0)
        asm_0424(d_637a_ + G1_4D42_ROW(a2).f5 + 0x5a0,
                 a1 - d_009d + 2,
                 ((a0 - d_009f) >> 3) + 16);

    if (g1_3513(a1 + 1, a0) != 0 || g1_3513(a1 + 1, a0 - 128) != 0)
        d_6379_ = 1;
}

/* g1_4f91 */
void g1_4f91(void)
{
    register int i;
    struct g1_4f91_record far *p;

    for (i = 0; i < d_05aa; ++i) {
        p = &d_b6bc_[i];
        if (g1_326e(p->x, p->y) == 0 && p->marker == 0)
            p->marker = 1;
        if (p->state == 0 || p->marker == 0)
            continue;

        while (1) {
            if (g1_3558(p->x + 1, p->y - 128) != 0 ||
                g1_3558(p->x + 1, p->y) != 0)
                ++d_5081_[i];
            if (d_5081_[i] == 3) {
                g1_314c(p->x + 1, p->y - 256);
                g1_314c(p->x, p->y - 128);
                g1_314c(p->x + 2, p->y);
                g1_2b86(1, p->x + 1, p->y - 128);
                g1_2b86(1, p->x + 2, p->y - 64);
                g1_2b86(1, p->x + 2, p->y - 128);
                g1_2b86(1, p->x + 1, p->y);
                if (d_0437 == 0)
                    g1_2fe7(p->x, p->y);
                g1_0b85(2000L);
                p->state = 0;
                break;
            }

            if (d_5081_[i] == 1 && d_0437 == 0)
                g1_2e64(p->x, p->y - 192);
            if (d_5081_[i] == 2 && d_0437 == 0) {
                g1_2e64(p->x + 2, p->y - 192);
                g1_2e64(p->x, p->y - 192);
            }

            if (p->state < 25) {
                if (g1_3714(p->x + 1, p->y + 128) == 0) {
                    if (p->x > d_0099 + d_009d - 3)
                        g1_4d42(2, p->x, p->y);
                    else
                        g1_4d42(5, p->x, p->y);
                    p->y += 128;
                    break;
                }

                if (p->x > d_0099 + d_009d - 3) {
                    p->marker = 1;
                    if (p->state != 12)
                        g1_4d42(0, p->x, p->y);
                } else {
                    if (p->state != 12)
                        g1_4d42(3, p->x, p->y);
                    p->marker = 2;
                }
                ++p->state;
                p->y = (p->y >> 7) << 7;
                if (p->state == 13) {
                    if (p->marker == 1) {
                        g1_1b8a(1, p->x - 1, p->y - 80);
                        g1_4d42(1, p->x, p->y);
                    }
                    if (p->marker == 2) {
                        g1_1b8a(2, p->x + 3, p->y - 80);
                        g1_4d42(4, p->x, p->y);
                    }
                    ++p->state;
                }
                break;
            }

            if (p->state < 50) {
                if (p->marker == 1) {
                    if (g1_3714(p->x + 1, p->y - 256) != 0) {
                        p->y = (p->y >> 7) << 7;
                        g1_4d42(2, p->x, p->y);
                        p->state = 1;
                        break;
                    }
                    if (g1_367e(p->x - 1, p->y) == 0) {
                        p->x -= d_0698[p->state - 25];
                        p->y -= d_0698[p->state - 24];
                    } else {
                        p->y -= d_0698[p->state - 24];
                    }
                    g1_4d42(2, p->x, p->y);
                    p->state += 2;
                    break;
                }
                if (p->marker == 2) {
                    if (g1_3714(p->x + 1, p->y - 256) != 0) {
                        p->y = (p->y >> 7) << 7;
                        g1_4d42(5, p->x, p->y);
                        p->state = 1;
                        break;
                    }
                    if (g1_367e(p->x + 4, p->y) == 0) {
                        p->x += d_0698[p->state - 25];
                        p->y -= d_0698[p->state - 24];
                    } else {
                        p->y -= d_0698[p->state - 24];
                    }
                    g1_4d42(5, p->x, p->y);
                    p->state += 2;
                    break;
                }
            }

            p->state = 1;
        }
    }
}

/* g1_5427 */
void pascal g1_5427(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x140 + 0x1540;

    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_326e(a1 + 2, a2) == 0)
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_3513(a1, a2) || g1_3513(a1 + 2, a2))
        d_6379_ = 1;
}

/* g1_54e1 */
void g1_54e1(void)
{
    register int i;
    struct g1_54e1_record far *p;

    ++d_06de;
    if (d_06de == 2) {
        d_06de = 0;
        ++d_06dc;
    }
    if (d_06dc == 2)
        d_06dc = 0;

    for (i = 0; i < d_05ac; ++i) {
        p = &d_a0ff_[i];
        if (p->state == 0)
            continue;

        if (g1_3558(p->x, p->y) != 0 ||
            g1_3558(p->x + 2, p->y) != 0)
            ++d_d57e_[i];

        if (d_d57e_[i] == 2) {
            g1_314c(p->x + 2, p->y);
            g1_314c(p->x, p->y);
            g1_2b86(1, p->x + 1, p->y);
            g1_0b85(0x9c4L);
            g1_0042(0x12);
            p->state = 0;
            continue;
        }

        if (d_d57e_[i] == 1 && d_0437 == 0) {
            g1_2e64(p->x + 2, p->y - 0x40);
        }
        if (g1_3714(p->x, p->y + 0x80) == 0) {
            p->y += 0x20;
            g1_5427(0, p->x, p->y);
            continue;
        }

        if (p->state == 1) {
            if (g1_367e(p->x, p->y) != 0) {
                p->state = 2;
                g1_1b8a(2, p->x + 4, p->y - 0x40);
            } else if (g1_367e(p->x, p->y + 0x80) == 0) {
                p->state = 2;
                g1_1b8a(2, p->x + 4, p->y - 0x40);
            } else {
                if (d_06de == 0)
                    --p->x;
                g1_5427(d_06dc, p->x, p->y);
            }
        }

        if (p->state == 2) {
            if (g1_367e(p->x + 4, p->y) != 0 ||
                g1_367e(p->x + 4, p->y + 0x80) == 0) {
                p->state = 1;
                g1_1b8a(1, p->x - 2, p->y - 0x40);
                g1_5427(d_06dc + 2, p->x - 1, p->y);
                continue;
            }
            if (d_06de == 0)
                ++p->x;
            g1_5427(d_06dc + 2, p->x, p->y);
        }
    }
}

/* g1_573d */
void g1_573d(void)
{
    if (d_cc82_ != 0)
        return;

    if (g1_326e(d_0530, d_0532) != 0)
        return;

    if (g1_3714(d_0530, d_0532 + 0x80) == 0)
        d_0532 += 0x80;

    if (g1_3513(d_0530, d_0532) != 0 && d_0534 != 0) {
        d_cc82_ = 1;
        g1_2a40(0x3c0, d_0530, d_0532);
        g1_0b85(1000L);
        g1_0042(12);
        g2_1ffa(d_a0fb_ + 0x2760);
        return;
    }

    if (d_0534 == 0) {
        if (g1_3558(d_0530, d_0532) != 0) {
            g1_314c(d_0530, d_0532);
            d_0534 = 1;
            if (g1_3714(d_0530, d_0532 + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, d_0530, d_0532);
            }
        }
    }

    if (d_0534 == 0) {
        asm_0424(d_a0fb_,
                 d_0530 - d_009d,
                 ((d_0532 - d_009f) >> 3) + 0x10);
        return;
    }

    asm_0424(d_a0fb_ + 0x2760,
             d_0530 - d_009d,
             ((d_0532 - d_009f) >> 3) + 0x10);
}

/* g1_5887 */
void g1_5887(void)
{
    if (d_b3d4_ != 0)
        return;
    if (d_053c == 0)
        return;
    if (g1_326e(d_0536, d_0538) != 0)
        return;

    if (g1_3714(d_0536, d_0538 + 0x80) == 0)
        d_0538 += 0x80;

    if (g1_3513(d_0536, d_0538) != 0 && d_053a != 0) {
        d_b3d4_ = 1;
        g1_2a40(0x3c0, d_0536, d_0538);
        g1_0b85(1000L);
        g2_1f9c();
        g1_0042(12);
        return;
    }

    if (d_053a == 0) {
        if (g1_3558(d_0536, d_0538) != 0) {
            g1_314c(d_0536, d_0538);
            d_053a = 1;
            if (g1_3714(d_0536, d_0538 + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, d_0536, d_0538);
            }
        }
    }

    if (d_053a == 0) {
        asm_0424(d_a0fb_,
                 d_0536 - d_009d,
                 ((d_0538 - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb_ + 0x2800,
                 d_0536 - d_009d,
                 ((d_0538 - d_009f) >> 3) + 0x10);
    }
}

/* g1_59cf */
void pascal g1_59cf(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x280 + 0x1e00;

    if (g1_326e(a1, a2 - 0x80) == 0)
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);

    if (g1_326e(a1 + 2, a2 - 0x80) == 0)
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 - d_009d + 2,
                 (a2 - d_009f) >> 3);

    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a_ + offset + 0x140,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_326e(a1 + 2, a2) == 0)
        asm_0424(d_637a_ + offset + 0x1e0,
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_3513(a1 + 1, a2) != 0 ||
        g1_3513(a1 + 1, a2 - 0x40) != 0)
        d_6379_ = 1;
}

/* g1_5b0b */
void g1_5b0b(void)
{
    register int i;
    struct g1_5b0b_record far *p;

    ++d_05ae;
    ++d_05b0;
    if (d_05b0 == 0x3c)
        d_05b0 = 0;

    if (d_05b0 < 0x19 && d_05ae >= 4)
        d_05ae = 0;
    if (d_05b0 >= 0x19 && d_05ae >= 8)
        d_05ae = 4;

    for (i = 0; i < d_05b2; ++i) {
        p = &d_abec_[i];
        if (p->state != 0) {
            if ((g1_3558(p->x, p->y) != 0 ||
                 g1_3558(p->x + 2, p->y) != 0) && d_05b0 < 0x19)
                ++d_4eda_[i];

            if (d_4eda_[i] == 2) {
                g1_314c(p->x + 2, p->y);
                g1_314c(p->x, p->y);
                g1_2e64(p->x + 2, p->y - 0x80);
                g1_2b86(1, p->x + 1, p->y);
                g1_2b86(1, p->x + 1, p->y - 0x80);
                g1_2b86(1, p->x, p->y - 0x80);
                g1_0b85(5000L);
                p->state = 0;
                continue;
            }

            if (d_4eda_[i] == 1 && d_0437 == 0)
                g1_2e64(p->x + 2, p->y - 0x40);

            if (g1_3714(p->x + 1, p->y + 0x80) == 0) {
                p->y += 0x80;
                g1_59cf(d_05ae, p->x, p->y);
                continue;
            }

            if (p->state == 1) {
                if (g1_367e(p->x, p->y + 0x80) == 0 || g1_367e(p->x, p->y) != 0) {
                    p->state = 2;
                } else {
                    if (d_0437 == 0x40 || d_0437 == 0)
                        --p->x;
                    g1_59cf(d_05ae, p->x, p->y);
                    continue;
                }
            }

            if (p->state == 2) {
                if (g1_367e(p->x + 3, p->y + 0x80) == 0 || g1_367e(p->x + 3, p->y) != 0)
                    p->state = 1;
                else if (d_0437 == 0x40 || d_0437 == 0)
                    ++p->x;
                g1_59cf(d_05ae, p->x, p->y);
            }
        }
    }
}

/* g1_5d6f */
void g1_5d6f(void)
{
    register int i;
    struct g1_5d6f_record far *p;

    for (i = 0; i < d_05b4; ++i) {
        p = &d_ab32_[i];
        if (p->active != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x80;
                if (g1_3513(p->x, p->y) != 0 && p->state != 0) {
                    p->active = 0;
                    if (d_c295_ < 4) {
                        ++d_c295_;
                        g1_0adc();
                    }
                    g1_0042(0xc);
                    g1_0b85(1000L);
                    g1_2a40(0x3c0, p->x, p->y);
                    continue;
                }
                if (p->state == 0 && g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    p->state = 1;
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(500L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                }
                if (p->state == 0) {
                    asm_0424(d_a0fb_,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                } else {
                    asm_0424(d_a0fb_ + 0x1ae0,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                }
            }
        }
    }
}

/* g1_5f0c */
void g1_5f0c(void)
{
    register int i;
    struct g1_5f0c_record far *p;
    char status;

    d_06e0 += 0xa0;
    if (d_06e0 == 0x1e0)
        d_06e0 = 0;

    for (i = 0; i < d_05b6; i++) {
        p = &d_b0b4_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (p->state < 3) {
            if ((status = g1_3558(p->x, p->y)) != 0) {
                if (status == 1)
                    --p->x;
                if (status == 2)
                    ++p->x;
                g1_0042(0x12);
                p->state = 3;
            }
        }
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (p->state == 1) {
            if (g1_367e(p->x - 1, p->y) != 0 ||
                g1_367e(p->x - 1, p->y + 0x80) == 0) {
                p->state = 2;
            } else if (d_06e0 == 0) {
                --p->x;
            }
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a_ + d_06e0 + 0x3200,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        } else if (p->state == 2) {
            if (g1_367e(p->x + 2, p->y) != 0 ||
                g1_367e(p->x + 2, p->y + 0x80) == 0) {
                p->state = 1;
            } else if (d_06e0 == 0) {
                ++p->x;
            }
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a_ + d_06e0 + 0x3200,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        } else if (p->state >= 3) {
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a_ + (p->state - 3) * 0xa0 + 0x33e0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            ++p->state;
            if (p->state == 10) {
                p->state = 0;
                g1_2b86(1, p->x, p->y);
                g1_0b85(100L);
            }
        }
        if (g1_3513(p->x, p->y) != 0) {
            if (p->state > 0) {
                if (p->state < 3)
                    d_6379_ = 1;
            }
        }
    }
}

/* g1_6183 */
void pascal g1_6183(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x280 + 0x3c00;
    if (g1_326e(a1, a2 - 0x80) == 0) {
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1 + 2, a2 - 0x80) == 0) {
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 - d_009d + 2,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1, a2) == 0) {
        asm_0424(d_637a_ + offset + 0x140,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
    if (g1_326e(a1 + 2, a2) == 0) {
        asm_0424(d_637a_ + offset + 0x1e0,
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
}

/* g1_6292 */
void g1_6292(void)
{
    ++d_06e2;
    if (d_06e2 == 1)
        d_06e2 = 0;

    if (d_d570_ == 0)
        return;

    if (g1_3513(d_d4bd_ + 1, d_d4c1_) ||
        g1_3513(d_d4bd_ + 1, d_d4c1_ - 128)) {
        if (d_555a_) {
            g2_16f3();
            d_555a_ = 0;
        }
    }

    if (d_4ed2_ == 0 && d_c68c_ != 0 && d_d13f_ == 0 && d_d4c0_ == 0 && d_d138_ == 0 &&
        (g1_3513(d_d4bd_ + 1, d_d4c1_) || g1_3513(d_d4bd_ + 1, d_d4c1_ - 128))) {
        d_4ed2_ = 1;
        if (d_02fa % 2 != 0)
            g1_0042(0x27);
        disable();
        d_c68c_ = 0;
        enable();
    }

    if (d_4ed2_ == 0)
        g1_6183(0, d_d4bd_, d_d4c1_);
    if (d_4ed2_ == 0)
        return;

    if (d_06e2 == 0)
        ++d_4ed2_;
    if (d_4ed2_ < 5) {
        if (d_4ed2_ == 3 && d_02fa % 2 == 0)
            g1_0042(0x13);
        g1_6183(d_4ed2_ - 1, d_d4bd_, d_d4c1_);
        return;
    }
    if (d_4ed2_ < 5)
        return;

    switch (d_4ed2_) {
    case 4:
        g1_6183(3, d_d4bd_, d_d4c1_);
        break;
    case 5:
        g1_6183(2, d_d4bd_, d_d4c1_);
        break;
    case 6:
        g1_6183(1, d_d4bd_, d_d4c1_);
        break;
    case 7:
        g1_6183(0, d_d4bd_, d_d4c1_);
        break;
    case 8:
        g1_6183(0, d_d4bd_, d_d4c1_);
        d_0436 = 1;
        break;
    }
}

/* g1_6445 */
void g1_6445(void)
{
    register int i;
    struct g1_6445_record far *p;

    for (i = 0; i < d_05b8; ++i) {
        p = &d_555d_[i];
        if (p->state != 0) {
            if (g1_3714(p->x, p->y + 0x80) == 0)
                p->y += 0x80;

            if (p->kind == 0) {
                if (g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    p->kind = 1;
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(0x1f4L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                }
            }

            if (p->kind == 0) {
                if (g1_326e(p->x, p->y) == 0 && p->state < 0x0c) {
                    asm_0424(d_a0fb_,
                            p->x - d_009d,
                            ((p->y - d_009f) >> 3) + 0x10);
                    continue;
                }
            }

            if (p->kind == 0) {
                continue;
            }

                ++p->state;
                if (g1_326e(p->x, p->y) == 0) {
                    if (p->state < 0x0c) {
                        asm_0424(d_637a_ + 0x4600,
                                p->x - d_009d,
                                ((p->y - d_009f) >> 3) + 0x10);
                    }
                    if (p->state % 2 != 0 && p->state < 0x0c) {
                        asm_0424(d_637a_ + 0x46a0,
                                p->x - d_009d,
                                ((p->y - d_009f) >> 3) + 0x10);
                    }
                }

                if (p->state <= 0x0c)
                    continue;

                if (p->state == 0x0e) {
                    g1_2b86(2, p->x, p->y);
                    g1_0042(0x21);
                }
                else if (p->state == 0x11) {
                    if (g1_367e(p->x - 2, p->y) == 0 &&
                        g1_367e(p->x - 2, p->y + 0x80) != 0) {
                        g1_2b86(2, p->x - 2, p->y);
                    } else {
                        p->flag8 = 0;
                    }
                    if (g1_367e(p->x + 2, p->y) == 0 &&
                        g1_367e(p->x + 2, p->y + 0x80) != 0) {
                        g1_2b86(2, p->x + 2, p->y);
                    } else {
                        p->flag10 = 0;
                    }
                } else if (p->state == 0x13) {
                    if (p->flag8 != 0) {
                        if (g1_367e(p->x - 4, p->y) == 0 &&
                            g1_367e(p->x - 4, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x - 4, p->y);
                        } else {
                            p->flag8 = 0;
                        }
                    }
                    if (p->flag10 != 0) {
                        if (g1_367e(p->x + 4, p->y) == 0 &&
                            g1_367e(p->x + 4, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x + 4, p->y);
                        } else {
                            p->flag10 = 0;
                        }
                    }
                } else if (p->state == 0x15) {
                    if (p->flag8 != 0) {
                        if (g1_367e(p->x - 6, p->y) == 0 &&
                            g1_367e(p->x - 6, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x - 6, p->y);
                        } else {
                            p->flag8 = 0;
                        }
                    }
                    if (p->flag10 != 0) {
                        if (g1_367e(p->x + 6, p->y) == 0 &&
                            g1_367e(p->x + 6, p->y + 0x80) != 0) {
                            g1_2b86(2, p->x + 6, p->y);
                        } else {
                            p->flag10 = 0;
                        }
                    }
                } else if (p->state == 0x17) {
                    if (p->flag8 != 0 &&
                        g1_367e(p->x - 8, p->y) == 0 &&
                        g1_367e(p->x - 8, p->y + 0x80) != 0)
                        g1_2b86(2, p->x - 8, p->y);
                    if (p->flag10 != 0 &&
                        g1_367e(p->x + 8, p->y) == 0 &&
                        g1_367e(p->x + 8, p->y + 0x80) != 0)
                        g1_2b86(2, p->x + 8, p->y);
                }

                if (p->state == 0x18)
                    p->state = 0;
        }
    }
}

/* g1_6947 */
void g1_6947(void)
{
    register int i;
    register int active;

    active = 1;
    if (d_b636_ != 0) {
        for (i = active; i < 10; ++i) {
            d_abd4_[i - 1] = d_abd4_[i];
            d_b09c_[i - 1] = d_b09c_[i];
            if (d_d249_[i] != 0)
                active = 0;
        }
        if (active != 0) {
            d_b636_ = 0;
            g1_0b85(10000L);
            d_5310_ = 1;
            return;
        }
    } else {
        return;
    }

    d_abe6_ += d_02fd[d_abd2_];
    d_b0ae_ += d_034d[d_abd2_] << 6;

    for (i = 1; i < 10; ++i) {
        if (g1_326e(d_abd4_[i], d_b09c_[i]) == 0 && d_d249_[i] != 0) {
            asm_0424(d_637a_ + d_06e3 + 0x4b00,
                     d_abd4_[i] - d_009d,
                     ((d_b09c_[i] - d_009f) >> 3) + 0x10);
            if (g1_3513(d_abd4_[i], d_b09c_[i]) != 0)
                d_6379_ = 1;
        }

        if (d_0437 != 0)
            d_06e3 += 0xa0;
        if (d_06e3 == 0x460)
            d_06e3 = 0;
        if (d_d249_[i] != 0 &&
            g1_3558(d_abd4_[i], d_b09c_[i] - 0x80) != 0) {
            g1_2b86(3, d_abd4_[i], d_b09c_[i]);
            g1_0b85(1000L);
            g1_0042(10);
            g1_314c(d_abd4_[i], d_b09c_[i] - 0x80);
            d_d249_[i] = 0;
        }
    }

    ++d_abd2_;
    if (d_abd2_ == 0x27)
        d_abd2_ = 0;
}

/* g1_6afd */
void g1_6afd(void)
{
    register int i;
    struct g1_6afd_record far *p;

    outport(0x3ce, 0x105);
    d_06e5 += 0x28;
    if (d_06e5 > 0x28)
        d_06e5 = 0;
    for (i = 0; i < d_05ba; ++i) {
        p = &d_70db_[i];
        if (g1_326e(p->x, p->y) == 0)
            asm_0315(p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10,
                     d_06e5);
    }
}

/* g1_6b82 */
void g1_6b82(void)
{
    register int i;
    struct g1_6b82_record far *p;

    if (d_0437 == 0)
        d_06e7 += 0xa0;

    if (d_06e7 == 0x280) {
        d_06e7 = 0;
        i = 0;
    } else {
        i = 0;
    }

    for (; i < d_05bc; ++i) {
        p = &d_5a12_[i];

        if (p->state >= 3 && g1_326e(p->x, p->y))
            p->state = 0;

        if (p->state == 0)
            continue;

        if (g1_326e(p->x, p->y))
            continue;

        if (p->state >= 3 && g1_326e(p->x, p->y)) {
            p->state = 0;
            continue;
        }

        if (!g1_3714(p->x, p->y + 0x80) && p->state < 3)
            p->y += 0x80;

        if (p->state >= 3) {
            if (d_0437 != 0)
                p->y -= 0x40;
            if (g1_3714(p->x, p->y - 0x40)) {
                g1_2b86(1, p->x, p->y);
                p->state = 0;
                continue;
            }
            if (g1_3513(p->x, p->y)) {
                p->state = 0;
                g1_0b85(1000L);
                g1_2a40(0x3c0, p->x, p->y);
                g1_0042(0x10);
                continue;
            }
        }

        if (g1_3558(p->x, p->y)) {
            if (p->state == 1) {
                g1_314c(p->x, p->y);
                p->state = 2;
                if (!g1_3714(p->x, p->y + 0x80)) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
            } else if (p->state == 2) {
                p->state = 3;
                g1_0042(2);
            }
        }

        if (g1_3513(p->x, p->y) && p->state == 2) {
            p->state = 0;
            g1_0b85(200L);
            g1_2a40(0x140, p->x, p->y);
            g1_0acc();
            g1_0042(1);
            if (d_5554_ != 0) {
                g2_1534();
                d_5554_ = 0;
            }
        }

        if (p->state == 1)
            asm_0424(d_a0fb_ + 0x3f20,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (p->state == 2)
            asm_0424(d_637a_ + d_06e7 + 0x5000,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (p->state >= 3)
            asm_0424(d_637a_ + d_06e7 + 0x5280,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
    }
}

/* g1_6e71 */
void g1_6e71(void)
{
    register int i;
    struct g1_6e71_record far *p;

    d_06e9 += 0xa0;
    d_06eb -= 0xa0;
    if (d_06eb == -0xa0)
        d_06eb = 0x1e0;
    if (d_06e9 == 0x280)
        d_06e9 = 0;

    for (i = 0; i < d_05be; ++i) {
        p = &d_d261_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;

        if (p->state == 1) {
            p->y -= 8;
            asm_0424(d_637a_ + d_06e9 + 0x5500,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x - 2, p->y) == 0 ||
                g1_3714(p->x, p->y) != 0)
                p->state = 2;
        } else if (p->state == 2) {
            p->y += 8;
            asm_0424(d_637a_ + d_06eb + 0x5500,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x - 2, p->y + 0x80) == 0 ||
                g1_3714(p->x, p->y + 0x80) != 0)
                p->state = 1;
        } else if (p->state == 3) {
            p->y -= 8;
            asm_0424(d_637a_ + d_06e9 + 0x5780,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x + 2, p->y) == 0 ||
                g1_3714(p->x, p->y) != 0)
                p->state = 4;
        } else if (p->state == 4) {
            p->y += 8;
            asm_0424(d_637a_ + d_06eb + 0x5780,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
            if (g1_3714(p->x + 2, p->y + 0x80) == 0 ||
                g1_3714(p->x, p->y + 0x80) != 0)
                p->state = 3;
        }

        if (g1_3558(p->x, p->y) != 0) {
            g1_2b86(1, p->x, p->y);
            g1_2e64(p->x, p->y - 0x40);
            g1_0b85(0x64L);
            g1_0042(0x12);
            p->state = 0;
        }
        if (p->state != 0 && g1_3513(p->x, p->y) != 0)
            d_6379_ = 1;
    }
}

/* g1_7163 */
void g1_7163(void)
{
    register int i;
    struct g1_7163_record far *p;

    for (i = 0; i < d_05c0; i++) {
        p = &d_c01e_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (g1_3513(p->x, p->y)) {
            if (p->state > 1 && d_637e_ != 0) {
                d_637e_ = 0;
                g2_15c9();
            }
            if (p->state == 2) {
                p->state = 0;
                g1_0b85(100L);
                g1_2a40(0, p->x, p->y);
                g1_0042(1);
                g1_0acc();
                continue;
            }
            if (p->state == 3) {
                p->state = 0;
                g1_0b85(200L);
                g1_2a40(0x140, p->x, p->y);
                g1_0042(1);
                g1_0acc();
                g1_0acc();
                continue;
            }
        }
        if (p->state != 3 && g1_3558(p->x, p->y)) {
            if (p->state == 1) {
                g1_314c(p->x, p->y);
                if (g1_3714(p->x, p->y + 0x80) == 0) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
                p->state = 2;
            } else if (p->state == 2)
                p->state = 3;
        }
        if (p->state == 1) {
            asm_0424(d_a0fb_ + 0x3f20, (p->x - d_009d), (((p->y - d_009f) >> 3) + 0x10));
        } else {
            if (p->state == 2) {
                asm_0424(d_a0fb_ + 0x1b80, (p->x - d_009d), (((p->y - d_009f) >> 3) + 0x10));
            }
            if (p->state == 3) {
                asm_0424(d_a0fb_ + 0x1c20, (p->x - d_009d), (((p->y - d_009f) >> 3) + 0x10));
            }
        }
        if (p->state > 1 && d_637e_ != 0 && g1_3513(p->x, p->y)) {
            d_637e_ = 0;
            g2_15c9();
        }
    }
}

/* g1_73d3 */
void g1_73d3(void)
{
    register int si;

    if (d_c281_ == 0)
        return;
    if (g1_35ee(d_b62e_ - 2, d_b62e_ + d_d136_, d_b632_ - 32) != 0) {
        if (d_d155_ == 2) {
            for (si = 0; si < (d_d136_ >> 1); si++) {
                *((d_7729_ + d_d4b9_ + si) + (d_d4bb_ << 7) - 2) =
                    *((d_7729_ + d_d4b9_ + si) + (d_d4bb_ << 7) - 130);
                if (si % 2 != 0)
                    g1_314c(d_b62e_ * 2 + si * 2, d_b632_);
                else
                    g1_2b86(1, d_b62e_ * 2 + si * 2, d_b632_);
            }
            d_c281_ = 0;
            d_d155_ = 0;
            d_d155_ = 1;
            return;
        }
        d_d155_ = 1;
        return;
    }
    if (d_d155_ == 1)
        d_d155_ = 2;
}

/* g1_74c2 */
void g1_74c2(void)
{
    register int i;
    struct t_b3d6 far *p;

    d_06ed += 0xa0;
    if (d_06ed == 0x280)
        d_06ed = 0;

    for (i = 0; i < d_05c2; ++i) {
        p = &d_b3d6_[i];
        if (p->used != 0 && g1_326e(p->x, p->y) == 0) {
            if (g1_3513(p->x, p->y) != 0) {
                asm_0424(d_a0fb_ + d_06ed + 0x21c0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                d_6379_ = 1;
            } else {
                asm_0424(d_a0fb_ + d_06ed + 0x1f40,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
            if (d_0437 == 0)
                g1_0042(0x15);
        }
    }
}

/* g1_75b9 */
void pascal g1_75b9(int row, int horizontal, int vertical)
{
    register int index = row * 0x140 + 0x6180;
    if (g1_326e(horizontal, vertical - 0x80) == 0)
        asm_0424(d_637a_ + index, horizontal - d_009d,
                 (vertical - d_009f) >> 3);
    if (g1_326e(horizontal, vertical) == 0)
        asm_0424(d_637a_ + index + 0xa0, horizontal - d_009d,
                 ((vertical - d_009f) >> 3) + 0x10);
}

/* g1_7647 */
void g1_7647(void)
{
    register int i;
    struct g1_7647_record far *p;

    for (i = 0; i < d_05c4; i++) {
        p = &d_798c_[i];
        if (p->state != 0 &&
            (p->state <= 3 || p->state == 5 || p->state == 9 ||
             p->state == 15 || p->state == 25))
            p->count++;

        if (p->count == 4)
            p->count = 0;

        if (g1_326e(p->value1, p->value2) != 0 &&
            g1_326e(p->value1, p->value2 - 128) != 0)
            continue;

        if (g1_3558(p->value1, p->value2) != 0 ||
            g1_3558(p->value1, p->value2 - 128) != 0) {
            if (p->state == 1 || p->state == 2)
                g1_0b85(1000L);
            p->state = 3;
            g1_0042(18);
            g1_2e64(p->value1, p->value2 - 192);
        }

        if (p->state >= 3)
            p->state++;
        if (p->state == 26)
            p->state = 0;
        g1_75b9(p->count, p->value1, p->value2);

        if (p->state == 1) {
            if (g1_3513(p->value1 - 2, p->value2 - 64) ||
                g1_3513(p->value1 - 4, p->value2 - 64) ||
                g1_3513(p->value1 - 6, p->value2 - 64)) {
                if (g1_1247())
                    d_0099--;
            }
        }

        if (p->state == 2) {
            if (g1_3513(p->value1 + 2, p->value2 - 64) ||
                g1_3513(p->value1 + 4, p->value2 - 64) ||
                g1_3513(p->value1 + 6, p->value2 - 64)) {
                if (g1_12ce())
                    d_0099++;
            }
        }
    }
}

/* g1_784b */
void g1_784b(void)
{
    register int i;
    struct g1_784b_record far *p;

    for (i = 0; i < d_05c6; i++) {
        p = &d_9d99_[i];
        if (p->active != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x80;
                if (g1_3513(p->x, p->y) != 0 && p->state != 0) {
                    p->active = 0;
                    g1_2a40(0, p->x, p->y);
                    g1_0b85(100L);
                    g1_0042(0x10);
                    continue;
                }
                if (p->state == 0 && g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    p->state = 1;
                    if (g1_3714(p->x, p->y + 0x80) == 0) {
                        g1_0b85(500L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                }
                if (p->state == 0) {
                    asm_0424(d_a0fb_ + 0x3e80,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                } else {
                    asm_0424(d_a0fb_ + 0x2440,
                             p->x - d_009d,
                             ((p->y - d_009f) >> 3) + 0x10);
                }
            }
        }
    }
}

/* g1_79d9 */
void g1_79d9(void)
{
    register int i;
    struct g1_79d9_record far *p;

    for (i = 0; i < d_05c8; ++i) {
        p = &d_a357_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (g1_3513(p->x, p->y) != 0 && p->flag != 0) {
            p->state = 0;
            g1_2a40(0x500, p->x, p->y);
            g1_0b85(0x7d0L);
            g1_0042(0x10);
            continue;
        }
        if (p->flag == 0 && g1_3558(p->x, p->y) != 0) {
            g1_314c(p->x, p->y);
            p->flag = 1;
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(0x1f4L);
                g1_2a40(0x280, p->x, p->y);
            }
        }
        if (p->flag == 0)
            asm_0424(d_a0fb_ + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        else
            asm_0424(d_a0fb_ + 0x24e0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
    }
}

/* g1_7b68 */
void g1_7b68(void)
{
    register int i;
    struct g1_7b68_record far *p;

    for (i = 0; i < d_05ca; ++i) {
        p = &d_9818_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (g1_3513(p->x, p->y) != 0 && p->flag != 0) {
            p->state = 0;
            g1_2a40(0x640, p->x, p->y);
            g1_0b85(5000L);
            g1_0042(0x10);
            continue;
        }
        if (p->flag == 0 && g1_3558(p->x, p->y) != 0) {
            g1_314c(p->x, p->y);
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, p->x, p->y);
            }
            p->flag = 1;
        }
        if (p->flag == 0)
            asm_0424(d_a0fb_ + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        else
            asm_0424(d_a0fb_ + 0x2580,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
    }
}

/* g1_7cfa */
void g1_7cfa(void)
{
    register int i;
    struct t_726b far *p;

    d_06ef += 0xa0;
    if (d_06ef == 0x280)
        d_06ef = 0;
    for (i = 0; i < d_05cc; ++i) {
        p = &d_726b_[i];
        if (p[1].x == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        g1_3558(p->x, p->y);
        if (g1_3513(p->x + 1, p->y) != 0 &&
            d_d13f_ != 0 && g1_12ce() != 0)
            ++d_0099;
        if (g1_3513(p->x - 1, p->y) != 0 &&
            d_d4c0_ != 0 && g1_1247() != 0)
            --d_0099;
        asm_0424(d_a0fb_ + d_06ef + 0x28a0,
                 p->x - d_009d,
                 ((p->y - d_009f) >> 3) + 0x10);
        if (d_0437 == 0)
            g1_0042(0x15);
    }
}

/* g1_7dff */
void pascal g1_7dff(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x280;
    offset += 0x6680;

    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 2, a2) == 0)
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 - d_009d + 2,
                 ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 4, a2) == 0)
        asm_0424(d_637a_ + offset + 0x140,
                 a1 - d_009d + 4,
                 ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 6, a2) == 0)
        asm_0424(d_637a_ + offset + 0x1e0,
                 a1 - d_009d + 6,
                 ((a2 - d_009f) >> 3) + 0x10);

    if (g1_3513(a1 + 2, a2 - 0x40) != 0 ||
        g1_3513(a1 + 4, a2 - 0x40) != 0)
        d_6379_ = 1;
}

/* g1_7f4a */
void pascal g1_7f4a(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x280 + 0x6e00;
    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a_ + offset, a1 - d_009d, ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 2, a2) == 0)
        asm_0424(d_637a_ + offset + 0xa0, a1 - d_009d + 2, ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 4, a2) == 0)
        asm_0424(d_637a_ + offset + 0x140, a1 - d_009d + 4, ((a2 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 6, a2) == 0) {
        asm_0424(d_637a_ + offset + 0x1e0, a1 - d_009d + 6, ((a2 - d_009f) >> 3) + 0x10);
        g1_0042(0x16);
    }
}

/* g1_8069 */
void g1_8069(void)
{
    register int i;
    struct g1_8069_record far *p;

    d_06f1 = !d_06f1;
    for (i = 0; i < d_05ce; i++) {
        p = &d_5ec9_[i];
        if (p->f0 == 0)
            continue;

        if (g1_326e(p->f2, p->f4) == 0 && p->f6 == 0) {
            if (g1_3714(p->f2 + 3, p->f4 + 128))
                p->f6 = 24;
            else
                p->f6 = 1;
        }

        if (p->f6 == 0)
            continue;

        if (p->f6 > 2) {
            --p->f6;
            p->f4 -= 16;
        }
        if (p->fa > 1 && p->f6 <= 2) {
            p->f4 += 16;
            ++p->fa;
            if (p->fa >= 24 || g1_3714(p->f2 + 3, p->f4 + 128)) {
                p->f6 = 24;
                p->fa = 0;
            }
        }

        if (p->f2 + 3 > d_0099 + d_009d) {
            p->f0 = 2;
            if (d_0437 == 0 || d_0437 == 0x40) {
                if (g1_367e(p->f2 - 2, p->f4) == 0)
                    --p->f2;
            }
        } else if (p->f2 + 3 < d_0099 + d_009d) {
            p->f0 = 3;
            if (d_0437 == 0 || d_0437 == 0x40) {
                if (g1_367e(p->f2 + 8, p->f4) == 0)
                    ++p->f2;
            }
        } else {
            if (p->f6 < 3 && p->fa == 0)
                p->fa = 2;
            p->f0 = 1;
        }

        if (g1_3558(p->f2, p->f4) ||
            g1_3558(p->f2 + 8, p->f4) ||
            g1_3558(p->f2 + 4, p->f4 - 128)) {
            if (p->f8 != 0)
                --p->f8;
        }
        if (p->f8 < 4 && d_0437 == 0)
            g1_2e64(p->f2 + 3, p->f4 - 96);
        if (p->f8 < 3 && d_0437 == 0x20)
            g1_2e64(p->f2, p->f4 - 96);
        if (p->f8 < 2 && d_0437 == 0x40)
            g1_2e64(p->f2 + 2, p->f4 - 128);

        if (p->f8 == 0) {
            if (g1_3714(p->f2, p->f4 + 128) ||
                g1_3714(p->f2 + 8, p->f4 + 128)) {
                g1_314c(p->f2, p->f4);
                g1_314c(p->f2 + 2, p->f4 - 64);
                g1_314c(p->f2 + 4, p->f4);
                g1_314c(p->f2 + 6, p->f4 - 64);
                g1_314c(p->f2 + 8, p->f4);
                g1_2fe7(p->f2 + 1, p->f4 - 32);
                g1_2fe7(p->f2 + 5, p->f4 - 128);
                g1_2b86(1, p->f2 + 1, p->f4 - 32);
                g1_2b86(1, p->f2 + 7, p->f4 - 64);
                g1_2b86(1, p->f2 + 1, p->f4 - 32);
                g1_2b86(1, p->f2 + 2, p->f4 - 128);
                g1_2b86(1, p->f2 + 3, p->f4 - 128);
                g1_2b86(1, p->f2 + 5, p->f4 - 32);
                p->f0 = 0;
                g1_0b85(5000L);
                continue;
            }
            p->f4 += 32;
        }

        switch (p->f0) {
        case 2:
            g1_7f4a(d_06f1, p->f2, p->f4 - 128);
            g1_7dff(0, p->f2, p->f4);
            break;
        case 1:
            g1_7f4a(d_06f1 + 2, p->f2, p->f4 - 128);
            g1_7dff(1, p->f2, p->f4);
            break;
        case 3:
            g1_7f4a(d_06f1 + 4, p->f2, p->f4 - 128);
            g1_7dff(2, p->f2, p->f4);
            break;
        }
    }
}

/* g1_8506 */
void g1_8506(void)
{
    register int i;
    struct g1_8506_record far *p;

    for (i = 0; i < d_05d0; i++) {
        p = &d_7cac_[i];
        if (p->state == 0)
            continue;

        if (p->state == 1) {
            if (g1_3714(p->x, p->y + 128) == 0)
                p->y += 64;
            if (g1_326e(p->x, p->y) == 0) {
                asm_0424(d_a0fb_ + 0x3e80,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
                if (g1_3558(p->x, p->y) != 0) {
                    g1_314c(p->x, p->y);
                    if (g1_3714(p->x, p->y + 128) == 0) {
                        g1_0b85(0x1f4L);
                        g1_2a40(0x280, p->x, p->y);
                    }
                    p->state = 2;
                }
            }
            continue;
        }

        if (d_0437 == 0)
            d_06f3 += 0xa0;
        if (d_06f3 == 0x1e0)
            d_06f3 = 0;

        if (g1_3714(p->x, p->y - 128) == 0)
            p->y -= 8;
        if (g1_3558(p->x, p->y - 128) != 0 || g1_3714(p->x, p->y - 128) != 0) {
            if (g1_326e(p->x, p->y - 128) == 0)
                asm_0424(d_a0fb_ + 0x2da0,
                         p->x - d_009d,
                         (p->y - d_009f) >> 3);
            p->state = 0;
            g1_2e64(p->x, p->y - 128);
            continue;
        }
        if (g1_326e(p->x, p->y - 128) == 0)
            asm_0424(d_a0fb_ + 0x2b20,
                     p->x - d_009d,
                     (p->y - d_009f) >> 3);
        if (g1_326e(p->x, p->y) == 0)
            asm_0424(d_a0fb_ + d_06f3 + 0x2bc0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        if (g1_3513(p->x, p->y) != 0) {
            g1_0b85(10000L);
            g1_2a40(0x780, p->x, p->y - 128);
            g1_0042(3);
            p->state = 0;
        }
    }
}

/* g1_87bf */
void g1_87bf(void)
{
    register int i;
    struct g1_87bf_record far *p;

    d_4ed6_ = 1;
    for (i = 0; i < d_05d2; ++i) {
        p = &d_68fc_[i];
        if (p->state == 0)
            continue;

        d_4ed6_ = 0;
        if (g1_326e(p->x, p->y) != 0)
            continue;

        if (p->x - 2 > d_0099 + d_009d) {
            asm_0424(d_637a_ + 0x7d00,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else if (p->x + 2 < d_0099 + d_009d) {
            asm_0424(d_637a_ + 0x7e40,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_637a_ + 0x7da0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }

        if (g1_3558(p->x, p->y) != 0) {
            g1_2a40(0, p->x, p->y);
            g1_0b85(100L);
            g1_2b86(1, p->x, p->y);
            p->state = 0;
            g1_0042(0x12);
        }
    }
}

/* g1_892b */
void g1_892b(void)
{
    register unsigned int i;
    struct g1_892b_record far *p;
    for (i = 0; i < d_05d4; ++i) {
        p = &d_7f06_[i];
        if (g1_326e(p->x, p->y) == 0)
            asm_0424((d_637a_ + p->offset),
                    p->x - d_009d,
                    ((p->y - d_009f) >> 3) + 16);
    }
}

/* g1_899e */
void g1_899e(void)
{
    register unsigned int si;
    struct g1_899e_record far *p;

    d_06f5 += 0xa0;
    if (d_06f5 == 0x5a0)
        d_06f5 = 0;

    for (si = 0; si < d_05d6; ++si) {
        p = &d_7063_[si];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;

        if (p->state == 1) {
            if (g1_3558(p->x, p->y) != 0) {
                g1_314c(p->x, p->y);
                p->state = 2;
                if (g1_3714(p->x, p->y + 0x80) == 0) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
            }
        }

        if (p->state == 2 && g1_3513(p->x, p->y) != 0) {
            p->state = 0;
            d_4ed4_ = 9;
            g1_0b85(1000L);
            g1_2a40(0x3c0, p->x, p->y);
            g1_0a0e();
            g1_0042(4);
            if (d_5ec8_ != 0) {
                d_5ec8_ = 0;
                g2_165e();
            }
            continue;
        }

        if (p->state == 1) {
            asm_0424(d_a0fb_,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb_ + d_06f5 + 0x2e40,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_8b5b */
void g1_8b5b(void)
{
    struct record far *p;
    register int i;

    d_531c_ = 1;
    for (i = 0; i < d_05d8; ++i) {
        p = &d_c691_[i];
        if (p->state == 0)
            continue;
        d_531c_ = 0;
        if (g1_326e(p->x, p->y) && g1_326e(p->x, p->y)) {
            if (p->state > 15) {
                p->state = 0;
                continue;
            } else {
                continue;
            }
        } else {
            if (p->state > 1) {
                if (g1_3714(p->x + 1, p->y + 0x80)) {
                    g1_314c(p->x + 1, p->y);
                    g1_2e64(p->x + 1, p->y);
                    p->state = 0;
                    continue;
                }
                ++p->state;
            }
            if (p->state < 2) {
                if (p->x - 1 <= d_0099 + d_009d &&
                    p->x + 3 >= d_0099 + d_009d &&
                    ((d_009b >> 4) << 7) + d_009f - p->y < 0x400 &&
                    ((d_009b >> 4) << 7) + d_009f - p->y > 0)
                    p->state = 2;
            }
            if (p->state == 16)
                g1_0042(0x20);
            if (p->state > 15) {
                p->y += 0x60;
                if (g1_3513(p->x, p->y) || g1_3513(p->x + 2, p->y))
                    d_6379_ = 1;
                if (g1_3558(p->x, p->y - 0x40) ||
                    g1_3558(p->x + 2, p->y - 0x40)) {
                    g1_314c(p->x + 1, p->y);
                    g1_2e64(p->x + 1, p->y);
                    g1_2b86(1, p->x + 1, p->y);
                    g1_0b85(0x1f4L);
                    g1_2a40(0x280, p->x + 1, p->y);
                    p->state = 0;
                    continue;
                }
            }
        }
        if (p->state == 1 || p->state >= 15) {
            if (!g1_326e(p->x, p->y))
                asm_0424(d_a0fb_ + 0x33e0,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (!g1_326e(p->x + 2, p->y))
                asm_0424(d_a0fb_ + 0x3480,
                         p->x - d_009d + 2,
                         ((p->y - d_009f) >> 3) + 0x10);
        }
        if (p->state >= 15)
            continue;
        if (!g1_326e(p->x, p->y))
            asm_0424(d_a0fb_ + 0x33e0,
                     p->x - d_009d,
                     (p->state % 2) + ((p->y - d_009f) >> 3) + 0x10);
        if (g1_326e(p->x + 2, p->y))
            continue;
        asm_0424(d_a0fb_ + 0x3480,
                 p->x - d_009d + 2,
                 (p->state % 2) + ((p->y - d_009f) >> 3) + 0x10);
    }
}

/* g1_8ec1 */
void g1_8ec1(void)
{
    register int i;
    register int event;

    event = 0;
    d_06f7 += 0xa0;
    if (d_06f7 == 0x320)
        d_06f7 = 0;
    if (g1_326e(d_c68d_, d_c68f_) != 0) {
        if (d_d572_ < 2)
            return;
        d_d572_ = 0;
        for (i = 0; i < d_05c2; ++i)
            d_b3d6_[i].used = 0;
        return;
    }

    if (d_c8e9_ != 0 && d_d572_ == 0)
        return;

    if (g1_3558(d_c68d_, d_c68f_) != 0) {
        --d_d56e_;
        g1_314c(d_c68d_, d_c68f_);
        if (d_d56e_ == 0)
            d_c8e9_ = 1;
        event = 1;
        g1_0042(0xa);
    }
    if (g1_3558(d_c68d_, d_c68f_ - 0x80) != 0) {
        --d_d56e_;
        g1_314c(d_c68d_, d_c68f_ - 0x80);
        if (d_d56e_ == 0)
            d_c8e9_ = 1;
        event = 1;
        g1_0042(0xa);
    }
    if (g1_3558(d_c68d_, d_c68f_ - 0x100) != 0) {
        --d_d56e_;
        g1_314c(d_c68d_, d_c68f_ - 0x100);
        if (d_d56e_ == 0)
            d_c8e9_ = 1;
        event = 1;
        g1_0042(0xa);
    }

    if (d_c8e9_ == 0) {
        g1_0042(0x24);
        if (event == 0) {
            asm_0424(d_a0fb_ + d_06f7 + 0x3840,
                     d_c68d_ - d_009d,
                     ((d_c68f_ - d_009f) >> 3) + 0x10);
            if (g1_326e(d_c68d_, d_c68f_ - 0x80) == 0)
                asm_0424(d_a0fb_ + d_06f7 + 0x3840,
                         d_c68d_ - d_009d,
                         (d_c68f_ - d_009f) >> 3);
            if (g1_326e(d_c68d_, d_c68f_ - 0x100) == 0)
                asm_0424(d_a0fb_ + d_06f7 + 0x3840,
                         d_c68d_ - d_009d,
                         ((d_c68f_ - d_009f) >> 3) - 0x10);
        } else {
            asm_0424(d_637a_ + 0x9f60,
                     d_c68d_ - d_009d,
                     ((d_c68f_ - d_009f) >> 3) + 0x10);
            if (g1_326e(d_c68d_, d_c68f_ - 0x80) == 0)
                asm_0424(d_637a_ + 0x9f60,
                         d_c68d_ - d_009d,
                         (d_c68f_ - d_009f) >> 3);
            if (g1_326e(d_c68d_, d_c68f_ - 0x100) == 0)
                asm_0424(d_637a_ + 0x9f60,
                         d_c68d_ - d_009d,
                         ((d_c68f_ - d_009f) >> 3) - 0x10);
        }
        if (g1_3513(d_c68d_, d_c68f_ - 0x40) != 0) {
            if (d_4ed4_ > 0) {
                d_4ed4_ = 0;
                g1_0a0e();
            }
        }
        return;
    }

    asm_0424(d_a0fb_ + 0x3840,
             d_c68d_ - d_009d,
             ((d_c68f_ - d_009f) >> 3) + 0x10);
    if (g1_326e(d_c68d_, d_c68f_ - 0x80) == 0)
        asm_0424(d_a0fb_ + 0x3840,
                 d_c68d_ - d_009d,
                 (d_c68f_ - d_009f) >> 3);
    if (g1_326e(d_c68d_, d_c68f_ - 0x100) == 0)
        asm_0424(d_a0fb_ + 0x3840,
                 d_c68d_ - d_009d,
                 ((d_c68f_ - d_009f) >> 3) - 0x10);
    ++d_d572_;
    if (d_0437 == 0)
        g1_2e64(d_c68d_ - 1, d_c68f_);
    if (d_0437 == 0x40)
        g1_2e64(d_c68d_ + 1, d_c68f_);
    if (d_d572_ == 0x20) {
        d_d572_ = 0;
        for (i = 0; i < d_05c2; ++i)
            d_b3d6_[i].used = 0;
        g1_0b85(0x4e20L);
        g1_0042(0x11);
        return;
    }
    if (d_0437 == 0)
        return;

    switch (d_d572_) {
    case 2:
        g1_2b86(1, d_c68d_ - 1, d_c68f_);
        break;
    case 8:
        g1_2b86(1, d_c68d_ - 2, d_c68f_ - 0x80);
        break;
    case 10:
        g1_2b86(1, d_c68d_ + 1, d_c68f_ + 0x100);
        break;
    case 13:
        g1_2b86(1, d_c68d_, d_c68f_ + 0x80);
        g1_2b86(1, d_c68d_ - 1, d_c68f_ + 0x180);
        g1_2b86(1, d_c68d_, d_c68f_ - 0x180);
        g1_2b86(3, d_c68d_ + 2, d_c68f_);
        g1_2b86(3, d_c68d_, d_c68f_ + 0x80);
        break;
    case 15:
        g1_2b86(1, d_c68d_ + 2, d_c68f_ - 0x80);
        break;
    case 17:
        g1_2b86(1, d_c68d_ + 1, d_c68f_ + 0x100);
        g1_2b86(1, d_c68d_ + 2, d_c68f_);
        g1_2b86(1, d_c68d_ - 3, d_c68f_ - 0x100);
        g1_314c(d_c68d_ - 1, d_c68f_);
        break;
    case 18:
        g1_314c(d_c68d_ + 3, d_c68f_ - 0x100);
        g1_2b86(1, d_c68d_ + 1, d_c68f_ + 0x100);
        break;
    case 23:
        g1_2fe7(d_c68d_, d_c68f_ + 0x40);
        g1_2fe7(d_c68d_ - 1, d_c68f_ - 0x40);
        g1_2b86(3, d_c68d_, d_c68f_ + 0x80);
        g1_314c(d_c68d_ + 2, d_c68f_);
        g1_314c(d_c68d_ - 1, d_c68f_ + 0x180);
        g1_2b86(1, d_c68d_ - 1, d_c68f_ + 0x180);
        g1_2b86(3, d_c68d_, d_c68f_ - 0x180);
        g1_2b86(3, d_c68d_ + 2, d_c68f_ - 0x80);
        g1_2b86(1, d_c68d_ + 1, d_c68f_ + 0x100);
        break;
    case 24:
        g1_314c(d_c68d_ + 1, d_c68f_ + 0x80);
        g1_314c(d_c68d_ - 2, d_c68f_ - 0x100);
        g1_2b86(1, d_c68d_ + 2, d_c68f_);
        g1_2b86(3, d_c68d_ - 3, d_c68f_ - 0x100);
        g1_314c(d_c68d_ - 1, d_c68f_);
        g1_314c(d_c68d_ + 3, d_c68f_ - 0x100);
        g1_2b86(1, d_c68d_ - 1, d_c68f_);
        g1_2b86(3, d_c68d_ - 2, d_c68f_ - 0x80);
        g1_2b86(1, d_c68d_ + 1, d_c68f_ + 0x100);
        break;
    case 29:
        g1_2fe7(d_c68d_ + 3, d_c68f_ - 0x80);
        g1_2fe7(d_c68d_ + 2, d_c68f_ + 0x100);
        g1_2b86(1, d_c68d_, d_c68f_ + 0x80);
        g1_314c(d_c68d_ + 2, d_c68f_);
        g1_314c(d_c68d_ - 1, d_c68f_ + 0x180);
        g1_2b86(3, d_c68d_ - 1, d_c68f_ + 0x180);
        g1_2b86(1, d_c68d_, d_c68f_ - 0x180);
        g1_2b86(3, d_c68d_ + 2, d_c68f_ - 0x80);
        g1_2b86(1, d_c68d_ + 1, d_c68f_ + 0x100);
        break;
    case 31:
        g1_2fe7(d_c68d_ - 2, d_c68f_ - 0x180);
        g1_314c(d_c68d_ + 1, d_c68f_ + 0x80);
        g1_314c(d_c68d_, d_c68f_);
        g1_2b86(3, d_c68d_ + 2, d_c68f_);
        g1_2b86(3, d_c68d_ - 3, d_c68f_ - 0x100);
        g1_314c(d_c68d_ - 1, d_c68f_);
        g1_314c(d_c68d_ + 3, d_c68f_ - 0x100);
        g1_2b86(1, d_c68d_ - 1, d_c68f_);
        g1_2b86(1, d_c68d_ - 2, d_c68f_ - 0x80);
        g1_2b86(3, d_c68d_ + 1, d_c68f_ + 0x100);
        g1_2a40(0x780, d_c68d_ - 1, d_c68f_);
        g1_2a40(0x780, d_c68d_ + 1, d_c68f_);
        break;
    }
}

/* g1_9698 */
void g1_9698(void)
{
    register int i;
    struct g1_9698_record far *p;

    for (i = 0; i < d_05da; ++i) {
        p = &d_9688_[i];
        if (g1_326e(p->x, p->y) == 0) {
            if (g1_3513(p->x, p->y)) {
                d_6379_ = 1;
                asm_0424(d_a0fb_ + 0x3c00,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            } else {
                asm_0424(d_a0fb_ + 0x3b60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
        }
    }
}

/* g1_9757 */
void g1_9757(void)
{
    register int i;
    struct g1_9757_row far *p;

    d_06f9 += 0xa0;
    if (d_06f9 == 0x1e0)
        d_06f9 = 0;
    for (i = 0; i < d_05dc; i++) {
        p = &d_c915_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (p->state == 1 && g1_3558(p->x, p->y)) {
            g1_314c(p->x, p->y);
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(0x1f4L);
                g1_2a40(0x280, p->x, p->y);
            }
            p->state = 2;
        }
        if (p->state == 2 && g1_3513(p->x, p->y) != 0) {
            p->state = 0;
            g1_0042(0x10);
            switch (d_0437) {
            case 0:
                g1_0b85(0x64L);
                g1_2a40(0, p->x, p->y);
                break;
            case 0x20:
                g1_0b85(0x1f4L);
                g1_2a40(0x280, p->x, p->y);
                break;
            case 0x40:
                g1_0b85(0x7d0L);
                g1_2a40(0x500, p->x, p->y);
                break;
            case 0x60:
                g1_0b85(0x1388L);
                g1_2a40(0x640, p->x, p->y);
                break;
            default:
                continue;
            }
            continue;
        }
        if (p->state == 1) {
            asm_0424(d_a0fb_ + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb_ + d_06f9 + 0x3ca0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_9986 */
void g1_9986(void)
{
    register int si;
    struct g1_9986_record far *p;

    d_06fb += 0xa0;
    if (d_06fb == 0x1e0)
        d_06fb = 0;

    si = 0;
    for (; si < d_05de; ++si) {
        p = &d_6e0b_[si];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;

        if (p->state == 1) {
            if (g1_3558(p->x, p->y) != 0) {
                g1_314c(p->x, p->y);
                if (g1_3714(p->x, p->y + 0x80) == 0) {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                }
                p->state = 2;
            }
        }

        if (p->state == 2) {
            if (g1_3513(p->x, p->y) != 0) {
            p->state = 0;
            g1_0042(0x10);
            switch (d_0437) {
            case 0:
                g1_0b85(100L);
                g1_2a40(0, p->x, p->y);
                break;
            case 0x20:
                g1_0b85(500L);
                g1_2a40(0x280, p->x, p->y);
                break;
            case 0x40:
                g1_0b85(2000L);
                g1_2a40(0x500, p->x, p->y);
                break;
            case 0x60:
                g1_0b85(5000L);
                g1_2a40(0x640, p->x, p->y);
                break;
            }
            continue;
            }
        }

        if (p->state == 1) {
            asm_0424(d_a0fb_ + 0x3e80,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb_ + d_06fb + 0x3fc0,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_9bb5 */
void pascal g1_9bb5(int a2, register int a1, register int a0)
{
    ++d_06fd;
    if (d_06fd == 3)
        d_06fd = 0;

    if (g1_326e(a1, a0 - 0x100) == 0)
        asm_0424(d_637a_ + 0x8480, a1 - d_009d,
                 ((a0 - d_009f) >> 3) - 0x10);
    if (g1_326e(a1 + 4, a0 - 0x100) == 0)
        asm_0424(d_637a_ + 0x85c0, a1 - d_009d + 4,
                 ((a0 - d_009f) >> 3) - 0x10);
    if (g1_326e(a1, a0 - 0x80) == 0)
        asm_0424(d_637a_ + 0x8660, a1 - d_009d,
                 (a0 - d_009f) >> 3);
    if (g1_326e(a1 + 2, a0 - 0x80) == 0)
        asm_0424(d_637a_ + 0x8700, a1 - d_009d + 2,
                 (a0 - d_009f) >> 3);
    if (g1_326e(a1 + 4, a0 - 0x80) == 0)
        asm_0424(d_637a_ + 0x87a0, a1 - d_009d + 4,
                 (a0 - d_009f) >> 3);
    if (g1_326e(a1, a0) == 0)
        asm_0424(d_637a_ + 0x8840, a1 - d_009d,
                 ((a0 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 2, a0) == 0)
        asm_0424(d_637a_ + 0x88e0, a1 - d_009d + 2,
                 ((a0 - d_009f) >> 3) + 0x10);
    if (g1_326e(a1 + 4, a0) == 0)
        asm_0424(d_637a_ + 0x8980, a1 - d_009d + 4,
                 ((a0 - d_009f) >> 3) + 0x10);

    switch (d_06fd) {
    case 0:
        if (g1_326e(a1 + 2, a0 - 0x80) == 0)
            asm_0424(d_637a_ + 0x8700, a1 - d_009d + 2,
                     (a0 - d_009f) >> 3);
        if (g1_326e(a1 + 4, a0 - 0x80) == 0)
            asm_0424(d_637a_ + 0x87a0, a1 - d_009d + 4,
                     (a0 - d_009f) >> 3);
        break;
    case 1:
        if (g1_326e(a1 + 2, a0 - 0x80) == 0)
            asm_0424(d_637a_ + 0x8c00, a1 - d_009d + 2,
                     (a0 - d_009f) >> 3);
        if (g1_326e(a1 + 4, a0 - 0x80) == 0)
            asm_0424(d_637a_ + 0x8d40, a1 - d_009d + 4,
                     (a0 - d_009f) >> 3);
        break;
    case 2:
        if (g1_326e(a1 + 2, a0 - 0x80) == 0)
            asm_0424(d_637a_ + 0x8ca0, a1 - d_009d + 2,
                     (a0 - d_009f) >> 3);
        if (g1_326e(a1 + 4, a0 - 0x80) == 0)
            asm_0424(d_637a_ + 0x8de0, a1 - d_009d + 4,
                     (a0 - d_009f) >> 3);
        break;
    }
    switch (a2) {
    case 0:
    case 2:
        if (g1_326e(a1 + 2, a0 - 0x100) == 0)
            asm_0424(d_637a_ + 0x8520, a1 - d_009d + 2,
                     ((a0 - d_009f) >> 3) - 0x10);
        break;
    case 1:
        if (g1_326e(a1 + 2, a0 - 0x100) == 0)
            asm_0424(d_637a_ + 0x8a20, a1 - d_009d + 2,
                     ((a0 - d_009f) >> 3) - 0x10);
        break;
    case 3:
        if (g1_326e(a1 + 2, a0 - 0x100) == 0)
            asm_0424(d_637a_ + 0x8ac0, a1 - d_009d + 2,
                     ((a0 - d_009f) >> 3) - 0x10);
        break;
    }
}

/* g1_a032 */
void g1_a032(void)
{
    if (d_c684_ != 0) {
        if (d_d139_ == 1) {
            d_d139_ = 0;
            d_009d = d_c27b_ - d_0099 + 2;
            d_009f = d_c28d_ - 0x300;
            d_0644 = 1;
            d_c68c_ = 0;
            d_c68a_ = 8;
            d_c686_ = 0;
        }

        if (d_d139_ > 1)
            --d_d139_;
        if (d_c686_ > 0) {
            g1_9bb5(d_c686_ % 4, d_c279_, d_c28b_);
            --d_c686_;
        } else {
            g1_9bb5(d_d139_ % 4, d_c279_, d_c28b_);
        }

        if (d_68f7_ != 0) {
            if (g1_3513(d_c279_ + 2, d_c28b_)) {
                d_68f7_ = 0;
                g2_18b8();
            }
        }
        if (g1_3513(d_c279_ + 2, d_c28b_)) {
            if (d_c68c_ != 0 && d_d139_ == 0 && d_d13f_ == 0 &&
                d_d4c0_ == 0 && d_d138_ == 0) {
                d_d139_ = 8;
                g1_0042(7);
            }
        }
    }
}

/* g1_a125 */
void g1_a125(void)
{
    if (d_c688_ == 0)
        return;

    if (d_d13b_ == 1) {
        d_d13b_ = 0;
        d_009d = d_c279_ - d_0099 + 2;
        d_009f = d_c28b_ + 0xfd00;
        d_0644 = 1;
        d_c68c_ = 0;
        d_c686_ = 8;
        d_c68a_ = 0;
    }

    if (d_d13b_ > 1)
        --d_d13b_;

    if (d_c68a_ > 0)
        {
            g1_9bb5(d_c68a_ % 4, d_c27b_, d_c28d_);
            --d_c68a_;
        }
    else
        g1_9bb5(d_d13b_ % 4, d_c27b_, d_c28d_);

    if (d_68f7_ != 0 && g1_3513(d_c27b_ + 2, d_c28d_)) {
        d_68f7_ = 0;
        g2_18b8();
    }

    if (!g1_3513(d_c27b_ + 2, d_c28d_))
        return;

    if (d_c68c_ != 0 && d_d13b_ == 0 && d_d13f_ == 0 &&
        d_d4c0_ == 0 && d_d138_ == 0) {
        d_d13b_ = 8;
        g1_0042(7);
    }
}

/* g1_a218 */
void g1_a218(void)
{
    register int i;
    struct g1_a218_record far *p;

    for (i = 0; i < d_05e0; ++i) {
        p = &d_ae44_[i];
        if (g1_326e(p->x, p->y) == 0) {
            p->y -= d_05e2[p->state + 6];
            ++p->state;
            if (p->state == 8)
                p->state = -6;
            if (p->state == -6)
                g1_0042(0x22);
            if (g1_3513(p->x, p->y))
                d_6379_ = 1;
            g1_3558(p->x, p->y);
            if (g1_326e(p->x, p->y) == 0)
                asm_0424(d_637a_ + 0x8b60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_a30a */
void g1_a30a(void)
{
    register int i;
    struct g1_a30a_record far *p;

    i = 0;
    while (i < d_5004_) {
        p = &d_5c6c_[i];
        if (p->used != 0) {
            if (g1_326e(p->x, p->y) == 0) {
                if (g1_3714(p->x, p->y + 0x80) == 0)
                    p->y += 0x40;
                if (g1_3513(p->x, p->y) != 0) {
                    p->used = 0;
                    d_6379_ = 1;
                    g1_2b86(2, p->x, p->y);
                    g1_0042(0x21);
                }
                asm_0424(d_637a_ + 0x8b60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
        }
        ++i;
    }
}

/* g1_a3e7 */
void g1_a3e7(void)
{
    register int i;

    if (d_7f04_ == -1)
        return;
    if (g1_326e(d_9d96_, d_a0b9_) != 0)
        return;

    if (d_7f04_ == 0) {
        asm_0424(d_a0fb_ + 0x46a0,
                 d_9d96_ - d_009d,
                 ((d_a0b9_ - d_009f) >> 3) + 0x10);
        return;
    }

    d_06fe += 0xa0;
    if (d_06fe == 0x500)
        d_06fe = 0;

    asm_0424(d_a0fb_ + d_06fe + 0x41a0,
             d_9d96_ - d_009d,
             ((d_a0b9_ - d_009f) >> 3) + 0x10);

    if (g1_3513(d_9d96_, d_a0b9_) != 0 && d_5553_ != 0) {
        d_5553_ = 0;
        g2_1821();
    }

    if (g1_3513(d_9d96_, d_a0b9_) != 0 && d_b3d4_ != 0 && d_c68c_ != 0) {
        for (i = 0; i < d_05cc; ++i)
            (&d_726b_[i].x)[2] = 0;      /* the original clears the NEXT record's x */

        d_7f04_ = 0;
        g2_3b79();
        g1_0042(0x1f);
        d_053c = 0;
        d_b3d4_ = 0;
    }

    if (g1_3513(d_9d96_, d_a0b9_) != 0 &&
        d_b3d4_ == 0 && d_c68c_ != 0 &&
        d_7f04_ != 0 && d_5555_ != 0)
        g2_1a82();
}

/* g1_a53a */
void g1_a53a(void)
{
    if (d_5307_ == 0)
        return;

    if (g1_326e(d_d13d_ - 2, d_d140_) == 0) {
        asm_0424(d_a0fb_ + 0x4880,
                 d_d13d_ - d_009d - 2,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    }

    if (g1_326e(d_d13d_ + 2, d_d140_) == 0) {
        asm_0424(d_a0fb_ + 0x4920,
                 d_d13d_ - d_009d + 2,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    }

    if (g1_326e(d_d13d_, d_d140_) != 0) {
        d_52db_ = 0;
        return;
    }

    if (g1_3513(d_d13d_, d_d140_) != 0 && d_555c_ != 0) {
        d_555c_ = 0;
        g2_178a();
    }

    if (g1_3513(d_d13d_, d_d140_) != 0) {
        if (d_c68c_ != 0 && d_5149_ == 0) {
            if (d_cc82_ != 0) {
                d_5149_ = 1;
                d_5000_ = 1;
                g1_0042(5);
            } else {
                d_52db_ = 1;
            }
        }
    }

    if (d_5149_ == 0 && d_0437 == 0) {
        asm_0424(d_a0fb_ + 0x4740,
                 d_d13d_ - d_009d,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    } else {
        asm_0424(d_a0fb_ + 0x47e0,
                 d_d13d_ - d_009d,
                 ((d_d140_ - d_009f) >> 3) + 0x10);
    }

    if (d_52db_ != 0) {
        if (d_0437 == 0)
            g1_1b8a(1, d_d13d_ + 2, d_d140_ - 36);
        if (d_0437 == 0x40)
            g1_1b8a(2, d_d13d_ - 2, d_d140_ - 36);
    }
}

/* g1_a6f4 */
void g1_a6f4(void)
{
    if (d_5316_ == 0) return;
    if (d_5000_ == 0) return;
    g1_2b86(3, d_d574_ + 2, d_d577_);
    if (*(d_7729_ + d_d577_ + (d_d574_ >> 1)) == 0x2fe0U) {
        d_5316_ = 0;
        d_5000_ = 0;
    } else {
        *(d_7729_ + d_d577_ + (d_d574_ >> 1)) = 0x2fe0U;
    }
    d_d574_ += 2;
}

/* g1_a75c */
void g1_a75c(void)
{
    register int i;
    struct g1_a75c_record far *p;

    for (i = 0; i < d_5309_; i++) {
        p = &d_a0bf_[i];
        if (p->state == 0)
            continue;
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (g1_3714(p->x, p->y + 0x80) == 0)
            p->y += 0x80;
        if (p->flag == 0 && g1_3558(p->x, p->y) != 0) {
            g1_314c(p->x, p->y);
            if (g1_3714(p->x, p->y + 0x80) == 0) {
                g1_0b85(500L);
                g1_2a40(0x280, p->x, p->y);
            }
            p->flag = 1;
        }
        if (p->flag != 0) {
            if (g1_3513(p->x, p->y) != 0) {
                if (p->state != 'E') {
                    d_d149_[d_d57a_++] = p->state;
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                    g1_0042(0x10);
                } else if (d_d57a_ == 3 && d_d149_[0] == 'D' &&
                           d_d14b_ == 'U' && d_d14d_ == 'K') {
                    g1_0b85(10000L);
                    g1_2a40(0x780, p->x, p->y);
                    g1_0042(0x25);
                    d_530c_ = 1;
                } else {
                    g1_0b85(500L);
                    g1_2a40(0x280, p->x, p->y);
                    g1_0042(0x10);
                }
                p->state = 0;
            }
        }
        if (g1_326e(p->x, p->y) != 0)
            continue;
        if (p->flag == 0) {
            asm_0424(d_a0fb_, p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            if (p->state == 'D')
                asm_0424(d_a0fb_ + 0x49c0, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (p->state == 'U')
                asm_0424(d_a0fb_ + 0x4a60, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (p->state == 'K')
                asm_0424(d_a0fb_ + 0x4b00, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            if (p->state == 'E')
                asm_0424(d_a0fb_ + 0x4ba0, p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_aa1b */
void pascal g1_aa1b(int a0, register int a1, int a2)
{
    register int offset;

    if (a0 <= 2)
        offset = a0 * 0x140 + 0x4740;
    else
        offset = (a0 - 3) * 0x140 + 0x8e80;

    if (g1_326e(a1, a2 - 0x80) == 0)
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);

    if (g1_326e(a1, a2) == 0)
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
}

/* g1_aac2 */
void g1_aac2(void)
{
    register int i;
    struct g1_aac2_record far *p;

    d_5312_ = 1;
    for (i = 0; i < d_0600; ++i) {
        p = &d_73fb_[i];
        if (p->state == 0)
            continue;

        d_5312_ = 0;
        if (p->state > 2) {
            switch (p->kind) {
            case 0:
                g1_aa1b(0, p->x, p->y);
                break;
            case 1:
                g1_aa1b(6, p->x, p->y);
                break;
            case 2:
                g1_aa1b(3, p->x, p->y);
                break;
            case 3:
                g1_aa1b(7, p->x, p->y);
                break;
            }
            ++p->state;
            ++p->kind;
            if (p->kind == 4)
                p->kind = 0;
            if (p->state == 0x14) {
                p->state = 0;
                g1_2e64(p->x, p->y);
                g1_2e64(p->x, p->y - 0x80);
                g1_2e64(p->x - 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0xc0);
                g1_2e64(p->x - 1, p->y);
                g1_0b85(5000L);
                g1_2a40(0x640, p->x, p->y);
                continue;
            }
        } else {
            if (!g1_3714(p->x, p->y + 0x80)) {
                p->y += 0x40;
            } else {
                if (g1_367e(p->x - 1, p->y) && p->state == 1) {
                    p->state = 2;
                    p->kind = 0;
                } else if (g1_367e(p->x + 2, p->y) && p->state == 2) {
                    p->state = 1;
                    p->kind = 0;
                }
            }

            if (p->kind == 0) {
                if (p->state == 1)
                    g1_aa1b(6, p->x, p->y);
                if (p->state == 2)
                    g1_aa1b(7, p->x, p->y);
                if (d_0437 != 0x40 && d_0437 != 0)
                    continue;
                p->kind = 1;
                continue;
            }

            if (p->state == 1) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    --p->x;
                if (p->kind < 3)
                    g1_aa1b(p->kind, p->x, p->y);
                else
                    g1_aa1b(5 - p->kind, p->x, p->y);
                if (d_0437 == 0 || d_0437 == 0x40) {
                    if (g1_3714(p->x, p->y + 0x80))
                        ++p->kind;
                    if (p->kind == 6)
                        p->kind = 1;
                }
            }

            if (p->state == 2) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    ++p->x;
                if (p->kind < 3)
                    g1_aa1b(p->kind + 2, p->x, p->y);
                else
                    g1_aa1b(8 - p->kind, p->x, p->y);
                if (d_0437 == 0 || d_0437 == 0x40) {
                    if (g1_3714(p->x, p->y + 0x80))
                        ++p->kind;
                    if (p->kind == 6)
                        p->kind = 1;
                }
            }

            if (g1_3558(p->x, p->y)) {
                p->state = 0;
                g1_2e64(p->x, p->y);
                g1_2e64(p->x, p->y - 0x80);
                g1_2e64(p->x - 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0x40);
                g1_2e64(p->x + 1, p->y - 0xc0);
                g1_2e64(p->x - 1, p->y);
                g1_0042(0x12);
                g1_0b85(200L);
                continue;
            }
            if (g1_3513(p->x, p->y)) {
                d_6379_ = 1;
                g1_0042(0x23);
                p->state = 3;
                p->kind = 0;
            }
        }
    }
}

/* g1_af06 */
void pascal g1_af06(int a2, int a1, int a0)
{
    register int row;
    register int col;

    col = a1;
    row = a2 * 0x140;
    row += 0x9600;
    if (g1_326e(a1, a0 - 0x80) == 0)
        asm_0424(d_637a_ + row, col - d_009d, (a0 - d_009f) >> 3);
    if (g1_326e(col, a0) == 0)
        asm_0424(d_637a_ + row + 0xa0, col - d_009d, ((a0 - d_009f) >> 3) + 0x10);
}

/* g1_af94 */
void g1_af94(void)
{
    register int i;
    struct g1_af94_record far *p;

    if (d_0437 == 0 || d_0437 == 0x40)
        ++d_0700;
    if (d_0700 == 3)
        d_0700 = 0;

    for (i = 0; i < d_05fe; ++i) {
        p = &d_a680_[i];
        if (p->state != 0) {
            if (g1_3714(p->x, p->y + 0x80) == 0)
                p->y += 0x40;
            if (g1_367e(p->x - 1, p->y) != 0 ||
                g1_3714(p->x - 2, p->y + 0x80) == 0)
                p->state = 2;
            if (g1_367e(p->x + 2, p->y) != 0 ||
                g1_3714(p->x + 2, p->y + 0x80) == 0)
                p->state = 1;

            if (p->state == 1) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    --p->x;
                g1_af06(d_0700, p->x, p->y);
            }
            if (p->state == 2) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    ++p->x;
                g1_af06(d_0700 + 3, p->x, p->y);
            }
            g1_3558(p->x, p->y);
            if (g1_3513(p->x, p->y) != 0)
                d_6379_ = 1;
        }
    }
}

/* g1_b118 */
void g1_b118(void)
{
    register int si;

    si = d_02fa;
    si <<= 2;
    g2_3d8c(2, 1, 3);
    g2_37b6(d_0ba1[si], 3, 3);
    g2_37b6(d_0ba1[si + 1], 3, 4);
    g2_37b6(d_0ba1[si + 2], 3, 5);
    g2_37b6(d_0ba1[si + 3], 3, 6);
    g2_37b6("      Press ENTER:      ", 3, 8);
    enable();
    do {
        g2_2870(0x1a, 8);
    } while (d_a0fa_ != 0x1c);
    d_d4c0_ = 0;
    d_d134_ = 0;
    disable();
    asm_05eb(!d_6e0a_);
    asm_05f7(d_6e0a_);
    d_02fb = 0;
}

/* g1_b1fd */
void g1_b1fd(void)
{
    if (d_a677_ != 0) {
        if (g1_326e(d_9d92_, d_9d94_) == 0) {
            if (d_5c6b_ == 1 && g1_3513(d_9d92_, d_9d94_) != 0) {
                d_5c6b_ = 0;
                g2_0f2a();
            }
            if (g1_3513(d_9d92_, d_9d94_) != 0 && d_c68c_ != 0) {
                g1_0042(0x1c);
                g1_b118();
            }
            asm_0424(d_a0fb_ + 0x4ce0,
                     d_9d92_ - d_009d,
                     ((d_9d94_ - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_b292 */
void pascal g1_b292(int a0, register int a1, register int a2)
{
    if (a0 < 2) {
        if (g1_326e(a1, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xa8c0,
                     a1 - d_009d,
                     (a2 - d_009f) >> 3);
        if (g1_326e(a1 + 2, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xa960,
                     a1 + 2 - d_009d,
                     (a2 - d_009f) >> 3);
    } else {
        if (g1_326e(a1, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xac80,
                     a1 - d_009d,
                     (a2 - d_009f) >> 3);
        if (g1_326e(a1 + 2, a2 - 0x80) == 0)
            asm_0424(d_637a_ + 0xad20,
                     a1 + 2 - d_009d,
                     (a2 - d_009f) >> 3);
    }

    switch (a0) {
    case 0:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xaa00,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xaaa0,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    case 1:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xab40,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xabe0,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    case 2:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xadc0,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xae60,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    case 3:
        if (g1_326e(a1, a2) == 0)
            asm_0424(d_637a_ + 0xaf00,
                     a1 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        if (g1_326e(a1 + 2, a2) == 0)
            asm_0424(d_637a_ + 0xafa0,
                     a1 + 2 - d_009d,
                     ((a2 - d_009f) >> 3) + 0x10);
        break;
    }

    if (g1_3513(a1, a2) != 0)
        d_6379_ = 1;
}

/* g1_b595 */
void g1_b595(void)
{
    if (d_554a_ != 0) {
        ++d_554a_;
        if (d_554a_ == 10)
            d_c293_ = 1;
        return;
    }

    d_0602 = !d_0602;
    if (d_c283_ == 0)
        return;

    if (d_d56c_ != 2) {
        if (d_d56c_ != 0) {
            if (d_0608 == 0) {
                ++d_0604;
                if (d_0604 == (d_060c >> 1)) {
                    if (d_0099 + d_009d - 2 < d_b630_)
                        g1_1b8a(1, d_b630_, d_b634_ - 32);
                    else
                        g1_1b8a(2, d_b630_ + 3, d_b634_ - 32);
                }
                if (d_0604 > d_060c) {
                    d_0604 = 0;
                    d_0606 = 0;
                    d_0608 = 1;
                    if (d_0099 + d_009d - 2 < d_b630_)
                        d_060a = 1;
                    else
                        d_060a = 0;
                }
            } else {
                d_b634_ += d_0702[d_0606];
                if (d_060a != 0) {
                    if (!g1_367e(d_b630_ - 1, d_b634_ - 64))
                        --d_b630_;
                } else {
                    if (!g1_367e(d_b630_ + 3, d_b634_ - 64))
                        ++d_b630_;
                }
                ++d_0606;
                if (d_0606 == 12) {
                    d_0608 = 0;
                    d_060c = (d_0437 >> 1) + 1;
                    d_0604 = 0;
                }
            }
            if (d_0099 + d_009d - 2 < d_b630_)
                g1_b292(d_0602, d_b630_, d_b634_);
            else
                g1_b292(d_0602 + 2, d_b630_, d_b634_);
            if (g1_3558(d_b630_ + 1, d_b634_ - 64)) {
                g1_2b86(3, d_b630_ + 2, d_b634_ - 92);
                --d_d142_;
            }
            if (d_0437 != 0 && d_d142_ < 10) {
                if (d_d142_ < 10)
                    g1_2e64(d_b630_ + 2, d_b634_ - 32);
                if (d_d142_ < 6)
                    g1_2e64(d_b630_ + 1, d_b634_ - 64);
                if (d_d142_ < 2)
                    g1_2e64(d_b630_ + 3, d_b634_ - 64);
            }
            if (d_d142_ == 1 && d_b9dc_ != 0)
                d_d56c_ = 0;
            else if (d_d142_ == 0)
                d_d56c_ = 2;
        } else {
            if (!g1_326e(d_b630_, d_b634_) && d_5002_ == 0) {
                d_5002_ = 1;
                g1_0042(40);
                disable();
                d_d135_ = d_d138_ = d_d13f_ = d_d4c0_ = d_c68c_ = d_d134_ = 0;
                enable();
            }
            if (d_5002_ > 30)
                d_c293_ = 1;
            if (d_5002_ != 0)
                ++d_5002_;
            if (d_5002_ != 0 && d_b634_ > 0x100 && d_009f > 0x100) {
                d_b634_ -= 0x80;
                d_009f -= 0x80;
                d_060e = 1;
            }
            if (d_0099 + d_009d - 2 < d_b630_)
                g1_b292(d_0602, d_b630_, d_b634_);
            else
                g1_b292(d_0602 + 2, d_b630_, d_b634_);
            return;
        }
    } else {
        d_b634_ += 32;
        if (d_0437 == 0)
            g1_314c(d_b630_ + 2, d_b634_);
        if (d_0437 == 32)
            g1_2b86(1, d_b630_ + 2, d_b634_);
        if (d_0437 == 64)
            g1_314c(d_b630_, d_b634_);
        if (d_0437 == 96)
            g1_2b86(3, d_b630_ + 2, d_b634_);
        if (d_0099 + d_009d - 2 < d_b630_)
            g1_b292(0, d_b630_, d_b634_);
        else
            g1_b292(2, d_b630_, d_b634_);
        if (g1_3714(d_b630_ + 1, d_b634_)) {
            g1_0042(41);
            d_554a_ = 1;
        }
        return;
    }
}

/* g1_b926 */
void pascal g1_b926(int a0, int a1, int a2)
{
    register int offset;

    offset = a0 * 0x140 + 0xa140;
    if (g1_326e(a1, a2 - 0x80) == 0) {
        asm_0424(d_637a_ + offset,
                 a1 - d_009d,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1 + 2, a2 - 0x80) == 0) {
        asm_0424(d_637a_ + offset + 0xa0,
                 a1 + 2 - d_009d,
                 (a2 - d_009f) >> 3);
    }
    if (g1_326e(a1, a2) == 0) {
        asm_0424(d_637a_ + 0xa000,
                 a1 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    }
    if (g1_326e(a1 + 2, a2) == 0) {
        asm_0424(d_637a_ + 0xa0a0,
                 a1 + 2 - d_009d,
                 ((a2 - d_009f) >> 3) + 0x10);
    } else {
        d_d146_ = 0;
    }
}

/* g1_ba39 */
void g1_ba39(void)
{
    register int si;

    if (d_c681_ == 0 || d_02fa == 0)
        return;

    ++d_071a;
    if (d_071a == 3)
        d_071a = 0;
    ++d_071c;

    if (d_071e != 0) {
        g1_b118();
        d_071e = 0;
        if (d_cc81_ == 0) {
            enable();
            while ((d_a0fa_ & 0x80) == 0) {
            }
            disable();
        }
    }

    if (d_071c == 0x7d)
        d_071c = 0;

    if (d_d146_ == 0 && d_5314_ == 0) {
        if (g1_3513(d_c276_ - 6, d_c289_) != 0) {
            g1_0042(0x1d);
            d_d146_ = 1;
            d_5314_ = 1;
            d_071e = 1;
        } else if (g1_3513(d_c276_ + 8, d_c289_) != 0) {
            g1_0042(0x1d);
            d_d146_ = 1;
            d_5314_ = 1;
            d_071e = 1;
        }
    }

    if (d_c68c_ != 0 &&
        (g1_3513(d_c276_, d_c289_) != 0 ||
         g1_3513(d_c276_ + 2, d_c289_) != 0)) {
        d_d146_ = 1;
        g1_0042(0x1d);
        d_071e = 1;
        d_5314_ = 1;
    }

    if (d_d146_ == 0) {
        g1_b926(d_071a, d_c276_, d_c289_);
    } else if (d_0099 + d_009d < d_c276_ - 1) {
        g1_b926(3, d_c276_, d_c289_);
    } else if (d_0099 + d_009d > d_c276_ + 3) {
        g1_b926(5, d_c276_, d_c289_);
    } else {
        g1_b926(4, d_c276_, d_c289_);
    }
}

/* g1_bb9f */
void pascal g1_bb9f(void)
{
    register int si;
    register int di;

    si = d_6e0a_;
    di = 0;
    do {
        ++di;
        asm_05eb(si);
        if (d_554f_ != 0)
            asm_0424(d_a0fb_ + 0x4d80, 0x1e, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x1e, 0x90);
        if (d_5550_ != 0)
            asm_0424(d_a0fb_ + 0x4e20, 0x20, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x20, 0x90);
        if (d_5551_ != 0)
            asm_0424(d_a0fb_ + 0x4ec0, 0x22, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x22, 0x90);
        if (d_5552_ != 0)
            asm_0424(d_a0fb_ + 0x4f60, 0x24, 0x90);
        else
            asm_0424(d_a0fb_ + 0x4c40, 0x24, 0x90);
        si = !si;
    } while (di == 1);
}

/* g1_bccb */
void g1_bccb(void)
{
    register int si;
    struct s_bccb far *p;

    for (si = 0; si < d_d70e_; si++) {
        p = &d_6b58_[si];
        if (p->a == 0)
            continue;
        if (g1_326e(p->b, p->c))
            continue;
        if (g1_3513(p->b, p->c)) {
            switch (p->a) {
            case 0x00a0:
                d_554f_ = 1;
                break;
            case 0x0140:
                d_5550_ = 1;
                break;
            case 0x01e0:
                d_5551_ = 1;
                break;
            case 0x0280:
                d_5552_ = 1;
                break;
            }
            g1_0042(9);
            g1_0b85(1000L);
            g1_2a40(0x03c0, p->b, p->c);
            g1_bb9f();
            p->a = 0;
        } else {
            asm_0424(d_a0fb_ + p->a + 0x4ce0,
                     p->b - d_009d,
                     0x10 + ((p->c - d_009f) >> 3));
        }
    }
}

/* g1_bdd9 */
void g1_bdd9(void)
{
    register int i;
    register int j;
    struct t_b9de far *p;

    if (d_0437 == 0)
        ++d_0720;
    if (d_0720 == 0x140)
        d_0720 = 0;

    for (j = 0; j < d_5548_; ++j) {
        p = &d_d157_[j];
        if (g1_326e(p->x, p->y))
            continue;

        if (d_5a11_ != 0 && g1_3513(p->x, p->y)) {
            d_5a11_ = 0;
            g2_0e98();
        }
        if (g1_3513(p->x, p->y) != 0 &&
            d_c68c_ != 0 && p->offset != 0) {
            if ((d_554f_ != 0 && p->offset == 0x140) ||
                (d_5550_ != 0 && p->offset == 0x1e0) ||
                (d_5551_ != 0 && p->offset == 0x280) ||
                (d_5552_ != 0 && p->offset == 0x320)) {
                for (i = 0; i < d_5319_; ++i) {
                    if (d_b9de_[i].offset != p->offset - 0xa0)
                        continue;
                    d_b9de_[i].alternate = 1;
                    *(d_7729_ + d_b9de_[i].y + (d_b9de_[i].x >> 1) - 1) =
                        *(d_7729_ + d_b9de_[i].y + (d_b9de_[i].x >> 1) - 2);
                }

                switch (p->offset - 0xa0) {
                case 0xa0:
                    d_554f_ = 0;
                    break;
                case 0x140:
                    d_5550_ = 0;
                    break;
                case 0x1e0:
                    d_5551_ = 0;
                    break;
                case 0x280:
                    d_5552_ = 0;
                    break;
                }
                g1_bb9f();
                p->offset = 0;
                g1_0042(0x1f);
                g1_0b85(1000L);
                continue;
            }
            if (d_5c6a_ != 0)
                g2_1b19();
        }
        if (p->offset == 0) {
            asm_0424(d_a0fb_ + 0x5460 + p->alternate,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else if (d_0720 % 2 != 0) {
            asm_0424(d_a0fb_ + 0x5500,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        } else {
            asm_0424(d_a0fb_ + 0x5460 + p->offset,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 0x10);
        }
    }
}

/* g1_c0c7 */
void g1_c0c7(void)
{
    register int i;
    struct t_b9de far *p;

    for (i = 0; i < d_5319_; ++i) {
        p = &d_b9de_[i];
        if (p->offset != 0 && g1_326e(p->x, p->y) == 0) {
            if (p->alternate != 0) {
                if (d_0437 == 0 || d_0437 == 0x40)
                    p->offset += 0xa0;
                if (p->offset == 0x5a0) {
                    p->offset = 0;
                    continue;
                }
                asm_0424(d_a0fb_ + p->offset + 0x4f60,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            } else {
                asm_0424(d_a0fb_ + 0x5000,
                         p->x - d_009d,
                         ((p->y - d_009f) >> 3) + 0x10);
            }
        }
    }
}

/* g1_c1b2 */
void g1_c1b2(void)
{
    register int i;
    struct g1_c1b2_record far *p;

    i = 0;
    while (i < d_531e_) {
        p = &d_cc84_[i];
        if (g1_326e(p->x, p->y) == 0) {
            if (g1_3513(p->x, p->y) != 0)
                d_6379_ = 1;
            asm_0424(d_a0fb_ + p->kind,
                     p->x - d_009d,
                     ((p->y - d_009f) >> 3) + 16);
        }
        ++i;
    }
}

/* g1_c243 */
void pascal g1_c243(void (far *key)(void))
{
    register int i;

    for (i = 0; i < d_554d_; ++i) {
        if (d_514b_[i] == key)
            return;
    }
    d_514b_[i] = key;
    ++d_554d_;
}

/* g1_c287 */
void pascal g1_c287(unsigned int a0) {
    register unsigned int col;
    register unsigned int row;
    int k;
    unsigned int far *cell;
    for (row=0; row<a0; ++row) {
        for (col=0; col<128; ++col) {
            cell=d_7729_+row*128+col;
            if (*cell>=0x3000) {
                switch (*cell) {
                case 0x3000:
                    d_669f_[d_043c].state=1;
                    d_669f_[d_043c].x=col*2+2;
                    d_669f_[d_043c].y=row*128;
                    g1_c243(g1_376f);
                    *cell=cell[-1];
                    ++d_043c;
                    break;
                case 0x3001:
                    d_a8da_[d_0524].used=1;
                    d_a8da_[d_0524].x=col*2+2;
                    d_d646_[d_0524]=cell[-128];
                    d_a8da_[d_0524].y=row*128;
                    *cell=0x1ae0;
                    ++d_0524;
                    break;
                case 0x3002:
                    d_c299_[d_0526].reserved=0;
                    d_c299_[d_0526].y=col+2;
                    d_c299_[d_0526].x=row*128;
                    k=0;
                    while (cell[k]!=0x3003) ++k;
                    d_c299_[d_0526].height=k*2;
                    d_c299_[d_0526].state=0;
                    g1_c243(g1_3a98);
                    *cell=0x1820;
                    ++d_0526;
                    break;
                case 0x3003:
                    break;
                case 0x3004:
                    d_c299_[d_0526].reserved=0;
                    d_c299_[d_0526].y=col+2;
                    d_c299_[d_0526].x=row*128;
                    k=0;
                    while (cell[k]!=0x3005) ++k;
                    d_c299_[d_0526].height=k*2;
                    d_c299_[d_0526].state=1;
                    g1_c243(g1_3a98);
                    ++d_0526;
                    break;
                case 0x3005:
                    break;
                case 0x3006:
                    d_0528=col*2+2;
                    d_052a=row*128;
                    d_052c=0;
                    g1_c243(g1_3cbc);
                    *cell=cell[-1];
                    break;
                case 0x3007:
                    d_6bb2_[d_053e].state=1;
                    d_6bb2_[d_053e].x=col*2+2;
                    d_6bb2_[d_053e].y=row*128;
                    g1_c243(g1_3e06);
                    d_5006_=1;
                    *cell=cell[-128];
                    ++d_053e;
                    break;
                case 0x3008:
                    d_a67b_=col*2+2;
                    d_a67e_=row*128;
                    d_052e=0;
                    g1_c243(g1_42b8);
                    *cell=cell[-1];
                    break;
                case 0x3009:
                    d_772e_[d_0540].state=1;
                    d_772e_[d_0540].x=col*2+2;
                    d_772e_[d_0540].y=row*128;
                    g1_c243(g1_43fa);
                    *cell=cell[1];
                    ++d_0540;
                    break;
                case 0x300a:
                    d_9b3a_[d_0542].state=1;
                    d_9b3a_[d_0542].position2=col*2+2;
                    d_9b3a_[d_0542].position4=row*128;
                    g1_c243(g1_4638);
                    *cell=cell[-1];
                    ++d_0542;
                    break;
                case 0x300b:
                    d_637f_[d_0544].type=1;
                    d_637f_[d_0544].x=col*2+2;
                    d_637f_[d_0544].y=row*128;
                    d_637f_[d_0544].step=0;
                    g1_c243(g1_4874);
                    *cell=cell[-1];
                    ++d_0544;
                    break;
                case 0x300c:
                    d_b6bc_[d_05aa].state=1;
                    d_b6bc_[d_05aa].x=col*2+2;
                    d_b6bc_[d_05aa].y=row*128;
                    d_b6bc_[d_05aa].marker=0;
                    d_5081_[d_05aa]=0;
                    g1_c243(g1_4f91);
                    *cell=cell[-1];
                    ++d_05aa;
                    break;
                case 0x300d:
                    d_a0ff_[d_05ac].state=1;
                    d_a0ff_[d_05ac].x=col*2+2;
                    d_a0ff_[d_05ac].y=row*128;
                    d_d57e_[d_05ac]=0;
                    g1_c243(g1_54e1);
                    *cell=cell[-1];
                    ++d_05ac;
                    break;
                case 0x300e:
                    d_abec_[d_05b2].state=1;
                    d_abec_[d_05b2].x=col*2+2;
                    d_abec_[d_05b2].y=row*128;
                    d_4eda_[d_05b2]=0;
                    g1_c243(g1_5b0b);
                    *cell=cell[-1];
                    ++d_05b2;
                    break;
                case 0x300f:
                    d_ab32_[d_05b4].active=1;
                    d_ab32_[d_05b4].x=col*2+2;
                    d_ab32_[d_05b4].y=row*128;
                    d_ab32_[d_05b4].state=0;
                    g1_c243(g1_5d6f);
                    *cell=cell[-1];
                    ++d_05b4;
                    break;
                case 0x3010:
                    d_b0b4_[d_05b6].state=1;
                    d_b0b4_[d_05b6].x=col*2+2;
                    d_b0b4_[d_05b6].y=row*128;
                    d_b0b4_[d_05b6].field3=0;
                    g1_c243(g1_5f0c);
                    *cell=cell[-1];
                    ++d_05b6;
                    break;
                case 0x3011:
                    d_4ed2_=0;
                    d_d570_=1;
                    d_d4bd_=col*2+2;
                    d_d4c1_=row*128+2;
                    *cell=cell[-1];
                    break;
                case 0x3012:
                    d_555d_[d_05b8].state=1;
                    d_555d_[d_05b8].x=col*2+2;
                    d_555d_[d_05b8].y=row*128;
                    d_555d_[d_05b8].kind=0;
                    d_555d_[d_05b8].flag8=1;
                    d_555d_[d_05b8].flag10=1;
                    g1_c243(g1_6445);
                    *cell=cell[-1];
                    ++d_05b8;
                    break;
                case 0x3013:
                    d_5310_=0;
                    d_b636_=1;
                    d_abd2_=0;
                    for (k=9; k>0; --k) {
                        d_abd4_[k]=col*2+k*2;
                        d_b09c_[k]=row*128+2;
                        d_d249_[k]=1;
                    }
                    g1_c243(g1_6947);
                    *cell=cell[-1];
                    break;
                case 0x3014:
                    d_70db_[d_05ba].x=col*2+2;
                    d_70db_[d_05ba].y=row*128;
                    ++d_05ba;
                    *cell=cell[-1];
                    break;
                case 0x3015:
                case 0x3052:
                    if (*cell==0x3052) d_5a12_[d_05bc].state=2;
                    else d_5a12_[d_05bc].state=1;
                    d_5a12_[d_05bc].x=col*2+2;
                    d_5a12_[d_05bc].y=row*128;
                    ++d_05bc;
                    *cell=cell[-1];
                    g1_c243(g1_6b82);
                    break;
                case 0x3016:
                case 0x3017:
                    if (*cell==0x3016) {
                        d_d261_[d_05be].state=1;
                        *cell=cell[1];
                    } else {
                        d_d261_[d_05be].state=3;
                        *cell=cell[-1];
                    }
                    d_d261_[d_05be].x=col*2+2;
                    d_d261_[d_05be].y=row*128;
                    ++d_05be;
                    g1_c243(g1_6e71);
                    break;
                case 0x3018:
                case 0x3051:
                    if (*cell==0x3051) d_c01e_[d_05c0].state=2;
                    else d_c01e_[d_05c0].state=1;
                    d_c01e_[d_05c0].x=col*2+2;
                    d_c01e_[d_05c0].y=row*128;
                    ++d_05c0;
                    *cell=cell[-1];
                    g1_c243(g1_7163);
                    break;
                case 0x3019:
                    d_d4b9_=col+2;
                    d_d4bb_=row;
                    d_c281_=1;
                    d_d155_=0;
                    d_b62e_=col+2;
                    d_b632_=row*128;
                    k=0;
                    while (((struct cell_pair far *)(cell+k))->second<0x1800) { cell[k]=0x21a0;
                        ((struct cell_pair far *)(cell+k))->second=0x21c0;
                        k+=2;
                    }
                    d_d136_=k*2;
                    g1_c243(g1_73d3);
                    *cell=0x21a0;
                    break;
                case 0x301a:
                    d_b3d6_[d_05c2].x=col*2+2;
                    d_b3d6_[d_05c2].y=row*128;
                    d_b3d6_[d_05c2].used=1;
                    g1_c243(g1_74c2);
                    ++d_05c2;
                    *cell=cell[-128];
                    break;
                case 0x301b:
                case 0x301c:
                    if (*cell==0x301b) { d_798c_[d_05c4].state=1;
                        *cell=cell[-1];
                    }
                    else { d_798c_[d_05c4].state=2;
                        *cell=cell[1];
                    }
                    d_798c_[d_05c4].value1=col*2+2;
                    d_798c_[d_05c4].value2=row*128;
                    d_798c_[d_05c4].count=0;
                    g1_c243(g1_7647);
                    ++d_05c4;
                    break;
                case 0x301d:
                case 0x3050:
                    d_9d99_[d_05c6].active=1;
                    d_9d99_[d_05c6].x=col*2+2;
                    d_9d99_[d_05c6].y=row*128;
                    if (*cell==0x3050) d_9d99_[d_05c6].state=1;
                    else d_9d99_[d_05c6].state=0;
                    ++d_05c6;
                    *cell=cell[-1];
                    g1_c243(g1_784b);
                    break;
                case 0x301e:
                case 0x3054:
                    d_a357_[d_05c8].state=1;
                    d_a357_[d_05c8].x=col*2+2;
                    d_a357_[d_05c8].y=row*128;
                    if (*cell==0x3054) d_a357_[d_05c8].flag=1;
                    else d_a357_[d_05c8].flag=0;
                    ++d_05c8;
                    *cell=cell[-1];
                    g1_c243(g1_79d9);
                    break;
                case 0x301f:
                case 0x3053:
                    d_9818_[d_05ca].state=1;
                    d_9818_[d_05ca].x=col*2+2;
                    d_9818_[d_05ca].y=row*128;
                    if (*cell==0x3053) d_9818_[d_05ca].flag=1;
                    else d_9818_[d_05ca].flag=0;
                    ++d_05ca;
                    *cell=cell[-1];
                    g1_c243(g1_7b68);
                    break;
                case 0x3020:
                    d_0530=col*2+2;
                    d_0532=row*128;
                    d_0534=0;
                    g1_c243(g1_573d);
                    *cell=cell[-1];
                    break;
                case 0x3021:
                    d_726b_[d_05cc].x=col*2+2;
                    d_726b_[d_05cc].y=row*128;
                    (&d_726b_[d_05cc].x)[2]=1;
                    g1_c243(g1_7cfa);
                    ++d_05cc;
                    *cell=cell[-1];
                    break;
                case 0x3022:
                    d_5ec9_[d_05ce].f0=1;
                    d_5ec9_[d_05ce].f2=col*2+2;
                    d_5ec9_[d_05ce].f4=row*128;
                    d_5ec9_[d_05ce].f6=0;
                    d_5ec9_[d_05ce].f8=4;
                    d_5ec9_[d_05ce].fa=0;
                    g1_c243(g1_8069);
                    ++d_05ce;
                    *cell=cell[-1];
                    break;
                case 0x3023:
                    d_7cac_[d_05d0].state=1;
                    d_7cac_[d_05d0].x=col*2+2;
                    d_7cac_[d_05d0].y=row*128;
                    g1_c243(g1_8506);
                    ++d_05d0;
                    *cell=cell[-1];
                    break;
                case 0x3024:
                    d_d57c_=1;
                    d_68fc_[d_05d2].state=1;
                    d_68fc_[d_05d2].x=col*2+2;
                    d_68fc_[d_05d2].y=row*128;
                    ++d_05d2;
                    *cell=cell[128];
                    break;
                case 0x3025:
                    d_7f06_[d_05d4].offset=0x7ee0;
                    d_7f06_[d_05d4].x=col*2+2;
                    d_7f06_[d_05d4].y=row*128;
                    ++d_05d4;
                    *cell=cell[-128];
                    break;
                case 0x3026:
                case 0x3027:
                    d_7f06_[d_05d4].offset=(*cell+0xcfda)*0xa0+0x7f80;
                    d_7f06_[d_05d4].x=col*2+2;
                    d_7f06_[d_05d4].y=row*128;
                    ++d_05d4;
                    if (*cell==0x3026) *cell=cell[-1];
                    else *cell=cell[1];
                    break;
                case 0x3028:
                    d_7f06_[d_05d4].offset=0x80c0;
                    d_7f06_[d_05d4].x=col*2+2;
                    d_7f06_[d_05d4].y=row*128;
                    ++d_05d4;
                    *cell=0;
                    break;
                case 0x3029:
                    d_7063_[d_05d6].state=1;
                    d_7063_[d_05d6].x=col*2+2;
                    d_7063_[d_05d6].y=row*128;
                    ++d_05d6;
                    g1_c243(g1_899e);
                    *cell=cell[-1];
                    break;
                case 0x302a:
                    d_c691_[d_05d8].state=1;
                    d_c691_[d_05d8].x=col*2+2;
                    d_c691_[d_05d8].y=row*128;
                    ++d_05d8;
                    g1_c243(g1_8b5b);
                    *cell=cell[-1];
                    break;
                case 0x302b:
                    d_c8e9_=0;
                    d_c68d_=col*2+2;
                    d_c68f_=row*128;
                    d_d572_=1;
                    d_d56e_=10;
                    g1_c243(g1_8ec1);
                    *cell=cell[-1];
                    break;
                case 0x302c:
                    d_9688_[d_05da].x=col*2+2;
                    d_9688_[d_05da].y=row*128;
                    g1_c243(g1_9698);
                    ++d_05da;
                    *cell=cell[-128];
                    break;
                case 0x302d:
                case 0x3055:
                    if (*cell==0x3055) d_c915_[d_05dc].state=2;
                    else d_c915_[d_05dc].state=1;
                    d_c915_[d_05dc].x=col*2+2;
                    d_c915_[d_05dc].y=row*128;
                    ++d_05dc;
                    g1_c243(g1_9757);
                    *cell=cell[-1];
                    break;
                case 0x302e:
                case 0x3056:
                    if (*cell==0x3056) d_6e0b_[d_05de].state=2;
                    else d_6e0b_[d_05de].state=1;
                    d_6e0b_[d_05de].x=col*2+2;
                    d_6e0b_[d_05de].y=row*128;
                    ++d_05de;
                    g1_c243(g1_9986);
                    *cell=cell[-1];
                    break;
                case 0x302f:
                    d_c684_=1;
                    d_c279_=col*2+2;
                    d_c28b_=row*128;
                    d_d139_=0;
                    d_c686_=0;
                    g1_c243(g1_a032);
                    *cell=cell[-1];
                    break;
                case 0x3030:
                    d_c688_=1;
                    d_c27b_=col*2+2;
                    d_c28d_=row*128;
                    d_d13b_=0;
                    d_c68a_=0;
                    g1_c243(g1_a125);
                    *cell=cell[-1];
                    break;
                case 0x3031:
                    d_ae44_[d_05e0].state=0xfffa;
                    d_ae44_[d_05e0].x=col*2+2;
                    d_ae44_[d_05e0].y=row*128;
                    g1_c243(g1_a218);
                    *cell=cell[-1];
                    ++d_05e0;
                    break;
                case 0x3032:
                    d_009d=col*2-14;
                    d_009f=row*128-384;
                    d_009b=64;
                    *cell=cell[-1];
                    break;
                case 0x3033:
                    d_b3d4_=0;
                    d_053c=1;
                    d_0536=col*2+2;
                    d_0538=row*128;
                    d_053a=0;
                    g1_c243(g1_5887);
                    *cell=cell[-1];
                    break;
                case 0x3034:
                    d_7f04_=1;
                    d_9d96_=col*2+2;
                    d_a0b9_=row*128;
                    *cell=cell[-1];
                    break;
                case 0x3035:
                    d_5307_=1;
                    d_52db_=0;
                    d_5149_=0;
                    d_d13d_=col*2+2;
                    d_d140_=row*128;
                    *cell=cell[-1];
                    break;
                case 0x3036:
                    d_5316_=1;
                    d_5000_=0;
                    d_d574_=col*2+2;
                    d_d577_=row*128;
                    *cell=0x2fe0;
                    g1_c243(g1_a6f4);
                    break;
                case 0x3037:
                case 0x3038:
                case 0x3039:
                case 0x303a:
                    d_530c_=0;
                    switch (*cell) {
                    case 0x3037:
                        d_a0bf_[d_5309_].state=0x44;
                        break;
                    case 0x3038:
                        d_a0bf_[d_5309_].state=0x55;
                        break;
                    case 0x3039:
                        d_a0bf_[d_5309_].state=0x4b;
                        break;
                    case 0x303a:
                        d_a0bf_[d_5309_].state=0x45;
                        break;
                    }
                    d_a0bf_[d_5309_].x=col*2+2;
                    d_a0bf_[d_5309_].y=row*128;
                    d_a0bf_[d_5309_].flag=0;
                    *cell=cell[-1];
                    g1_c243(g1_a75c);
                    ++d_5309_;
                    break;
                case 0x303b:
                    d_73fb_[d_0600].state=1;
                    d_73fb_[d_0600].x=col*2+2;
                    d_73fb_[d_0600].y=row*128;
                    d_73fb_[d_0600].kind=0;
                    ++d_0600;
                    g1_c243(g1_aac2);
                    *cell=cell[-1];
                    break;
                case 0x303c:
                    d_a680_[d_05fe].state=1;
                    d_a680_[d_05fe].x=col*2+2;
                    d_a680_[d_05fe].y=row*128;
                    ++d_05fe;
                    g1_c243(g1_af94);
                    *cell=cell[-1];
                    break;
                case 0x303d:
                case 0x303e:
                case 0x303f:
                    d_7f06_[d_05d4].offset=(*cell+0xcfc3)*0xa0+0x9d80;
                    d_7f06_[d_05d4].x=col*2+2;
                    d_7f06_[d_05d4].y=row*128;
                    ++d_05d4;
                    *cell=0;
                    break;
                case 0x3040:
                    d_a677_=1;
                    d_9d92_=col*2+2;
                    d_9d94_=row*128;
                    *cell=cell[-1];
                    break;
                case 0x3041:
                    d_c681_=1;
                    d_d146_=0;
                    d_c276_=col*2+2;
                    d_c289_=row*128;
                    *cell=cell[-1];
                    break;
                case 0x3042:
                case 0x3043:
                    d_c283_=1;
                    d_b630_=col*2+2;
                    d_b634_=row*128;
                    d_d56c_=1;
                    if (*cell==0x3043) d_b9dc_=1;
                    else d_b9dc_=0;
                    d_d142_=10;
                    d_5002_=0;
                    *cell=cell[-1];
                    g1_c243(g1_b595);
                    break;
                case 0x3044:
                case 0x3045:
                case 0x3046:
                case 0x3047:
                    d_6b58_[d_d70e_].a=(*cell+0xcfbd)*0xa0;
                    d_6b58_[d_d70e_].b=col*2+2;
                    d_6b58_[d_d70e_].c=row*128;
                    ++d_d70e_;
                    *cell=cell[-1];
                    g1_c243(g1_bccb);
                    break;
                case 0x3048:
                case 0x3049:
                case 0x304a:
                case 0x304b:
                    d_d157_[d_5548_].offset=(*cell+0xcfba)*0xa0;
                    d_d157_[d_5548_].x=col*2+2;
                    d_d157_[d_5548_].y=row*128;
                    d_d157_[d_5548_].alternate=(*cell+0xcfba)*0xa0;
                    ++d_5548_;
                    *cell=cell[-1];
                    break;
                case 0x304c:
                case 0x304d:
                case 0x304e:
                case 0x304f:
                    d_b9de_[d_5319_].offset=(*cell+0xcfb5)*0xa0;
                    d_b9de_[d_5319_].x=col*2+2;
                    d_b9de_[d_5319_].y=row*128;
                    d_b9de_[d_5319_].alternate=0;
                    ++d_5319_;
                    *cell=0x1820;
                    g1_c243(g1_c0c7);
                    break;
                case 0x3057:
                    d_5c6c_[d_5004_].used=1;
                    d_5c6c_[d_5004_].x=col*2+2;
                    d_5c6c_[d_5004_].y=row*128;
                    ++d_5004_;
                    *cell=cell[-1];
                    g1_c243(g1_a30a);
                    break;
                case 0x3058:
                case 0x3059:
                    d_cc84_[d_531e_].x=col*2+2;
                    d_cc84_[d_531e_].y=row*128;
                    g1_c243(g1_c1b2);
                    if (*cell==0x3058) { d_cc84_[d_531e_].kind=0x5c80;
                        *cell=cell[-128];
                    }
                    else { d_cc84_[d_531e_].kind=0x5d20;
                        *cell=cell[128];
                    } ++d_531e_;
                    break;
                case 0x305a:
                    break;
                case 0x305b:
                    break;
                case 0x305c:
                    break;
                case 0x305d:
                    break;
                case 0x305e:
                    break;
                case 0x305f:
                    break;
                default:
                    break;
                }
            }
        }
    }
}

/* g1_de26 */
void g1_de26(char far *filename)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    fread(d_7729_, 0x2d00, 2, stream);
    fclose(stream);
}

/* g1_de71 */
void g1_de71(char far *filename, char far *buffer)
{
    FILE *fp;

    fp = fopen(filename, "rb");
    if (fp == 0) {
        d_c278_ = 0;
        d_530e_ = 1;
    } else {
        d_530e_ = 0;
        d_040e = getw(fp);
        fread(buffer, 0x4268, 1, fp);
        d_c278_ = 1;
    }
    fclose(fp);
}

/* g1_dee9 */
void g1_dee9(char far *filename, char far *buffer)
{
    FILE *stream;

    stream = fopen(filename, "rb");
    if (stream == NULL) {
        d_c278_ = 0;
    } else {
        d_0410 = getw(stream);
        fread(buffer, 0x4268, 1, stream);
        d_c278_ = 1;
    }
    fclose(stream);
}

/* g1_df57 */
void g1_df57(char far *filename, void far *buffer)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    putw(d_040e, stream);
    fwrite(buffer, 0x4268, 1, stream);
    fclose(stream);
}

/* g1_dfb2 */
void g1_dfb2(char far *filename, void far *buffer)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    putw(d_0410, stream);
    fwrite(buffer, 0x4268, 1, stream);
    fclose(stream);
}

/* g1_e00d */
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

/* g1_e3e0 */
void pascal g1_e3e0(char far *a0)
{
    g1_1b51();
    d_0436 = 0;
    d_0437 = 0;
    d_060e = 0;
    d_0439 = 0;
    d_043a = 4;
    d_043b = 0;
    d_d576_ = 0;
    d_043c = 0;
    d_043e = 12;
    d_051c = 3;
    d_051e = 7;
    d_0520 = 0x12;
    d_0522 = 8;
    d_0524 = 0;
    d_0526 = 0;
    d_053e = 0;
    d_0540 = 0;
    d_0542 = 0;
    d_0544 = 0;
    d_05a6 = 0;
    d_05a8 = 0;
    d_05aa = 0;
    d_05ac = 0;
    d_05b2 = 0;
    d_554d_ = 0;
    d_05b4 = 0;
    d_05b6 = 0;
    d_4ed2_ = 0;
    d_d570_ = 0;
    d_05b8 = 0;
    d_b636_ = 0;
    d_05ba = 0;
    d_05bc = 0;
    d_05be = 0;
    d_05c0 = 0;
    d_c281_ = 0;
    d_05c2 = 0;
    d_05c4 = 0;
    d_05c6 = 0;
    d_05c8 = 0;
    d_05ca = 0;
    d_05cc = 0;
    d_05ce = 0;
    d_05d0 = 0;
    d_05d2 = 0;
    d_05d4 = 0;
    d_05d6 = 0;
    d_05d8 = 0;
    d_05da = 0;
    d_c8e9_ = 1;
    d_d572_ = 0;
    d_05dc = 0;
    d_05de = 0;
    d_05e0 = d_c688_ = d_d13b_ = d_c684_ = d_d139_ = 0;
    d_7f04_ = -1;
    d_c283_ = d_c681_ = d_a677_ = d_05fe = d_0600 = d_d57a_ = d_5309_ = d_5316_ = d_5307_ = 0;
    d_6379_ = 0;
    d_d4bf_ = 0x15;
    d_5314_ = d_5319_ = d_d70e_ = d_5548_ = d_053c = d_b3d4_ = 0;
    d_d56e_ = 10;
    d_060a = d_0608 = d_0606 = d_0604 = d_0602 = d_5004_ = 0;
    d_060c = 10;
    d_554a_ = d_531e_ = d_b9dc_ = d_5002_ = 0;

    g1_de26(a0);
    outport(0x3ce, 5);

    if (d_02fa % 2 == 0) {
        g1_10fb(d_0b47[(int)d_02fa],
                0x4000, 0x5140);
        g1_10fb(d_0b47[(int)d_02fa + 1],
                0x8100, 0x5140);
    }

    if (d_02fa % 2 == 0) {
        d_d247_ = 1;
        d_5312_ = 0;
        g1_2a1d();
    }

    g1_c287(0x5a);
    d_0644 = 1;
    d_a679_ = 0;
    d_d144_ = 0;
    d_554f_ = 0;
    d_5550_ = 0;
    d_5551_ = 0;
    d_5552_ = 0;
    g1_bb9f();
}

/* g1_e655 */
void g1_e655(void)
{
    long saved;

    d_05ae = 0;
    d_05b0 = 0;
    d_043a = 4;
    d_043b = 0;
    d_d576_ = 0;
    d_0528 = 0;
    d_052a = 0;
    d_798a_ = 0;
    d_052c = 0;
    d_052e = 0;
    d_a0f8_ = 0;
    d_0530 = 0;
    d_0532 = 0;
    d_cc82_ = 0;
    d_0534 = 0;
    d_0536 = 0;
    d_0538 = 0;
    d_b3d4_ = 0;
    d_053a = 0;
    d_9682_ = 0;
    d_9b38_ = 0;
    d_5310_ = 0;
    d_530c_ = 0;
    d_c295_ = 1;
    d_5006_ = 0;
    d_0610 = 1;
    d_0611 = 0;
    d_0612 = 0;
    d_0099 = 0x10;
    d_009b = 0x30;
    d_009d = 0;
    d_009f = 0;
    d_68f8_ = 0L;
    d_d57c_ = 0;
    d_4ed6_ = 0;
    d_531c_ = 0;
    d_02fa = 0;
    d_4ed4_ = 9;

    if (d_03a3) {
        g2_219d(d_554c_);
        if (d_5318_) {
            return;
        }
        g2_0009(0x14);
        g2_3114();
        d_03a3 = 0;
        if (d_798a_) {
            g2_1ffa(d_a0fb_ + 0x640);
        }
        if (d_a0f8_) {
            g2_1ffa(d_a0fb_ + 0xb40);
        }
        if (d_cc82_) {
            g2_1ffa(d_a0fb_ + 0x2760);
        }
    } else {
        g2_3114();
    }

    g2_2ab9();
    g2_1454();
    g2_29a2();
    g2_0036(0x14);

    if (d_0098 == 2 || d_c683_ == 2) {
        d_02fa = 0x14;
    }
    g1_e3e0(d_03a4[d_02fa]);
    saved = d_68f8_;
    d_68f8_ = 0L;
    g1_0b85(0L);
    d_68f8_ = saved;
    g1_0b85(0L);
    g1_0adc();
    g1_0a0e();
}

/* g1_e83e */
void g1_e83e(void)
{
    unsigned long available;

    available = coreleft();
    if (available < 0x57e40UL) {
        printf("Not enough memory to run Duke Nukum!\n");
        printf("(There needs to be at least 520k available.)\n");
        printf("Try unloading TSRs or exiting from a shell\n");
        printf("and then try running the game again.  Thanks!\n");
        _exit(0);
    }
}

/* g1_e89d */
void pascal g1_e89d(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "rb");
    if (stream == NULL) {
        d_4ed0_ = 0;
    } else {
        d_4ed0_ = getw(stream);
    }
    fclose(stream);
}

/* g1_e8ed */
void pascal g1_e8ed(char far *filename)
{
    FILE *stream;
    stream = fopen(filename, "wb");
    putw(d_4ed0_, stream);
    fclose(stream);
}

/* g1_e92e */
void pascal g1_e92e(register int n)
{
    d_02fb = 0;
    while (d_02fb < n)
        ;
}

/* g1_e947 */
void g1_e947(void)
{
    register int i;
    register int phase;
    long counter;
    int button1;
    int button2;

    counter = 0L;
    phase = 0;
    g1_0b85(100000L);
    if (d_b9dc_ != 0) {
        g2_01a9(10);
        g2_36c1();
        g2_0036(10);
        for (i = 0; i < 0x34; ++i) {
            phase = !phase;
            asm_0424(d_a0fb_ + (phase % 2) * 0xa0 + 0x5820,
                     0x1a, 0x7d - i);
            g1_e92e(10);
        }
        for (i = 0; i < 0x32; ++i) {
            phase = !phase;
            asm_0424(d_a0fb_ + (phase % 2) * 0xa0 + 0x5820,
                     0x1a, 0x4a);
            g1_e92e(10);
        }
        for (i = 0; i < 5; ++i) {
            asm_0424(d_a0fb_ + i * 0xa0 + 0x5960,
                     0x1a, 0x4b - i);
            g1_e92e(14);
        }

        counter = 0L;
        d_a0fa_ = 0;
        if (d_d56b_ != 0) {
            button1 = inportb(0x201) & 0x10;
            button2 = inportb(0x201) & 0x20;
        } else {
                button1 = button2 = 1;
            }
            while (d_a0fa_ == 0 && button1 != 0 && button2 != 0) {
                if (d_d56b_ != 0) {
                    button1 = inportb(0x201) & 0x10;
                    button2 = inportb(0x201) & 0x20;
                } else {
                    button1 = button2 = 1;
                }
                if (d_02fb % 2 != 0) {
                    ++counter;
                    if (counter == 0x16e360L) {
                        g2_01a9(10);
                        g2_340f();
                        g2_0036(10);
                        goto stage_after_first;
                    }
                    if (counter == 0x493e0L)
                        g2_2473();
                }
            }

            g2_01a9(10);
            g2_340f();
            g2_0036(10);
            if (d_cc81_ == 0) {
                do {
                } while ((d_a0fa_ & 0x80) == 0);
            }
    stage_after_first:
            g2_4334();
            d_02fb = 0;

            g2_01a9(10);
            g2_3568();
            g2_0036(10);
            if (d_cc81_ == 0) {
                do {
                } while ((d_a0fa_ & 0x80) == 0);
            }
            g2_4394();
            d_02fb = 0;

            g2_01a9(10);
            g2_340f();
            g2_0036(10);
            if (d_cc81_ == 0) {
                do {
                } while ((d_a0fa_ & 0x80) == 0);
            }
            g2_43f5();
            d_02fb = 0;

            g2_01a9(10);
            g2_3568();
            g2_0036(10);
            if (d_cc81_ == 0) {
                do {
                } while ((d_a0fa_ & 0x80) == 0);
            }
            g2_4444();
            g2_01a9(10);
        } else {
        d_02fb = 0;
        while (d_02fb < 500) {
        }
        g2_01a9(20);
        g2_3114();
        g2_3568();
        g2_0036(20);
        if (d_cc81_ == 0) {
            do {
            } while ((d_a0fa_ & 0x80) == 0);
        }
        g2_44a5();
        g2_01a9(20);
    }
    d_02fb = 0;
    g2_452b(7);
}

/* g1_ec3d */
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

/* g1_ecf4 */
void g1_ecf4(void)

{
    int wait;
    register int i;
    register int j;

    wait = 0;
    d_0b9f = 0;
    d_5305_ = 0;
    d_039f = 0;
    d_02fb = 0;
    d_c293_ = 0;
    disable();
    d_d135_ = d_d138_ = d_d13f_ = d_d4c0_ = d_c68c_ = d_d134_ = 0;
    enable();

    if (d_c683_ != 0)
        d_a0fa_ = 0;
    for (;;) {
        while (d_4ed0_ + 9 > d_02fb)
            ;
        d_02fb = 0;
        g1_290f();
        if (d_cc81_ != 0) {
            if (d_d139_ == 0 && d_d13b_ == 0)
                g1_0c52(1);
            g1_10a5();
        }
        disable();

        if (d_c683_ == 1) {
            d_c68c_ = ((char far *)d_9684_)[d_040c];
            d_d134_ = ((char far *)d_9684_)[d_040c + 1];
            d_d13f_ = ((char far *)d_9684_)[d_040c + 2];
            d_d4c0_ = ((char far *)d_9684_)[d_040c + 3];
            d_d135_ = ((char far *)d_9684_)[d_040c + 4];
            d_d138_ = ((char far *)d_9684_)[d_040c + 5];
            d_040c += 6;
            if (d_040c >= 0x425a || d_040c >= d_040e) {
                enable();
                goto reset_c683_exit;
            }
        }
        if (d_0098 == 1 && d_040c != 0x425a) {
            ((char far *)d_9684_)[d_040c] = d_c68c_;
            ((char far *)d_9684_)[d_040c + 1] = d_d134_;
            ((char far *)d_9684_)[d_040c + 2] = d_d13f_;
            ((char far *)d_9684_)[d_040c + 3] = d_d4c0_;
            ((char far *)d_9684_)[d_040c + 4] = d_d135_;
            ((char far *)d_9684_)[d_040c + 5] = d_d138_;
            d_040c += 6;
            if (d_040c >= 0x4259) {
                d_0098 = 0;
                d_040e = d_040c;
            }
        }
        if (d_c683_ == 2) {
            d_c68c_ = ((char far *)d_5a0d_)[d_040c];
            d_d134_ = ((char far *)d_5a0d_)[d_040c + 1];
            d_d13f_ = ((char far *)d_5a0d_)[d_040c + 2];
            d_d4c0_ = ((char far *)d_5a0d_)[d_040c + 3];
            d_d135_ = ((char far *)d_5a0d_)[d_040c + 4];
            d_d138_ = ((char far *)d_5a0d_)[d_040c + 5];
            d_040c += 6;
            if (d_040c >= 0x425a || d_040c >= d_0410) {
                enable();
                goto reset_c683_exit;
            }
        }
        if (d_0098 == 2 && d_040c != 0x425a) {
            ((char far *)d_5a0d_)[d_040c] = d_c68c_;
            ((char far *)d_5a0d_)[d_040c + 1] = d_d134_;
            ((char far *)d_5a0d_)[d_040c + 2] = d_d13f_;
            ((char far *)d_5a0d_)[d_040c + 3] = d_d4c0_;
            ((char far *)d_5a0d_)[d_040c + 4] = d_d135_;
            ((char far *)d_5a0d_)[d_040c + 5] = d_d138_;
            d_040c += 6;
            d_0410 = d_040c;
            if (d_040c >= 0x4259)
                d_0098 = 0;
        }

        g1_1e77();
        enable();
        g1_2a93();
        g1_32a5();
        g1_2f4c();
        g1_2eb1();
        g1_1933();
        g1_1bf6();
        g1_30c9();
        j = 0;
        while (j < d_554d_) {
            d_514b_[j]();
            ++j;
        }

        if (d_c683_ == 2) {
            if (d_0437 == 0 || d_0437 == 0x20)
                g2_37b6("Press any key.", 8, 10);
            g2_3f68();
        }
        if (d_7728_ != 0 && d_772d_ != 0 && d_771b_ != 0 && d_0095 != 0) {
            d_b3d4_ = d_798a_ = d_a0f8_ = d_cc82_ = 1;
            d_053c = 0;
            g2_1ffa(d_a0fb_ + 0x640);
            g2_1ffa(d_a0fb_ + 0xb40);
            g2_1ffa(d_a0fb_ + 0x2760);
            g2_1f9c();
            d_4ed4_ = 9;
            g1_0a0e();
            d_554f_ = d_5550_ = d_5551_ = d_5552_ = 1;
            g1_bb9f();
            d_c295_ = 4;
            g1_0adc();
            d_02fb = 0;
            d_9682_ = 0;
        }
        if (d_a67d_ == 1 && d_a8d9_ == 1) {
            g1_0042(0x19);
            g2_3d8c(2, 1, 2);
            g2_3cdc();
            while (d_a67d_ != 0 || d_a8d9_ != 0)
                ;
            g2_2870(0x1a, 6);
            d_554f_ = d_5550_ = d_5551_ = d_5552_ = 1;
            g1_bb9f();
            d_c295_ = 4;
            g1_0adc();
            d_02fb = 0;
            d_d4c0_ = 0;
            d_d134_ = 0;
        }
        g1_2bd9();
        g1_6afd();
        g2_29a2();
        if (d_0098 != 0)
            asm_02ad(0x3200, 2);
        if (d_c683_ != 0 && d_0437 == 0)
            asm_02ad(0x3180, 2);
        if (d_a67d_ == 1 && d_7728_ != 0) {
            while (d_a67d_ == 1 || d_7728_ != 0)
                ;
            while (d_a67d_ == 0 && d_7728_ == 0)
                ;
        }
        if (d_a0fa_ == 0x11 && d_7728_ != 0 && d_772d_ != 0 && d_0095 != 0)
            d_0436 = 1;
        if (d_a0fa_ == 0x23) {
            while (d_a0fa_ == 0x23)
                ;
            g2_10f0(2);
            d_02fb = 0;
            asm_05eb(!d_6e0a_);
            asm_05f7(d_6e0a_);
            d_d4c0_ = 0;
            d_d134_ = 0;
        }
        if (d_a0fa_ == 0x19) {
            g2_11f2(2);
            while (d_a0fa_ == 0x19)
                ;
            d_02fb = 0;
            asm_05eb(!d_6e0a_);
            asm_05f7(d_6e0a_);
            d_d4c0_ = 0;
            d_d134_ = 0;
        }
        if (d_a0fa_ == 0x3b && d_c683_ == 0) {
            d_0094 = 0;
            g1_037e(2);
            if (d_0094 != 0) {
                d_0094 = 0;
                g2_14e6();
                if (d_a0fa_ == 0x15) {
                    if (d_02fa == 0 && d_0098 != 0) {
                        d_0098 = 0;
                        d_040e = d_040c;
                    }
                    d_d4c0_ = 0;
                    d_d134_ = 0;
                    d_02fb = 0;
                    goto mode_tail;
                }
                d_02fb = 0;
                asm_05eb(!d_6e0a_);
                asm_05f7(d_6e0a_);
            }
            while (d_a0fa_ == 1)
                ;
            d_d4c0_ = 0;
            d_d134_ = 0;
            d_02fb = 0;
            asm_05eb(!d_6e0a_);
            asm_05f7(d_6e0a_);
        }
        if (d_a0fa_ == 0x1f && d_c683_ == 0) {
            g2_1058(2);
            while (d_a0fa_ == 0x1f)
                ;
            d_02fb = 0;
            asm_05eb(!d_6e0a_);
            asm_05f7(d_6e0a_);
            d_d4c0_ = 0;
            d_d134_ = 0;
        }

        if (d_d148_ != 0 && d_4ed0_ > 0) {
            --d_4ed0_;
            asm_02ad(0x3500, 4);
        }
        if (d_0643 != 0 && d_4ed0_ <= 8) {
            ++d_4ed0_;
            asm_02ad(0x3520, 4);
        }
        asm_05eb(d_6e0a_);
        asm_05f7(d_6e0a_ = !d_6e0a_);
        if (d_0436 == 1) {
            if (d_0098 == 1) {
                d_0098 = 0;
                d_040e = d_040c;
            }
            if (d_0098 == 2) {
                d_0098 = 0;
                d_0410 = d_040c;
                goto return_without_c683_reset;
            }
            if (d_c683_ != 0)
                wait = 1;
            ++d_02fa;
            g1_e3e0(d_03a4[d_02fa]);
            if (d_02fa % 2 != 0) {
                i = 0;
                if (d_d247_ != 0) {
                    g1_2a40(0xb40, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0xc80, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    i += 0x100;
                    g1_0b85(0x2710L);
                }
                if (d_4ed6_ != 0 && d_d57c_ != 0) {
                    g1_2a40(0x8c0, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0xa00, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    i += 0x100;
                    g1_0b85(0x2710L);
                    d_4ed6_ = 0;
                    d_d57c_ = 0;
                }
                if (d_531c_ != 0) {
                    g1_2a40(0xdc0, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0xf00, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_0b85(0x2710L);
                    d_531c_ = 0;
                }
                d_d247_ = 1;
                if (d_4ed8_ != 0 && d_5006_ != 0) {
                    g1_2a40(0x1040, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0x1180, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    i += 0x100;
                    g1_0b85(0x2710L);
                    d_4ed8_ = 0;
                }
                if (d_530c_ != 0) {
                    g1_2a40(0x12c0, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0x1400, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_0b85(0x2710L);
                    i += 0x100;
                    d_530c_ = 0;
                }
                if (d_5310_ != 0) {
                    g1_2a40(0x1540, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0x1680, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_0b85(0x2710L);
                    i += 0x100;
                    d_5310_ = 0;
                }
                if (d_5312_ != 0) {
                    g1_2a40(0x17c0, d_0099 + d_009d + 4,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_2a40(0x1900, d_0099 + d_009d + 6,
                            (((d_009b - 29) >> 4) << 7) + i + d_009f + 0x300);
                    g1_0b85(0x2710L);
                    i += 0x100;
                    d_5312_ = 0;
                }
                g1_0151('T');
            }
        }
        if (d_4ed4_ < 2) {
            if (d_6e0a_ == 0) {
                asm_02ad(0x3540, 0x660);
                asm_02ad(0x3560, 0x662);
            } else {
                asm_02ad(0x3480, 0x660);
                asm_02ad(0x34a0, 0x662);
            }
        } else {
            outport(0x3ce, 0x0105);
            asm_02ad(0x3480, 0x660);
            asm_02ad(0x34a0, 0x662);
        }
        if (d_03a1 != 0) {
            ++d_03a1;
            if (d_03a1 < 0x0f)
                g1_0042(10);
        switch (d_03a1) {
        case 1:
            g1_314c(d_0099 + d_009d,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
            goto case_two_seven;
        case 3:
            g1_314c(d_0099 + d_009d - 2,
                    128 - (((d_009b - 16) >> 4) << 7) + d_009f);
        case 4:
            g1_314c(d_0099 + d_009d + 2,
                    128 - (((d_009b - 16) >> 4) << 7) + d_009f);
            break;
        case 5:
            g1_314c(d_0099 + d_009d - 3,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
        case 6:
            g1_314c(d_0099 + d_009d + 3,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
            break;
        case_two_seven:
        case 2:
        case 7:
            g1_314c(d_0099 + d_009d,
                    (((d_009b - 16) >> 4) << 7) + d_009f + 128);
            break;
        case 8:
            g1_314c(d_0099 + d_009d,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
            break;
        case 10:
        case 15:
            g1_314c(d_0099 + d_009d - 2,
                    128 - (((d_009b - 16) >> 4) << 7) + d_009f);
        case 11:
        case 16:
            g1_314c(d_0099 + d_009d + 3,
                    128 - (((d_009b - 16) >> 4) << 7) + d_009f);
            break;
        case 12:
        case 17:
            g1_314c(d_0099 + d_009d - 3,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
            break;
        case 13:
        case 18:
            g1_314c(d_0099 + d_009d + 2,
                    (((d_009b - 16) >> 4) << 7) + d_009f);
        case 9:
        case 14:
        case 19:
            g1_314c(d_0099 + d_009d,
                    128 - (((d_009b - 16) >> 4) << 7) + d_009f);
            break;
        }
        }

        if (d_4ed4_ == 0 && d_03a1 == 0)
            d_03a1 = 1;
        if ((d_4ed4_ == 0 && d_c683_ == 0 && d_03a1 == 0x1e) ||
            (d_a0fa_ == 0x44 && d_02fa % 2 == 0)) {
            if (d_a0fa_ == 0x44) {
                g2_14e6();
                if (d_a0fa_ == 0x15) {
                    if (d_02fa != 0)
                        goto mode_tail;
                    if (d_0098 == 0)
                        goto mode_tail;
                    d_0098 = 0;
                    d_040e = d_040c;
                    goto mode_tail;
                } else {
                    d_02fb = 0;
                    asm_05eb(!d_6e0a_);
                    asm_05f7(d_6e0a_);
                }
                goto post_mode;
            } else {
                g1_0042(0);
                if (d_02fa != 0) {
                    g2_3d8c(2, 1, 2);
                    g2_3c9a();
                    while (d_02fb < 100)
                        ;
                    d_02fb = 0;
                    do {
                        d_a0fa_ = 0;
                        g2_2870(0x1a, 6);
                    } while (d_a0fa_ != 0x1c);
                    d_d134_ = 0;
                    d_d4c0_ = 0;
                }
            }
        } else {
            goto post_mode;
        }
    mode_tail:
        d_a0fa_ = 0;
        asm_05eb(0);
        g2_29a2();
        asm_05eb(1);
        g2_29a2();
        d_6e0a_ = 0;
        asm_05eb(d_6e0a_);
        asm_05f7(d_6e0a_);
        d_03a1 = 0;
        d_5318_ = 0;
        d_03a3 = 1;
        d_554c_ = 'T';
        if (d_0098 != 0)
            d_040e = d_040c;
        d_0098 = 0;
        g2_29a2();
        g1_e655();
        d_9682_ = 0;
        d_9b38_ = 0;
        if (d_798a_ != 0)
            g2_1ffa(d_a0fb_ + 0x640);
        if (d_a0f8_ != 0)
            g2_1ffa(d_a0fb_ + 0xb40);
        if (d_cc82_ != 0)
            g2_1ffa(d_a0fb_ + 0x2760);
        d_b3d4_ = 0;

    post_mode:
        if (wait == 1)
            goto state_tail;
        if (d_c683_ == 0)
            goto state_c293;
        if (d_a0fa_ != 0)
            goto state_tail;
        if (d_4ed4_ == 0)
            goto state_tail;
    state_c293:
        if (d_c293_ == 0)
            goto state_event;
        g1_e947();
        asm_05eb(d_6e0a_);
        asm_05f7(!d_6e0a_);
        d_6e0a_ = 0;
        asm_05eb(0);
        g2_3114();
        goto post_state_g1;
    state_event:
        if (d_a0fa_ != 1 && d_a0fa_ != 0x10)
            continue;
        while (d_a0fa_ == 0x10)
            ;
    state_tail:
        if (d_c683_ != 0)
            goto reset_c683_exit;
        if (g2_3d1e(2) == 0) {
            d_02fb = 0;
            asm_05eb(d_6e0a_);
            asm_05f7(!d_6e0a_);
            d_d4c0_ = 0;
            d_d134_ = 0;
            continue;
        }
        g1_0042(8);
        if (wait == 0) {
            if (d_0098 == 2)
                d_0410 = d_040c;
            if (d_0098 == 1)
                d_040e = d_040c;
        }
        d_6e0a_ = 0;
        asm_05eb(0);
        g2_3114();
    post_state_g1:
        asm_05f7(0);
        g1_0928();
        while ((d_a0fa_ & 0x80) == 0)
            ;
        d_a0fa_ = 0;
        g2_1d40(7);
        delay(300);
        g2_2870(0x1f, 0x14);
        d_02fb = 0;
        d_0098 = 0;
    reset_c683_exit:
        d_c683_ = 0;
    return_without_c683_reset:
        return;
    }
}

/* g1_fc85 */
void pascal g1_fc85(void)
{
    g1_e655();
    if (!d_5318_) {
        g1_0151('T');
        g1_ecf4();
    }
}

/* g1_fc9c */
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

/* g1_fd15 */
void pascal g1_fd15(void)
{
    register int state;

    for (;;) {
        g2_3114();
        state = g1_049f(7);

        d_5a11_ = 0;
        d_5c6b_ = 0;
        d_5554_ = 0;
        d_637e_ = 0;
        d_5ec8_ = 0;
        d_555a_ = 0;
        d_555c_ = 0;
        d_5553_ = 0;
        d_555b_ = 0;
        d_68f7_ = 0;
        d_5555_ = 0;
        d_5c6a_ = 0;

        if (state == 1) {
            d_c683_ = 0;
            d_c278_ = 1;
            d_040c = 0;
            d_0098 = 1;
            d_03a3 = 0;
            g2_01a9(0x14);
            g2_340f();
            g2_0036(0x14);
            if (d_cc81_ == 0) {
                while ((d_a0fa_ & 0x80) == 0) {
                }
            }
            g2_3bd7();
            g2_01a9(0x14);
            g2_3568();
            g2_0036(0x14);
            if (d_cc81_ == 0) {
                while ((d_a0fa_ & 0x80) == 0) {
                }
            }
            g2_3c38();
            d_530e_ = 0;
            g2_0009(0x14);
            if (d_0b46 == 1) {
                d_5a11_ = 1;
                d_5c6b_ = 1;
                d_5554_ = 1;
                d_637e_ = 1;
                d_5ec8_ = 1;
                d_555a_ = 1;
                d_555c_ = 1;
                d_5553_ = 1;
                d_555b_ = 1;
                d_68f7_ = 1;
                d_5555_ = 1;
                d_5c6a_ = 1;
            }
            g1_0042(0x1a);
            return;
        }

        if (state == 2) {
            if (d_c278_ == 0)
                continue;
            d_c683_ = 1;
            d_0098 = 0;
            d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 3 && g1_0126(7) != 0) {
            d_03a3 = 1;
            d_c683_ = 0;
            d_0098 = 0;
            if (d_0b46 == 1) {
                d_5a11_ = 1;
                d_5c6b_ = 1;
                d_5554_ = 1;
                d_637e_ = 1;
                d_5ec8_ = 1;
                d_555a_ = 1;
                d_555c_ = 1;
                d_5553_ = 1;
                d_555b_ = 1;
                d_68f7_ = 1;
                d_5555_ = 1;
                d_5c6a_ = 1;
            }
            return;
        }

        if (state == 4) {
            d_c683_ = 0;
            d_c278_ = 1;
            d_040c = 0;
            d_0098 = 2;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 5) {
            if (d_c278_ == 0)
                continue;
            d_c683_ = 2;
            d_0098 = 0;
            d_040c = 0;
            d_03a3 = 0;
            g2_0009(0x14);
            return;
        }

        if (state == 0) {
            g2_01a9(0x14);
            g1_fc9c();
            continue;
        }
    }
}

/* g1_ff16 */
void main(int argc, char **argv)
{
    if (argv[1][0] == 'a' && argv[1][1] == 's' && argv[1][2] == 'p') {
        d_0095 = 1;
        if (argv[2][0] == 'g')
            d_039d = 1;
    }
    g1_ec3d();
    for (;;) {
        g1_fd15();
        g1_fc85();
        g2_01a9(15);
        d_5318_ = 0;
    }
}

