/* Wait out an 0xE0 extended-key prefix in the keyboard byte, then return it
   with the release bit cleared (interrupts left disabled). */
#include <dos.h>
extern char d_a0fa;
/*@body*/
char g2_276f(void)
{
    if (d_a0fa == 0xe0) {
        while (d_a0fa == 0xe0)
            ;
        disable();
        return d_a0fa & 0x7f;
    }
    return d_a0fa;
}
