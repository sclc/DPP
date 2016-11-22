//==========================================================================
// _mm256_blendv_pd
//     float64 ベクトルの条件付き混合または条件付きマージを実行します。
//     対応する AVX 命令は VBLENDVPD です。
//
// _mm256_blendv_ps
//     float32 ベクトルの条件付き混合または条件付きマージを実行します。
//     対応する AVX 命令は VBLENDVPS です。
//
// C:\>blendv
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
    __m256i dmask = _mm256_set_epi32(0, 0, 1<<31, 0, 0, 0, 1<<31, 0);
                                    //二つをペアで使う

    //_mm256_blendv_pd
    __m256d pd = _mm256_blendv_pd(da, db, _mm256_castsi256_pd(dmask));

    for(int i=0; i<sizeof(pd)/sizeof(pd.m256d_f64[0]);i++)
        printf("%.0f ", pd.m256d_f64[i]);
    printf("\n");



    __m256 fa = _mm256_setr_ps(1, 2, 3, 4, 5, 6, 7, 8);
    __m256 fb = _mm256_setr_ps(11, 12, 13, 14, 15, 16, 17, 18);
    __m256i fmask = _mm256_set_epi32(1<<31, 0, 1<<31, 0, 1<<31, 0, 1<<31, 0 );

    //_mm256_blendv_ps
    __m256 fd = _mm256_blendv_ps(fa, fb, _mm256_castsi256_ps(fmask));

    for(int i=0; i<sizeof(fd)/sizeof(fd.m256_f32[0]);i++)
        printf("%.0f ", fd.m256_f32[i]);

    return 0;
}
