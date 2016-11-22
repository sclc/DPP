#include <stdio.h>

extern "C" void asmSample(int* a);  // assembler function

int
main(void)
{
    int a = 0;

    asmSample(&a);
    printf("a=%d\n", a);

    return 0;
}
