#include <stdio.h>

extern "C" void asmSample(int* a, int b);

int
main(void)
{
    int a = 0, b = 2;

    asmSample(&a, b);

    printf("a = %d\n", a);

    return 0;
}
