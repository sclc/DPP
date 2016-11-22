#include <stdio.h>

extern "C" void asmSample(char* ca, short* sa, int* ia);

int
main(void)
{
    char ca = 0;
    short sa = 0;
    int ia = 0;

    asmSample(&ca, &sa, &ia);
    printf("a = 0x%02X, %d\n", ca, ca);
    printf("b = 0x%04X, %d\n", sa, sa);
    printf("c = 0x%08X, %d\n", ia, ia);

    return 0;
}
