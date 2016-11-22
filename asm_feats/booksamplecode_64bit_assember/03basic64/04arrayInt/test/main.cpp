#include <stdio.h>

extern "C" void asmSample(int a[]);

int
main(void)
{
    int a[100];

    asmSample(a);
    for (int i = 0; i < 5; i++)
        printf("a[%d] = %d\n", i, a[i]);

    return 0;
}
