extern void (far *d_514b_[])(void);
extern int d_554d_;
/*@body*/
void pascal g1_c243(void (far *key)(void))
{
    register int i;

    for (i = 0; i < d_554d_; ++i) {
        if (d_514b_[i] == key)
            return;
    }
    d_514b_[i] = key;
    ++d_554d_;
}
