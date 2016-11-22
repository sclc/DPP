#include <stdio.h>

extern "C" {
    int incfunc(int a);
    int decfunc(int a);
}

int
main(void)
{
    int a = 0;

    a = incfunc(a);
    printf("a = %d\n", a);

    a = decfunc(a);
    printf("a = %d\n", a);

    return 0;
}
