#include <stdio.h>

extern "C" int eq5(int a);

int
main(void)
{
    int a = 5;

    if (eq5(a))
        printf("%d == 5\n", a);
    else
        printf("%d != 5\n", a);

    a = 2;

    if (eq5(a))
        printf("%d == 5\n", a);
    else
        printf("%d != 5\n", a);

    return 0;
}
