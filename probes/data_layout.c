/* Probe: order of initialised globals, string literals, statics and BSS in a
   Turbo C 2.0 large-model unit's _DATA/_BSS (rule DATA-LAYOUT). */
int first_init = 0x1111;
char *msg_ptr = "ptr-literal";
int zero_init = 0;
int uninit_a;
static int static_init = 0x2222;
static int static_uninit;
void f1(void) { extern void sink(char *); sink("in-f1-a"); sink("in-f1-b"); }
int second_init = 0x3333;
int uninit_b;
void f2(void) { extern void sink(char *); sink("in-f2"); sink("in-f1-a"); static_uninit = static_init; }
char last_init[3] = { 1, 2, 3 };
