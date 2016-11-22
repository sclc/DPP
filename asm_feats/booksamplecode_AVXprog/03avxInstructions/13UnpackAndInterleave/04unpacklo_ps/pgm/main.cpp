//==========================================================================
// _mm256_unpacklo_ps
//     下位のパックド単精度浮動小数点値をアンパックして、インターリーブ
//     します。対応する AVX 命令は VUNPCKHPS です。
//
// C:\>unpacklo_ps
// a:   1.0    2.0    3.0    4.0    5.0    6.0    7.0    8.0
// b:  11.0   12.0   13.0   14.0   15.0   16.0   17.0   18.0
//
// c:   1.0   11.0    2.0   12.0    5.0   15.0    6.0   16.0
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
    __m256 b = _mm256_setr_ps(11,12,13,14,15,16,17,18);

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256_f32[0]); i++)
        printf("%5.1f  ", a.m256_f32[i]);
    printf("\n");
    printf("b: ");
    for(int i=0; i<sizeof(b)/sizeof(b.m256_f32[0]); i++)
        printf("%5.1f  ", b.m256_f32[i]);
    printf("\n\n");


    __m256 c = _mm256_unpacklo_ps(a, b);

    printf("c: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256_f32[0]); i++)
        printf("%5.1f  ", c.m256_f32[i]);
    printf("\n");

    return 0;
}
