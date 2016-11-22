//==========================================================================
//
// C:\>mul
// out[0]= 1.1
// out[1]= 4.4
// out[2]= 9.9
// out[3]=17.6
//
//  1.0,  2.0,  3.0,  4.0
//   *     *     *     *
//  1.1,  2.2,  3.3,  4.4
// ------------------------
//  1.1,  4.4,  9.9, 17.6
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    double out[4];

    __m256d a=_mm256_setr_pd(1.0, 2.0, 3.0, 4.0);
    __m256d b=_mm256_setr_pd(1.1, 2.2, 3.3, 4.4);

    __m256d dst = _mm256_mul_pd(a, b);

    _mm256_storeu_pd(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%4.1f\n", i, out[i]);

    return 0;
}
