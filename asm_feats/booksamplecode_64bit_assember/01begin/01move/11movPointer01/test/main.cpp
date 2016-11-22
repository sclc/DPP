#include <stdio.h>

int
main(void)
{
    char a = 10, b = 0;
    char* pb = &b;

    __asm
    {
        mov eax, pb             // eax=pb
        mov bl, byte ptr a      // bl = a
        mov byte ptr [eax], bl  // *pb = a
    }

    printf("b = %d\n", b);

    return 0;
}
