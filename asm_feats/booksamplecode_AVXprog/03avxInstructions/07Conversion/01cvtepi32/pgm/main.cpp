//==========================================================================
// _mm256_cvtepi32_pd
//     32 ビットの拡張パックド整数値をパックド倍精度浮動小数点値に
//     型キャストします。対応する AVX 命令は VCVTDQ2PD です。
//
// _mm256_cvtepi32_ps
//     32 ビットの拡張パックド整数値をパックド単精度浮動小数点値に
//     型キャストします。対応する AVX 命令は VCVTDQ2PS です。
//
// C:\>cvtepi32
// 1.0 2.0 3.0 4.0
// 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    //_mm256_cvtepi32_pd
    __m128i fa = _mm_setr_epi32(1, 2, 3, 4);

    __m256d db = _mm256_cvtepi32_pd(fa);

    for(int i=0; i<sizeof(db)/sizeof(db.m256d_f64[0]);i++)
        printf("%.1f ", db.m256d_f64[i]);
    printf("\n");



    //_mm256_cvtepi32_ps
    __m256i da = _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8);

    __m256 fb = _mm256_cvtepi32_ps(da);

    for(int i=0; i<sizeof(fb)/sizeof(fb.m256_f32[0]);i++)
        printf("%.1f ", fb.m256_f32[i]);
    printf("\n");

    return 0;
}
