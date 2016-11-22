#include <stdio.h>

extern "C" int comp(int a, int b);

int
main(void)
{
    int a = 5, b= -5;
    char gtlt;

    gtlt = comp(a, b) != 0 ? '>' : '<';
    printf("%3d %c %3d, (0x%08X %c 0x%08X)\n", a, gtlt, b, a, gtlt, b);

    b = 100;
    gtlt = comp(a, b) != 0 ? '>' : '<';
    printf("%3d %c %3d, (0x%08X %c 0x%08X)\n", a, gtlt, b, a, gtlt, b);

    return 0;
}
