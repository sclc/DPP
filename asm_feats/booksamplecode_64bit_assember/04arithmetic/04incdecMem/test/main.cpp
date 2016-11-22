#include <stdio.h>

extern "C" {
    void incfunc(int *a);
    void decfunc(int *a);
}

int
main(void)
{
    int a = -10;

    incfunc(&a);
    printf("a = %d\n", a);

    decfunc(&a);
    printf("a = %d\n", a);

    return 0;
}
