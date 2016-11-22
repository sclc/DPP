//==========================================================================
// _mm256_testz_ps、_mm_testz_ps
//     2 つの 256 ビットまたは 128 ビットの float32 ベクトルの
//     パックド・ビット･テストを実行して、ZF フラグを設定します。
//     対応する AVX 命令は VTESTPS です。
//
// (VTESTPS (VEX.256 encoded version))
// TEMP[255:0] ← SRC[255:0] AND DEST[255:0]
// IF (TEMP[31] = TEMP[63] = TEMP[95] = TEMP[127]=
//                         TEMP[160] =TEMP[191] = TEMP[224] =TEMP[255] = 0)
//     THEN ZF ← 1;
//     ELSE ZF ← 0;
//
// C:\>testz_ps
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
    __m256 y0 = _mm256_setr_ps(1,2,3,4,5,6,7,8);
    __m256 y1 = _mm256_setr_ps(1,2,3,4,5,6,7,8);

    int r = _mm256_testz_ps(y0, y1);
    printf("%d\n", r);

    y0 = _mm256_setr_ps(-11,-12,-13,-14,-15,-16,-17,-18);
    y1 = _mm256_setr_ps(-21,-22,-23,-24,-25,-26,-27,-28);
    r = _mm256_testz_ps(y0, y1);
    printf("%d\n", r);


    __m128 y2 = _mm_setr_ps(1,2,3,4);
    __m128 y3 = _mm_setr_ps(1,2,3,4);

    r = _mm_testz_ps(y2, y3);
    printf("%d\n", r);

    y2 = _mm_setr_ps( -0.11f, -0.12f, -0.13f, -0.14f);
    y3 = _mm_setr_ps(-0.001f,-0.002f,-0.003f,-0.004f);
    r = _mm_testz_ps(y2, y3);
    printf("%d\n", r);

    return 0;
}
