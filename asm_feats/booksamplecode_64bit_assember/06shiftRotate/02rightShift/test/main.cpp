#include <stdio.h>

extern "C" {
    int rightSigned(int a, char shift);
    int rightUnsigned(int a, char shift);
}

int
main(void)
{
    int a, b = 4, c = -4;

    a = rightSigned(b, 1);
    printf("sar: %10d >> 1 = %10d\n", b, a);
    printf("sar: 0x%08X >> 1 = 0x%08X\n\n", b, a);

    a = rightSigned(c, 1);
    printf("sar: %10d >> 1 = %10d\n", c, a);
    printf("sar: 0x%08X >> 1 = 0x%08X\n\n", c, a);

    a = rightUnsigned(b, 1);
    printf("shr: %10d >> 1 = %10d\n", b, a);
    printf("shr: 0x%08X >> 1 = 0x%08X\n\n", b, a);

    a = rightUnsigned(c, 1);
    printf("shr: %10d >> 1 = %10d\n", c, a);
    printf("shr: 0x%08X >> 1 = 0x%08X\n\n", c, a);

    return 0;
}
