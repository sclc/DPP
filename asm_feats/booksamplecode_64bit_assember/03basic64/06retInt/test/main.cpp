#include <stdio.h>

extern "C" int asmSample(int a, int b);

int
main(void)
{
    int a=0, b=2, c=3;

    a = asmSample(b, c);
    printf("%d + %d = %d\n", b, c, a);

    return 0;
}
