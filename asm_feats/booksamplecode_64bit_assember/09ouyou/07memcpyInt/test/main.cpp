#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" void asmCode(int *destination, int *source, size_t length);

int
main(void)
{
    const int length = 1024;
    int src[length], dstAsm[length], dstCpp[length];

    for (int i = 0; i < length; i++)
        src[i] = rand() - (RAND_MAX / 2);

    memcpy(dstCpp, src, sizeof(src));
    asmCode(dstAsm, src, sizeof(src));

    for (int i = 0; i < length; i++)
        if (dstCpp[i] != dstAsm[i])
            printf("error: i=%d\n", i);

    return 0;
}
