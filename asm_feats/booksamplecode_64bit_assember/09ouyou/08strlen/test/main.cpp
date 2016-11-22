#include <stdio.h>

extern "C" int asmCode(char *str);

int
main(void)
{
    char src[] = "This is a pen!";

    int length=asmCode(src);
    printf("length=%d\n", length);

    return 0;
}
