#include <stdio.h>

extern "C" int loopSum(void);

int
main(void)
{
    int sum;

    sum = 0;
    for (int i = 0; i < 100; i++)
        sum += i;
    printf("sum=%d\n", sum);

    sum = loopSum();
    printf("sum=%d\n", sum);

    return 0;
}
