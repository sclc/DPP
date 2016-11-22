#include <stdio.h>

extern "C" {
    int addfunc(int a, int b);
    int subfunc(int a, int b);
}

int
main(void)
{
    int a = 0, b = 2, c = 3;

    a = addfunc(b, c);
    printf("%d + %d = %d\n", b, c, a);

    a = subfunc(b, c);
    printf("%d - %d = %d\n", b, c, a);

    return 0;
}
