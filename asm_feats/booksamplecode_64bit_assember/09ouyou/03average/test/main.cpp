#include <stdio.h>
#include <stdlib.h>

extern "C" int asmCode(size_t num, int* a);

int
main(void)
{
    int a[100000];
	size_t length = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < length; i++)
        a[i] = rand() - (RAND_MAX / 2);

    int sum = 0;
    for (int i = 0; i < length; i++)
        sum += a[i];
    int avarage = sum / length;
    printf("avarage=%d\n", avarage);

    avarage = asmCode(length, a);
    printf("avarage=%d\n", avarage);

    return 0;
}
