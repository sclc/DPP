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
    struct_t* ps = &s;

    __asm
    {
        mov eax, ps
        mov [eax]s.ca, 10
        mov [eax]s.sa, 20
        mov [eax]s.ia, 30
    }

    printf("s.ca = %d\n", s.ca);
    printf("s.sa = %d\n", s.sa);
    printf("s.ia = %d\n", s.ia);

    return 0;
}
