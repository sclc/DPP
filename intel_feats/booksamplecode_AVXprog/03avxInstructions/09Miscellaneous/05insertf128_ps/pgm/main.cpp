//==========================================================================
// _mm256_insertf128_ps
//     パックド float32 値の 128 ビットを挿入します。対応する AVX 命令
//     は VINSERTF128 です。
//
// C:\>insertf128_ps
// a:   1.0    2.0    3.0    4.0    5.0    6.0    7.0    8.0
// b:  11.0   12.0   13.0   14.0
//
// offset=0:
// fc:  11.0   12.0   13.0   14.0    5.0    6.0    7.0    8.0
//
// offset=1:
// fc:   1.0    2.0    3.0    4.0   11.0   12.0   13.0   14.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256 a = _mm256_setr_ps(1,2,3,4,5,6,7,8);
    __m128 b = _mm_setr_ps(11,12,13,14);
    __m256 c;

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256_f32[0]); i++)
        printf("%5.1f  ", a.m256_f32[i]);
    printf("\n");
    printf("b: ");
    for(int i=0; i<sizeof(b)/sizeof(b.m128_f32[0]); i++)
        printf("%5.1f  ", b.m128_f32[i]);
    printf("\n");


    c = _mm256_setr_ps(21,22,23,24,25,26,27,28);
    c = _mm256_insertf128_ps(a, b, 0);

    printf("\noffset=0:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256_f32[0]); i++)
        printf("%5.1f  ", c.m256_f32[i]);
    printf("\n");


    c = _mm256_setr_ps(21,22,23,24,25,26,27,28);
    c = _mm256_insertf128_ps(a, b, 1);

    printf("\noffset=1:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256_f32[0]); i++)
        printf("%5.1f  ", c.m256_f32[i]);
    printf("\n");

    return 0;
}
