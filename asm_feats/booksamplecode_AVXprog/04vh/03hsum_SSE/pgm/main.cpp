//==========================================================================
// 水平演算、レジスタ4要素のみ
//
// C:\>hsum_SSE
// out=10.0
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
    __m128 sum=_mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f); // d0, d1, d2, d3

    sum = _mm_hadd_ps(sum, sum);        // d0+d1,       d2+d3,       d0+d1,       d2+d3
    sum = _mm_hadd_ps(sum, sum);        // d0+d1+d2+d3, d0+d1+d2+d3, d0+d1+d2+d3, d0+d1+d2+d3

    _mm_store_ss(&out, sum);            // out=d0+d1+d2+d3

    printf("out=%4.1f\n", out);

    return 0;
}
