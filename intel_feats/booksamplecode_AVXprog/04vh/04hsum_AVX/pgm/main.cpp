//==========================================================================
// _mm256_hadd_ps
//    水平加算します。ymm 8要素floatのsumを計算
//
// C:\>hsum_AVX
// out=37.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    float out;
    __m256 sum=_mm256_setr_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.1f, 6.2f, 7.3f, 8.4f);
                                                        // d0, d1, d2, d3, d4, d5, d6, d7

    sum = _mm256_hadd_ps(sum, sum);                     // d0+d1,       d2+d3,       d0+d1,       d2+d3,       d4+d5,       d6+d7        d4+d5,       d6+d7
    sum = _mm256_hadd_ps(sum, sum);                     // d0+d1+d2+d3, d0+d1+d2+d3, d0+d1+d2+d3, d0+d1+d2+d3, d4+d5+d6+d7, d4+d5+d6+d7, d4+d5+d6+d7, d4+d5+d6+d7

    __m128 m128sum0 = _mm256_extractf128_ps(sum, 0);    // d0+d1+d2+d3, d0+d1+d2+d3, d0+d1+d2+d3, d0+d1+d2+d3
    __m128 m128sum1 = _mm256_extractf128_ps(sum, 1);    // d4+d5+d6+d7, d4+d5+d6+d7, d4+d5+d6+d7, d4+d5+d6+d7

    m128sum0 = _mm_add_ss(m128sum0, m128sum1);          // m128sum0=(d0+d1+d2+d3)+(d4+d5+d6+d7);
    _mm_store_ss(&out, m128sum0);                       // out=m128sum0(LSFloat)

    printf("out=%4.1f\n", out);

    return 0;
}
