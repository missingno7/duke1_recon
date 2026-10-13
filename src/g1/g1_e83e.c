#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
/*@body*/
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
