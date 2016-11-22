#include <stdio.h>

extern "C" {
    int andfunc(int a, int b);
    int orfunc(int a, int b);
}

int
main(void)
{
    int a = 0, b = 0xAA55FF00, c = 0x55AA55AA;

    a = andfunc(b, c);
    printf("0x%08X & 0x%08X = 0x%08X\n", b, c, a);

    a = orfunc(b, c);
    printf("0x%08X | 0x%08X = 0x%08X\n", b, c, a);

    return 0;
}
