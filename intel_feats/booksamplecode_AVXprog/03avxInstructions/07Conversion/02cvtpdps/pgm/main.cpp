//==========================================================================
// _mm256_cvtpd_epi32
//     パックド倍精度浮動小数点値を 32 ビットの拡張整数値に変換します。
//     対応する AVX 命令は VCVTPD2DQ です。
//
// _m256_cvtps_epi32
//     パックド単精度浮動小数点値を 32 ビットの拡張整数値に変換します。
//     対応する AVX 命令は VCVTPS2DQ です。
//
// C:\>cvtpdps
// 1 2 3 4
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
    //_mm256_cvtpd_epi32
    __m256d da = _mm256_setr_pd(1, 2, 3, 4);

    __m128i b = _mm256_cvtpd_epi32(da);

    for(int i=0; i<sizeof(b)/sizeof(b.m128i_i32[0]);i++)
        printf("%d ", b.m128i_i32[i]);
    printf("\n");



    //_m256_cvtps_epi32
    __m256 fa = _mm256_setr_ps(1, 2, 3, 4, 5, 6, 7, 8);

    __m256i c = _mm256_cvtps_epi32(fa);

    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i32[0]);i++)
        printf("%d ", c.m256i_i32[i]);
    printf("\n");

    return 0;
}
