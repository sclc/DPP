#include <stdio.h>

extern "C" {
    float addfunc(float a, float b);
    float subfunc(float a, float b);
}

int
main(void)
{
    float a, b = (float)1.11111, c = (float)2.22222;

    a = addfunc(b, c);
    printf("%.5f + %.5f = %.5f\n", b, c, a);

    a = subfunc(b, c);
    printf("%.5f - %.5f = %.5f\n", b, c, a);

    return 0;
}
