#include <stdio.h>

extern "C" {
    float mulfunc(float a, float b);
    float divfunc(float a, float b);
}

int
main(void)
{
    float a, b = (float)1.11111, c = (float)2.22222;

    a = mulfunc(b, c);
    printf("%.5f * %.5f = %.5f\n", b, c, a);

    a = divfunc(b, c);
    printf("%.5f / %.5f = %.5f\n", b, c, a);

    return 0;
}
