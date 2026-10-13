/* G2 BSS objects in ascending DN1 address order. Each typed array spans to the next object start. */
/* Accepted G1 struct definitions required by G2 BSS arrays. */
struct Record {
    int reserved;
    int y;
    int x;
    int height;
    int state;
};

struct g1_3882_record { int used, x, y; };

struct g1_4f91_record { int state, x, y, marker; };

struct g1_54e1_record { int state, x, y; };

struct g1_5b0b_record { int state, x, y; };

struct g1_5d6f_record { int active, x, y, state; };

struct g1_5f0c_record { int state, x, y, field3; };

struct g1_6e71_record { int state, x, y; };

struct g1_7163_record { int state, x, y; };

struct g1_79d9_record { int state, x, y, flag; };

struct g1_9757_row { int state, x, y; };

struct g1_a218_record { int state, x, y; };

struct g1_af94_record { int state, x, y; };

struct g1_c1b2_record {
    int kind;
    int x;
    int y;
};

struct record {
    int state;
    int x;
    int y;
};

struct s8 { int a, b, c, d; };

struct t_b3d6 { int x, y, used; };

struct t_b63c { int state, x, y, kind; };

struct t_b9de { int offset, x, y, alternate; };

struct t_c8eb { int used, value1, value2; };

struct t_cb6d { int state, x, y, marker; };

struct t_d1cf { int used, x, y; };

