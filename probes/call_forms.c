/* Discriminating probe: how Turbo C 2.0 (large model) emits calls inside one
   translation unit.  Checked by tools/probe.py (rule CALL-FORMS). */
extern int g;
void ext_fn(int a);
int earlier(int a, int b) { return a + b; }
void later(void);
static void st_earlier(void) { g--; }
static void st_later(void);
void caller(int x)
{
    ext_fn(x);
    earlier(x, 1);
    later();
    st_earlier();
    st_later();
    g = (int)(long)(void far *)earlier;
}
void later(void) { g++; }
static void st_later(void) { g = 0; }
