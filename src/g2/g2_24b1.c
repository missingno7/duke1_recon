#include <stdio.h>
#include <string.h>
extern long d_4fa2_[];
extern long d_4fa6_[];
extern long d_4faa_[];
extern long d_4fae_[];
extern long d_4fb2_[];
extern char d_5008_[10][11];
extern char d_5013_[11];
extern char d_501e_[11];
extern char d_5029_[11];
extern char d_5034_[11];
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
        strcpy(&d_5008_[0][0], "TODD");
        d_4fa6_[0] = 30000L;
        strcpy(d_5013_, "SCOTT");
        d_4faa_[0] = 20000L;
        strcpy(d_501e_, "GEORGE");
        d_4fae_[0] = 10000L;
        strcpy(d_5029_, "AL");
        d_4fb2_[0] = 500L;
        strcpy(d_5034_, "JOHN");
    } else {
        for (i = 0; i < 10; i++) {
            fscanf(stream, "%lu", &d_4fa2_[i]);
            fscanf(stream, "%[^\n]s", d_5008_[i]);
        }
    }
    fclose(stream);
}
