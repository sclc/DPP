#include <stdio.h>

int
main(void)
{
    int a = 0;

    __asm
    {
        mov a, 1
    }

    printf("a = %d\n", a);

    return 0;
}
