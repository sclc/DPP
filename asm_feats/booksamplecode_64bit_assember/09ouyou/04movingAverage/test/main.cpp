#include <stdio.h>
#include <stdlib.h>

extern "C" void asmCode(int window, int total, int* a, int* a_r);

int
main(void)
{
    const int totalLength = 10000;
    const int windowSize = 5;
    int a[totalLength], c_r[totalLength], a_r[totalLength];

    for (int i = 0; i < windowSize; i++)
        a[i] = rand() - (RAND_MAX / 2);

    for (int i = 0; i < totalLength - windowSize; i++)
    {
        int sum = 0;
        for (int w = i; w < i + windowSize; w++)
            sum += a[w];
        c_r[i] = sum / windowSize;
    }

    asmCode(windowSize, totalLength, a, a_r);

    for (int i = 0; i < totalLength - windowSize; i++)
        if (c_r[i] != a_r[i])
            printf("error: i=%d\n", i);

    return 0;
}
