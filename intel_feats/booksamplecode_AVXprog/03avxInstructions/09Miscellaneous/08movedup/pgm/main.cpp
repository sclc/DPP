//==========================================================================
// _mm256_movedup_pd
//     インデックスが偶数の倍精度浮動小数点値を複製します。対応する
//      AVX 命令は VMOVDDUP です。
//
// _mm256_movehdup_ps
//     インデックスが奇数の単精度浮動小数点値を複製します。対応する
//      AVX 命令は VMOVSHDUP です。
//
// _mm256_moveldup_ps
//     インデックスが偶数の単精度浮動小数点値を複製します。対応する
//      AVX 命令は VMOVSLDUP です。
//
// C:\>movedup
// _mm256_movedup_pd
//     in = 1 2 3 4
//     out= 1 1 3 3
//
// _mm256_movehdup_ps
//     in = 1 2 3 4 5 6 7 8
//     out= 2 2 4 4 6 6 8 8
//
// _mm256_moveldup_ps
//     in = 1 2 3 4 5 6 7 8
//     out= 1 1 3 3 5 5 7 7
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    //_mm256_movedup_pd
    __m256d da = _mm256_setr_pd(1,2,3,4);

    __m256d db = _mm256_movedup_pd(da);

    printf("_mm256_movedup_pd\n    in = ");
    for(int i=0; i<sizeof(da)/sizeof(da.m256d_f64[0]);i++)
        printf("%.0f ", da.m256d_f64[i]);
    printf("\n    out= ");
    for(int i=0; i<sizeof(db)/sizeof(db.m256d_f64[0]);i++)
        printf("%.0f ", db.m256d_f64[i]);
    printf("\n\n");


    //_mm256_movehdup_ps
    __m256 fa = _mm256_setr_ps(1,2,3,4,5,6,7,8);

    __m256 fb = _mm256_movehdup_ps(fa);

    printf("_mm256_movehdup_ps\n    in = ");
    for(int i=0; i<sizeof(fa)/sizeof(fa.m256_f32[0]);i++)
        printf("%.0f ", fa.m256_f32[i]);
    printf("\n    out= ");
    for(int i=0; i<sizeof(fb)/sizeof(fb.m256_f32[0]);i++)
        printf("%.0f ", fb.m256_f32[i]);
    printf("\n\n");


    //_mm256_moveldup_ps
    fb = _mm256_moveldup_ps(fa);

    printf("_mm256_moveldup_ps\n    in = ");
    for(int i=0; i<sizeof(fa)/sizeof(fa.m256_f32[0]);i++)
        printf("%.0f ", fa.m256_f32[i]);
    printf("\n    out= ");
    for(int i=0; i<sizeof(fb)/sizeof(fb.m256_f32[0]);i++)
        printf("%.0f ", fb.m256_f32[i]);
    printf("\n\n");

    return 0;
}
