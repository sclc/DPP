//a[0] = 1
//a[1] = 2
//a[2] = 3
//a[3] = 4
//a[4] = 5
#include <stdio.h>

extern "C" void asmSample(short a[]);

int
main(void)
{
    short a[100];

    asmSample(a);
    for (int i = 0; i < 5; i++)
        printf("a[%d] = %d\n", i, a[i]);

    return 0;
}
