#include <stdio.h>

int
main(void)
{
    char ca = 0;
    short sa = 0;
    int ia = 0;

    __asm
    {
        mov eax, 0x01020304 // eax=0x01020304
        mov byte ptr ca, al
        mov word ptr sa, ax
        mov dword ptr ia, eax
    }

    printf("a = 0x%02X\n", ca);
    printf("b = 0x%04X\n", sa);
    printf("c = 0x%08X\n", ia);

    return 0;
}
