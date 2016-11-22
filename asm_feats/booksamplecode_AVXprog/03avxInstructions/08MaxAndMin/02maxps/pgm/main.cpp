//==========================================================================
// _mm256_max_ps
//     float32 ベクトルの最大値を特定します。対応する AVX 命令は VMAXPS
//     です。
//
// C:\>maxps
// 5 12 7 14 9 16 11 18
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256 a = _mm256_setr_ps(1, 12, 3, 14, 5,16, 7,18);
    __m256 b = _mm256_setr_ps(5,  6, 7,  8, 9,10,11,12);

    __m256 c = _mm256_max_ps(a, b);

    for(int i=0; i<sizeof(c)/sizeof(c.m256_f32[0]);i++)
        printf("%.0f ", c.m256_f32[i]);
    printf("\n");

    return 0;
}
