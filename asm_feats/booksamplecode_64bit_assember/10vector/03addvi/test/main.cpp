#include <stdio.h>
#include <stdlib.h>

extern "C" void asmCode(size_t length, int a[], int b[], int c[]);

int
main(void)
{
	const size_t length = 1024;        // length must be an integer multiple of 4
    int srca[length], srcb[length], dstAsm[length], dstCpp[length];
    static_assert((length % 4) == 0, "error length.");

    for (int i = 0; i < length; i++)
    {
        srca[i] = rand();
        srcb[i] = rand();
    }


    for (int i = 0; i < length; i++)
        dstCpp[i] = srca[i] + srcb[i];

    asmCode(length, srca, srcb, dstAsm);


    for (int i = 0; i < length; i++)
        if (dstCpp[i] != dstAsm[i])
            printf("i = %d, %d != %d\n", i, dstCpp[i], dstAsm[i]);

    return 0;
}
