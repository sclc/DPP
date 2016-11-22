//==========================================================================
// _mm256_round_pd
//     丸めモードに応じて、倍精度浮動小数点値を最も近い整数値に丸めます。
//     対応する AVX 命令は VROUNDPD です。
//
// _mm256_round_ps
//     丸めモードに応じて、単精度浮動小数点値を最も近い整数値に丸めます。
//     対応する AVX 命令は VROUNDPS です。
//
// C:\>round
//     in =  1.11  -2.55   3.66  -4.11
// _mm256_ceil_pd
//     out=  2.00  -2.00   4.00  -4.00
// _mm256_floor_pd
//     out=  1.00  -3.00   3.00  -5.00
//
//
//     in =  1.11  -2.55   3.66  -4.11   5.11  -6.66   7.77  -8.11
// _mm256_ceil_ps
//     out=  2.00  -2.00   4.00  -4.00   6.00  -6.00   8.00  -8.00
// _mm256_floor_ps
//     out=  1.00  -3.00   3.00  -5.00   5.00  -7.00   7.00  -9.00
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>


int
main(void)
{
    //_mm256_round_pd
    __m256d da = _mm256_setr_pd(1.11,-2.55,3.66,-4.11);

    printf("    in = ");
    for(int i=0; i<sizeof(da)/sizeof(da.m256d_f64[0]); i++)
        printf("%5.2f  ", da.m256d_f64[i]);
    printf("\n");

    //__m256d db = _mm256_ceil_pd(da);
    __m256d db = _mm256_round_pd(da, 0x0A);

    printf("_mm256_ceil_pd\n    out= ");
    for(int i=0; i<sizeof(db)/sizeof(db.m256d_f64[0]); i++)
        printf("%5.2f  ", db.m256d_f64[i]);

    //db = _mm256_floor_pd(da);
    db = _mm256_round_pd(da, 0x09);

    printf("\n_mm256_floor_pd\n    out= ");
    for(int i=0; i<sizeof(db)/sizeof(db.m256d_f64[0]); i++)
        printf("%5.2f  ", db.m256d_f64[i]);
    printf("\n");




    //_mm256_round_ps
    __m256 fa = _mm256_setr_ps(1.11f,-2.55f,3.66f,-4.11f,5.11f,-6.66f,7.77f,-8.11f);

    printf("\n\n    in = ");
    for(int i=0; i<sizeof(fa)/sizeof(fa.m256_f32[0]); i++)
        printf("%5.2f  ", fa.m256_f32[i]);
    printf("\n");

    //__m256 fb = _mm256_ceil_ps(fa);
    __m256 fb = _mm256_round_ps(fa, 0x0A);

    printf("_mm256_ceil_ps\n    out= ");
    for(int i=0; i<sizeof(fb)/sizeof(fb.m256_f32[0]); i++)
        printf("%5.2f  ", fb.m256_f32[i]);

    //fb = _mm256_floor_ps(fa);
    fb = _mm256_round_ps(fa, 0x09);

    printf("\n_mm256_floor_ps\n    out= ");
    for(int i=0; i<sizeof(fb)/sizeof(fb.m256_f32[0]); i++)
        printf("%5.2f  ", fb.m256_f32[i]);
    printf("\n");

    return 0;
}
