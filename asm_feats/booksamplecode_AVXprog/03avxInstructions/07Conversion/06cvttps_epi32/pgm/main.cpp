//==========================================================================
// _mm256_cvttps_epi32
//     パックド float32 値を、端数を切り捨てた 32 ビットの拡張整数値に
//     変換します。対応する AVX 命令は VCVTTPS2DQ です。
//
// C:\>cvttps_epi32
// 1 2 3 4 5 6 7 8
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256 fa = _mm256_setr_ps(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f);
    __m256i b = _mm256_setr_epi32(11, 12, 13, 14, 15, 16, 17, 18);

    b = _mm256_cvttps_epi32(fa);

    for (int i = 0; i < sizeof(b) / sizeof(b.m256i_i32[0]); i++)
        printf("%d ", b.m256i_i32[i]);

    return 0;
}
