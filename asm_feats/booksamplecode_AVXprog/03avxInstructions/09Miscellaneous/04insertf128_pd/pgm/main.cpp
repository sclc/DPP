//==========================================================================
// _mm256_insertf128_pd
//     パックド float64 値の 128 ビットを挿入します。対応する AVX 命令は
//      VINSERTF128 です。
//
// C:\>insertf128_pd
// a:   1.0    2.0    3.0    4.0
// b:  11.0   12.0
//
// offset=0:
// fc:  11.0   12.0    3.0    4.0
//
// offset=1:
// fc:   1.0    2.0   11.0   12.0
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
    __m128d b = _mm_setr_pd(11,12);
    __m256d c;

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256d_f64[0]); i++)
        printf("%5.1f  ", a.m256d_f64[i]);
    printf("\n");
    printf("b: ");
    for(int i=0; i<sizeof(b)/sizeof(b.m128d_f64[0]); i++)
        printf("%5.1f  ", b.m128d_f64[i]);
    printf("\n");


    c = _mm256_setr_pd(11,12,13,14);
    c = _mm256_insertf128_pd(a, b, 0);

    printf("\noffset=0:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256d_f64[0]); i++)
        printf("%5.1f  ", c.m256d_f64[i]);
    printf("\n");

    c = _mm256_setr_pd(11,12,13,14);
    c = _mm256_insertf128_pd(a, b, 1);

    printf("\noffset=1:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256d_f64[0]); i++)
        printf("%5.1f  ", c.m256d_f64[i]);
    printf("\n");

    return 0;
}
