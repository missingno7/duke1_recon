#include <stdio.h>
extern long d_4fa2[];
extern char d_5008[10][11];
/*@body*/
void g2_1e1b(void)
{
    FILE *stream;
    register int i;
#if EPISODE == 1
    stream = fopen("HIGHS.DN1", "w+");
#elif EPISODE == 2
    stream = fopen("HIGHS.dn2", "w+");
#else
    stream = fopen("HIGHS.dn3", "w+");
#endif
    for (i = 0; i < 10; i++) {
        fprintf(stream, "%lu", d_4fa2[i]);
        fprintf(stream, "%s\n", d_5008[i]);
    }
    fclose(stream);
}


