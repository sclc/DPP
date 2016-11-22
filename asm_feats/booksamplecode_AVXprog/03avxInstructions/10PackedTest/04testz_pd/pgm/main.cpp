//==========================================================================
// _mm256_testz_pd、_mm_testz_pd
//     2 つの 256 ビットまたは 128 ビットの float64 ベクトルの
//     パックド・ビット･テストを実行して、ZF フラグを設定します。
//     対応する AVX 命令は VTESTPD です。
//
// (VTESTPD)
// TEMP[255:0] ← SRC[255:0] AND DEST[255:0]
// IF (TEMP[63] = TEMP[127] = TEMP[191] = TEMP[255] = 0)
//     THEN ZF ← 1;
//     ELSE ZF ← 0;
//
// (VTESTPS (VEX.256 encoded version))
// TEMP[255:0] ← SRC[255:0] AND DEST[255:0]
// IF (TEMP[31] = TEMP[63] = TEMP[95] = TEMP[127]=
//                         TEMP[160] =TEMP[191] = TEMP[224] =TEMP[255] = 0)
//     THEN ZF ← 1;
//     ELSE ZF ← 0;
//
// C:\>testz_pd
// 1
// 0
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
    __m128d y2 = _mm_setr_pd(1,2);
    __m128d y3 = _mm_setr_pd(1,2);

    int r = _mm_testz_pd(y2, y3);
    printf("%d\n", r);

    y2 = _mm_setr_pd(-1,-2);
    y3 = _mm_setr_pd(-1,-2);
    r = _mm_testz_pd(y2, y3);
    printf("%d\n", r);


    __m256d y0 = _mm256_setr_pd(1,2,3,4);
    __m256d y1 = _mm256_setr_pd(1,2,3,4);

    r = _mm256_testz_pd(y0, y1);
    printf("%d\n", r);

    //y1 = _mm256_setr_pd(11,2,3,4);
    y0 = _mm256_setr_pd(-1,-2,-3,-4);
    y1 = _mm256_setr_pd(-1,-2,-3,-4);
    r = _mm256_testz_pd(y0, y1);
    printf("%d\n", r);

    return 0;
}
