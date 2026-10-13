/* g1_de71 candidate 3 */
#include <stdio.h>
extern int d_040e;
extern char d_530e_;
extern char d_c278_;
/*@body*/
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
