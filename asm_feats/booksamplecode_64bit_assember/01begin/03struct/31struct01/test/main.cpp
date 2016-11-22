#include <stdio.h>

typedef struct {
    char ca;
    short sa;
    int ia;
} struct_t;

int
main(void)
{
    struct_t s = { 0, 0, 0 };


    __asm
    {
        mov s.ca, 10
        mov s.sa, 20
        mov s.ia, 30
    }

    printf("s.ca = %d\n", s.ca);
    printf("s.sa = %d\n", s.sa);
    printf("s.ia = %d\n", s.ia);

    return 0;
}
