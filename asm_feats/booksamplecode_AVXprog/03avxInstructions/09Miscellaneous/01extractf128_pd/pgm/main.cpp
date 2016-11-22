//==========================================================================
// _mm256_extractf128_pd
//     128 ビットのパックド float64 値を抽出します。対応する AVX 命令は
//      VEXTRACTF128 です。
//
// C:\>extractf128_pd
// a:   1.0    2.0    3.0    4.0
//
// offset=0:
// fc:   1.0    2.0
//
// offset=1:
// fc:   3.0    4.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256d a = _mm256_setr_pd(1,2,3,4);
    __m128d c;

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256d_f64[0]); i++)
        printf("%5.1f  ", a.m256d_f64[i]);
    printf("\n");


    c = _mm256_extractf128_pd(a, 0);

    printf("\noffset=0:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m128d_f64[0]); i++)
        printf("%5.1f  ", c.m128d_f64[i]);
    printf("\n");


    c = _mm256_extractf128_pd(a, 1);

    printf("\noffset=1:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m128d_f64[0]); i++)
        printf("%5.1f  ", c.m128d_f64[i]);
    printf("\n");

    return 0;
}
