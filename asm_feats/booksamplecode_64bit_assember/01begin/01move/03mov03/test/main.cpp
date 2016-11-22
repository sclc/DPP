#include <stdio.h>

int
main(void)
{
    int a=0,  b=2;

    __asm
    {
        mov eax, b
        mov a, eax
    }

    printf("a = %d\n", a);

    return 0;
}
