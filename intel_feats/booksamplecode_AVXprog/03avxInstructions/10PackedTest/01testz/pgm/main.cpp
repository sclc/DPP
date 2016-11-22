//==========================================================================
// _mm256_testz_si256
//     2 つの整数ベクトルのパックド・ビット･テストを実行して、ZF フラグ
//     を設定します。対応する AVX 命令は VPTEST です。
//
// IF (SRC[255:0] BITWISE AND DEST[255:0] == 0) THEN ZF ← 1;
//         ELSE ZF ← 0;
//
// C:\>testz
// 0
// 1
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256i y0 = _mm256_set_epi32(1,2,3,4,5,6,7,8);
    __m256i y1 = _mm256_set_epi32(1,2,3,4,5,6,7,8);

    int r = _mm256_testz_si256(y0, y1);
    printf("%d\n", r);


    y1 = _mm256_setzero_si256();
    r = _mm256_testz_si256(y0, y1);
    printf("%d\n", r);

    return 0;
}
