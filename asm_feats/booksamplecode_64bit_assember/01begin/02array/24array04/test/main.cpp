#include <stdio.h>

int
main(void)
{
    int a[100];

    __asm
    {
        mov a[0 * type a], 1
        mov a[1 * type a], 2
        mov a[2 * type a], 3
        mov a[3 * type a], 4
        mov a[4 * type a], 5
    }

    for (int i = 0; i < 5; i++)
        printf("a[%d] = %d\n", i, a[i]);

    return 0;
}
