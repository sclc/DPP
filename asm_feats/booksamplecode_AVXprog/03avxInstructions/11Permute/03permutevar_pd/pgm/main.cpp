//==========================================================================
// _mm256_permutevar_pd、_mm_permutevar_pd
//     float64 値を 256 ビットまたは 128 ビットのデスティネーション・
//     ベクトルに並べ替えます。対応する AVX 命令は VPERMILPD です。
//
// C:\>permutevar_pd
// da:   1.0    2.0    3.0    4.0
// dc:   2.0    1.0    3.0    3.0
//
// fa:   1.0    2.0
// fc:   2.0    1.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    //_mm256_permutevar_pd
    __m256d da = _mm256_setr_pd(1,2,3,4);
    __m256i ds = _mm256_set_epi32(0,0,0,0,0,0,0,0x02);

    printf("da: ");
    for(int i=0; i<sizeof(da)/sizeof(da.m256d_f64[0]); i++)
        printf("%5.1f  ", da.m256d_f64[i]);
    printf("\n");

    __m256d dc = _mm256_permutevar_pd(da, ds);

    printf("dc: ");
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256d_f64[0]); i++)
        printf("%5.1f  ", dc.m256d_f64[i]);
    printf("\n\n");



    //_mm_permutevar_pd
    __m128d fa = _mm_setr_pd(1, 2);
    __m128i fs = _mm_set_epi32(0,0,0,0x03);

    printf("fa: ");
    for(int i=0; i<sizeof(fa)/sizeof(fa.m128d_f64[0]); i++)
        printf("%5.1f  ", fa.m128d_f64[i]);
    printf("\n");

    __m128d fc = _mm_permutevar_pd(fa, fs);

    printf("fc: ");
    for(int i=0; i<sizeof(fc)/sizeof(fc.m128d_f64[0]); i++)
        printf("%5.1f  ", fc.m128d_f64[i]);
    printf("\n");

    return 0;
}
