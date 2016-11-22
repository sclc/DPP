#include <stdio.h>

extern "C" int asmCode(void);

int
main(void)
{
    int a = asmCode();
    printf("a=%d\n", a);

    return 0;
}
