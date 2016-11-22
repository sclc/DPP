#include <stdio.h>

extern "C" {
    int mulfunc(int a, int b);
    int divfunc(int a, int b);
}

int
main(void)
{
    int a, b = -2, c = 3;

    a = mulfunc(b, c);
    printf("%d * %d = %d\n", b, c, a);

    b = -31, c = -5;
    a = divfunc(b, c);
    printf("%d / %d = %d\n", b, c, a);

    return 0;
}
