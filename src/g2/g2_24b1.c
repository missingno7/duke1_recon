#include <stdio.h>
#include <string.h>
extern long d_4fa2[];
extern long d_4fa6[];
extern long d_4faa[];
extern long d_4fae[];
extern long d_4fb2[];
extern char d_5008[10][11];
extern char d_5013[11];
extern char d_501e[11];
extern char d_5029[11];
extern char d_5034[11];
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
        d_4fa2[0] = 40000L;
        strcpy(&d_5008[0][0], "TODD");
        d_4fa6[0] = 30000L;
        strcpy(d_5013, "SCOTT");
        d_4faa[0] = 20000L;
        strcpy(d_501e, "GEORGE");
        d_4fae[0] = 10000L;
        strcpy(d_5029, "AL");
        d_4fb2[0] = 500L;
        strcpy(d_5034, "JOHN");
    } else {
        for (i = 0; i < 10; i++) {
            fscanf(stream, "%lu", &d_4fa2[i]);
            fscanf(stream, "%[^\n]s", d_5008[i]);
        }
    }
    fclose(stream);
}
