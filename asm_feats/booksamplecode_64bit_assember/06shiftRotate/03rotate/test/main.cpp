#include <stdio.h>

extern "C" {
    int left(int a, char bits);
    int right(int a, char bits);
    int stcLeft(int a, char bits);
    int clcRight(int a, char bits);
}

int
main(void)
{
    int a, b = 0xF00FF00F, c = -1;

    a = left(b, 2);
    printf("rol: 0x%08X << 2 = 0x%08X\n", b, a);

    a = right(b, 1);
    printf("ror: 0x%08X >> 1 = 0x%08X\n", b, a);

    a = stcLeft(b, 2);
    printf("rcl: 0x%08X << 2 = 0x%08X\n", b, a);

    a = clcRight(b, 1);
    printf("rcr: 0x%08X >> 1 = 0x%08X\n", b, a);

    return 0;
}
