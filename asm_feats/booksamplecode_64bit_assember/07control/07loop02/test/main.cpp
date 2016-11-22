#include <stdio.h>

extern "C" void arrayAdd(int a[], size_t numOfarray);

int
main(void)
{
    int a[100], b[100];
    size_t numOfarray = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < numOfarray; i++)
        a[i] = b[i] = i % 16;

    arrayAdd(b, numOfarray);

    for (int i = 0; i < numOfarray; i++)
        a[i] += 2;

    for (int i = 0; i < numOfarray; i++)
        if (a[i] != b[i])
            printf("a[%d]=%d, b[%d]=%d\n", i, a[i], i, b[i]);

    return 0;
}
