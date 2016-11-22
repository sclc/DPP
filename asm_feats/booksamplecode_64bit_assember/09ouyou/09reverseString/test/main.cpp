#include <stdio.h>

extern "C" void asmCode(char *source, char *destination);

int
main(void)
{
    const int length = 1024;
    char src[length] = "This is a pen.", dst[length];

    asmCode(src, dst);

    printf("%s\n%s\n", src, dst);

    return 0;
}
