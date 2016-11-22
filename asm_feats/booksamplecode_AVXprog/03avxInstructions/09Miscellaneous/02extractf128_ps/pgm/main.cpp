//==========================================================================
// _mm256_extractf128_ps
//     128 ビットの float32 値を抽出します。対応する AVX 命令は
//     VEXTRACTF128 です。
//
// C:\>extractf128_ps
// a:   1.0    2.0    3.0    4.0    5.0    6.0    7.0    8.0
//
// offset=0:
// c:   1.0    2.0    3.0    4.0
//
// offset=1:
// c:   5.0    6.0    7.0    8.0
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
    __m128 c;

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256_f32[0]); i++)
        printf("%5.1f  ", a.m256_f32[i]);
    printf("\n");


    c = _mm256_extractf128_ps(a, 0);

    printf("\noffset=0:\nc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m128_f32[0]); i++)
        printf("%5.1f  ", c.m128_f32[i]);
    printf("\n");


    c = _mm256_extractf128_ps(a, 1);

    printf("\noffset=1:\nc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m128_f32[0]); i++)
        printf("%5.1f  ", c.m128_f32[i]);
    printf("\n");

    return 0;
}
