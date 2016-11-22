//==========================================================================
// _mm256_min_pd
//     float64 ベクトルの最小値を特定します。対応する AVX 命令は VMINPD
//     です。
//
// C:\>minpd
// 1 6 3 8
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256d a = _mm256_setr_pd(1, 12, 3, 14);
    __m256d b = _mm256_setr_pd(5,  6, 7,  8);

    __m256d c = _mm256_min_pd(a, b);

    for(int i=0; i<sizeof(c)/sizeof(c.m256d_f64[0]);i++)
        printf("%.0f ", c.m256d_f64[i]);
    printf("\n");

    return 0;
}
