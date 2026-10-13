#include <stdio.h>
#include <string.h>
extern long d_4fa2_[];
extern long d_4fa6_[];
extern long d_4faa_[];
extern long d_4fae_[];
extern long d_4fb2_[];
extern char d_5008_[10][11];
/*@body*/
void g2_24b1(void)
{
    FILE *stream;
    register int i;

#if EPISODE == 1
    stream = fopen("HIGHS.DN1", "r");
#elif EPISODE == 2
    stream = fopen("HIGHS.dn2", "r");
#else
    stream = fopen("HIGHS.dn3", "r");
#endif
    if (stream == 0) {
        d_4fa2_[0] = 40000L;
        strcpy(d_5008_[0], "TODD");
        d_4fa6_[0] = 30000L;
        strcpy(d_5008_[1], "SCOTT");
        d_4faa_[0] = 20000L;
        strcpy(d_5008_[2], "GEORGE");
        d_4fae_[0] = 10000L;
        strcpy(d_5008_[3], "AL");
        d_4fb2_[0] = 500L;
        strcpy(d_5008_[4], "JOHN");
    } else {
        for (i = 0; i < 10; i++) {
            fscanf(stream, "%lu", &d_4fa2_[i]);
            fscanf(stream, "%[^\n]s", d_5008_[i]);
        }
    }
    fclose(stream);
}
