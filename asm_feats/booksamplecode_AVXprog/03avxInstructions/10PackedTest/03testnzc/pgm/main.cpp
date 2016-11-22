//==========================================================================
// _mm256_testnzc_si256
//     2 つの整数ベクトルのパックド・ビット･テストを実行して、
//     ZF フラグと CF フラグを設定します。対応する AVX 命令は
//     VPTEST です。
//
// C:\>testnzc
// 1
// 0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256i y0 = _mm256_set_epi32(-1,-2,-3,-4,-5,-6,-7,-8);
    __m256i y1 = _mm256_set_epi32(1,2,3,4,5,6,7,8);

    int r = _mm256_testnzc_si256(y0, y1);
    printf("%d\n", r);


    y0 = _mm256_set_epi32(1,2,3,4,5,6,7,8);
    r = _mm256_testnzc_si256(y0, y1);
    printf("%d\n", r);

    return 0;
}
