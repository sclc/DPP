#include <stdio.h>
#include <stdlib.h>

extern "C" void asmCode(size_t length, short a[], short b[], short c[]);

int
main(void)
{
	const size_t length = 1024;        // length must be an integer multiple of 8
    const int SHORT_MAX = 32767, SHORT_MIN = -32768;
    short srca[length], srcb[length], dstAsm[length], dstCpp[length];
    static_assert((length % 8) == 0, "error length.");

    for (int i = 0; i < length; i++)
    {
        srca[i] = (short)rand();
        srcb[i] = (short)rand();
    }


    for (int i = 0; i < length; i++)
    {
        int r = srca[i] + srcb[i];  // saturate r to SHORT MIN from SHRT_MAX
        if (r > SHORT_MAX)
            r = SHORT_MAX;
        else
        if (r < SHORT_MIN)
            r = SHORT_MIN;
        dstCpp[i] = r;
    }

    asmCode(length, srca, srcb, dstAsm);


    for (int i = 0; i < length; i++)
        if (dstCpp[i] != dstAsm[i])
            printf("i = %d, %d != %d\n", i, dstCpp[i], dstAsm[i]);

    return 0;
}
