#include <stdio.h>

extern "C" {
    double addfunc(double a, double b);
    double subfunc(double a, double b);
}

int
main(void)
{
    double a, b = 3.33333f, c = 2.22222f;

    a = addfunc(b, c);
    printf("%.5f + %.5f = %.5f\n", b, c, a);

    a = subfunc(b, c);
    printf("%.5f - %.5f = %.5f\n", b, c, a);

    return 0;
}