/* 0xa0f4; accepted scalar type. */
void interrupt far (*d_a0f4_)(void);
/* 0xa0f8; accepted scalar type. */
int d_a0f8_;
/* 0xa0fa; accepted scalar type. */
char d_a0fa_;
/* 0xa0fb; accepted scalar type. */
char far *d_a0fb_;
/* 0xa0ff; array extent from address gap. */
struct g1_54e1_record d_a0ff_[100];
/* 0xa357; array extent from address gap. */
struct g1_79d9_record d_a357_[100];
/* 0xa677; accepted scalar type. */
int d_a677_;
/* 0xa679; accepted scalar type. */
int d_a679_;
/* 0xa67b; accepted scalar type. */
int d_a67b_;
/* 0xa67d; accepted scalar type. */
char d_a67d_;
/* 0xa67e; accepted scalar type. */
int d_a67e_;
/* 0xa680; array extent from address gap. */
struct g1_af94_record d_a680_[100];
/* 0xa8d8; accepted scalar type. */
char d_a8d8_;
/* 0xa8d9; accepted scalar type. */
char d_a8d9_;
/* 0xa8da; array extent from address gap. */
struct g1_3882_record d_a8da_[100];
/* 0xab32; array extent from address gap. */
struct g1_5d6f_record d_ab32_[20];
/* 0xabd2; accepted scalar type. */
int d_abd2_;
/* 0xabd4; array extent from address gap. */
int d_abd4_[9];
/* 0xabe6; accepted scalar type. */
int d_abe6_;
/* UNREFERENCED: [0xabe8,0xabec) has no accepted object start or direct DS reference. */
char d_abe8_[4];
/* 0xabec; array extent from address gap. */
struct g1_5b0b_record d_abec_[100];
/* 0xae44; array extent from address gap. */
struct g1_a218_record d_ae44_[100];
/* 0xb09c; array extent from address gap. */
int d_b09c_[9];
/* 0xb0ae; accepted scalar type. */
int d_b0ae_;
/* UNREFERENCED: [0xb0b0,0xb0b4) has no accepted object start or direct DS reference. */
char d_b0b0_[4];
/* 0xb0b4; array extent from address gap. */
struct g1_5f0c_record d_b0b4_[100];
/* 0xb3d4; accepted scalar type. */
int d_b3d4_;
/* 0xb3d6; array extent from address gap. */
struct t_b3d6 d_b3d6_[100];
/* 0xb62e; accepted scalar type. */
int d_b62e_;
/* 0xb630; accepted scalar type. */
int d_b630_;
/* 0xb632; accepted scalar type. */
int d_b632_;
/* 0xb634; accepted scalar type. */
int d_b634_;
/* 0xb636; accepted scalar type. */
int d_b636_;
/* 0xb638; accepted scalar type. */
char far *d_b638_;
/* 0xb63c; array extent from address gap. */
struct t_b63c d_b63c_[16];
/* 0xb6bc; array extent from address gap. */
struct g1_4f91_record d_b6bc_[100];
/* 0xb9dc; accepted scalar type. */
int d_b9dc_;
/* 0xb9de; array extent from address gap. */
struct t_b9de d_b9de_[200];
/* 0xc01e; array extent from address gap. */
struct g1_7163_record d_c01e_[100];
/* 0xc276; accepted scalar type. */
int d_c276_;
/* 0xc278; accepted scalar type. */
char d_c278_;
/* 0xc279; accepted scalar type. */
int d_c279_;
/* 0xc27b; accepted scalar type. */
int d_c27b_;
/* 0xc27d; accepted scalar type. */
char far *d_c27d_;
/* 0xc281; accepted scalar type. */
int d_c281_;
/* 0xc283; accepted scalar type. */
int d_c283_;
/* 0xc285; accepted scalar type. */
char far *d_c285_;
/* 0xc289; accepted scalar type. */
int d_c289_;
/* 0xc28b; accepted scalar type. */
int d_c28b_;
/* 0xc28d; accepted scalar type. */
int d_c28d_;
/* 0xc28f; accepted scalar type. */
char far *d_c28f_;
/* 0xc293; accepted scalar type. */
int d_c293_;
/* 0xc295; accepted scalar type. */
int d_c295_;
/* 0xc297; accepted scalar type. */
int d_c297_;
/* 0xc299; array extent from address gap. */
struct Record d_c299_[100];
/* 0xc681; accepted scalar type. */
int d_c681_;
/* 0xc683; accepted scalar type. */
char d_c683_;
/* 0xc684; accepted scalar type. */
int d_c684_;
/* 0xc686; accepted scalar type. */
int d_c686_;
/* 0xc688; accepted scalar type. */
int d_c688_;
/* 0xc68a; accepted scalar type. */
int d_c68a_;
/* 0xc68c; accepted scalar type. */
char d_c68c_;
/* 0xc68d; accepted scalar type. */
int d_c68d_;
/* 0xc68f; accepted scalar type. */
int d_c68f_;
/* 0xc691; array extent from address gap. */
struct record d_c691_[100];
/* 0xc8e9; accepted scalar type. */
int d_c8e9_;
/* 0xc8eb; array extent from address gap. */
struct t_c8eb d_c8eb_[7];
/* 0xc915; array extent from address gap. */
struct g1_9757_row d_c915_[100];
/* 0xcb6d; array extent from address gap. */
struct t_cb6d d_cb6d_[9];
/* 0xcbb5; array extent from address gap. */
char far *d_cbb5_[50];
/* 0xcc7d; accepted scalar type. */
char far *d_cc7d_;
/* 0xcc81; accepted scalar type. */
char d_cc81_;
/* 0xcc82; accepted scalar type. */
int d_cc82_;
/* 0xcc84; array extent from address gap. */
struct g1_c1b2_record d_cc84_[200];
/* 0xd134; accepted scalar type. */
char d_d134_;
/* 0xd135; accepted scalar type. */
char d_d135_;
/* 0xd136; accepted scalar type. */
int d_d136_;
/* 0xd138; accepted scalar type. */
char d_d138_;
/* 0xd139; accepted scalar type. */
int d_d139_;
/* 0xd13b; accepted scalar type. */
int d_d13b_;
/* 0xd13d; accepted scalar type. */
int d_d13d_;
/* 0xd13f; accepted scalar type. */
char d_d13f_;
/* 0xd140; accepted scalar type. */
int d_d140_;
/* 0xd142; accepted scalar type. */
int d_d142_;
/* 0xd144; accepted scalar type. */
unsigned int d_d144_;
/* 0xd146; accepted scalar type. */
int d_d146_;
/* 0xd148; accepted scalar type. */
char d_d148_;
/* 0xd149; array extent from address gap. */
int d_d149_[1];
/* 0xd14b; accepted scalar type. */
int d_d14b_;
/* 0xd14d; accepted scalar type. */
int d_d14d_;
/* UNREFERENCED: [0xd14f,0xd155) has no accepted object start or direct DS reference. */
char d_d14f_[6];
/* 0xd155; accepted scalar type. */
int d_d155_;
/* 0xd157; array extent from address gap. */
struct t_b9de d_d157_[15];
/* 0xd1cf; array extent from address gap. */
struct t_d1cf d_d1cf_[20];
/* 0xd247; accepted scalar type. */
int d_d247_;
/* 0xd249; array extent from address gap. */
int d_d249_[12];
/* 0xd261; array extent from address gap. */
struct g1_6e71_record d_d261_[100];
/* 0xd4b9; accepted scalar type. */
int d_d4b9_;
/* 0xd4bb; accepted scalar type. */
int d_d4bb_;
/* 0xd4bd; accepted scalar type. */
int d_d4bd_;
/* 0xd4bf; accepted scalar type. */
char d_d4bf_;
/* 0xd4c0; accepted scalar type. */
char d_d4c0_;
/* 0xd4c1; accepted scalar type. */
int d_d4c1_;
/* 0xd4c3; array extent from address gap. */
struct s8 d_d4c3_[21];
/* 0xd56b; accepted scalar type. */
char d_d56b_;
/* 0xd56c; accepted scalar type. */
int d_d56c_;
/* 0xd56e; accepted scalar type. */
int d_d56e_;
/* 0xd570; accepted scalar type. */
int d_d570_;
/* 0xd572; accepted scalar type. */
int d_d572_;
/* 0xd574; accepted scalar type. */
int d_d574_;
/* 0xd576; accepted scalar type. */
char d_d576_;
/* 0xd577; accepted scalar type. */
int d_d577_;
/* 0xd579; accepted scalar type. */
char d_d579_;
/* 0xd57a; accepted scalar type. */
int d_d57a_;
/* 0xd57c; accepted scalar type. */
int d_d57c_;
/* 0xd57e; array extent from address gap. */
int d_d57e_[100];
/* 0xd646; array extent from address gap. */
int d_d646_[100];
/* 0xd70e; accepted scalar type. */
int d_d70e_;
/* 0xd710; accepted scalar type. */
char far *d_d710_;
/* 0xd714; accepted scalar type. */
char far *d_d714_;
/* 0xd718; accepted scalar type. */
int d_d718_;
