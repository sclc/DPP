//==========================================================================
// _mm256_cvtps_pd
//     パックド float32 値をパックド float64 値に変換します。対応する
//     AVX 命令は VCVTPS2PD です。
//
// C:\>cvtps_pd
// 1.0 2.0 3.0 4.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m128  fa = _mm_setr_ps(1, 2, 3, 4);
    __m256d db = _mm256_setr_pd(11, 12, 13, 14);

    db = _mm256_cvtps_pd(fa);

    for(int i=0; i<sizeof(db)/sizeof(db.m256d_f64[0]);i++)
        printf("%.1f ", db.m256d_f64[i]);

    return 0;
}
