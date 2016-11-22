#include <stdio.h>

extern "C" int xorfunc(int a, int b);

int
main(void)
{
    int a, b = 0xAA55FF00, c = 0x55AA55AA;

    a = xorfunc(b, c);
    printf("0x%08X xor 0x%08X = 0x%08X\n", b, c, a);

    return 0;
}
