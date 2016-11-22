#include <stdio.h>

extern "C" {
    int leftSigned(int a, char shift);
    int leftUnsigned(int a, char shift);
}

int
main(void)
{
    int a, b = 4, c = 0xDFFFFFFF;

    a = leftSigned(b, 1);
    printf("sal: %11d << 1 = %d\n", b, a);
    printf("sal:  0x%08X << 1 = 0x%08X\n\n", b, a);

    a = leftSigned(c, 2);
    printf("sal: %11d << 2 = %d\n", c, a);
    printf("sal:  0x%08X << 2 = 0x%08X\n\n", c, a);

    a = leftUnsigned(b, 1);
    printf("shl: %11d << 1 = %d\n", b, a);
    printf("shl:  0x%08X << 1 = 0x%08X\n\n", b, a);

    a = leftUnsigned(c, 2);
    printf("shl: %11d << 2 = %d\n", c, a);
    printf("shl:  0x%08X << 2 = 0x%08X\n\n", c, a);

    return 0;
}
