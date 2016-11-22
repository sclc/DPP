#include <stdio.h>

extern "C" int jump(void);

int
main(void)
{
    int a = jump();
    printf("a=%d\n", a);

    return 0;
}
