//==========================================================================
// _mm256_blend_pd
//     float64 ベクトルの条件付き混合または条件付きマージを実行します。
//     対応する AVX 命令は VBLENDPD です。
//
// _mm256_blend_ps
//     float32 ベクトルの条件付き混合または条件付きマージを実行します。
//     対応する AVX 命令は VBLENDPS です。
//
// C:\>blend
// 5 2 7 4
// 1 12 3 14 5 16 7 18
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256d da = _mm256_setr_pd(1, 2, 3, 4);
    __m256d db = _mm256_setr_pd(5, 6, 7, 8);

    //_mm256_blend_pd
    __m256d pd = _mm256_blend_pd(da, db, 0x05);

    for(int i=0; i<sizeof(pd)/sizeof(pd.m256d_f64[0]);i++)
        printf("%.0f ", pd.m256d_f64[i]);
    printf("\n");



    __m256 fa = _mm256_setr_ps(1, 2, 3, 4, 5, 6, 7, 8);
    __m256 fb = _mm256_setr_ps(11, 12, 13, 14, 15, 16, 17, 18);

    //_mm256_blend_ps
    __m256 fd = _mm256_blend_ps(fa, fb, 0xAA);

    for(int i=0; i<sizeof(fd)/sizeof(fd.m256_f32[0]);i++)
        printf("%.0f ", fd.m256_f32[i]);

    return 0;
}
