#include <stdio.h>
#include <stdlib.h>

extern "C" int asmCode(size_t num, int* a);

int
main(void)
{
    int a[100000], min;
    size_t length = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < length; i++)
        a[i] = rand() - (RAND_MAX / 2);

    min = INT_MAX;
    for (int i = 0; i < length; i++)
        min = min>a[i] ? a[i] : min;
    printf("min=%d\n", min);

    min = asmCode(length, a);
    printf("min=%d\n", min);

    return 0;
}
