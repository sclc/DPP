//==========================================================================
// _mm256_cvttp_epi32
//     パックド float64 値を、端数を切り捨てた 32 ビットの拡張整数値に
//     変換します。対応する AVX 命令は VCVTTPD2DQ です。
//
// C:\>cvttpd_epi32
// 1 2 3 4
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256d da = _mm256_setr_pd(1.1f, 2.4f, 3.6f, 4.8f);
    __m128i b = _mm_setr_epi32(11, 12, 13, 14);

    b = _mm256_cvttpd_epi32(da);

    for (int i = 0; i < sizeof(b) / sizeof(b.m128i_i32[0]); i++)
        printf("%d ", b.m128i_i32[i]);

    return 0;
}
