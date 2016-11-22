//==========================================================================
// _mm256_cvtpd_ps
//     パックド float64 値をパックド float32 値に変換します。対応する
//     AVX 命令は VCVTPD2PS です。
//
// C:\>cvtpd_ps
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
    __m256d da = _mm256_setr_pd(1, 2, 3, 4);
    __m128  fb = _mm_setr_ps(11, 12, 13, 14);

    fb = _mm256_cvtpd_ps(da);

    for(int i=0; i<sizeof(fb)/sizeof(fb.m128_f32[0]);i++)
        printf("%.1f ", fb.m128_f32[i]);

    return 0;
}
