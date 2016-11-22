#include <stdio.h>

extern "C" double asmSample(double a, double b);

int
main(void)
{
    double a = asmSample(1.23456f, 11.22222f);
    printf("a = %.5f\n", a);

    return 0;
}
