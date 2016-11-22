#include <stdio.h>

extern "C" int equal(int a, int b);

int
main(void)
{
    int a = 5, b = 5;

    if (equal(a, b))
        printf("%d == %d\n", a, b);
    else
        printf("%d != %d\n", a, b);

    a = 2;

    if (equal(a, b))
        printf("%d == %d\n", a, b);
    else
        printf("%d != %d\n", a, b);

    return 0;
}
