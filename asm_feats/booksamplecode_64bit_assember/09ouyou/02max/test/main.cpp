#include <stdio.h>
#include <stdlib.h>

extern "C" int asmCode(size_t num, int* a);

int
main(void)
{
    int a[100000], max;
	size_t length = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < length; i++)
        a[i] = rand() - (RAND_MAX / 2);

    max = INT_MIN;
    for (int i = 0; i < length; i++)
        max = max < a[i] ? a[i] : max;
    printf("max=%d\n", max);

    max = asmCode(length, a);
    printf("max=%d\n", max);

    return 0;
}
