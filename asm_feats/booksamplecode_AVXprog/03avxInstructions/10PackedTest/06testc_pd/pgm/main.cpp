//==========================================================================
// _mm256_testc_pd、_mm_testc_pd
//     2 つの 256 ビットまたは 128 ビットの float64 ベクトルの
//     パックド・ビット･テストを実行して、CF フラグを設定します。
//     対応する AVX 命令は VTESTPD です。
//
// TEMP[255:0] ← SRC[255:0] AND NOT DEST[255:0]
// IF (TEMP[63] = TEMP[127] = TEMP[191] = TEMP[255] = 0)
//     THEN CF ← 1;
//     ELSE CF ← 0;
//
// C:\>testc_pd
// 0
// 1
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
    __m256i i0 = _mm256_set_epi32(0x59595959,0x59595959,0x59595959,
            0x59595959,0x59595959,0x59595959,0x59595959,0x59595959);
    __m256i i1 = _mm256_set_epi32(0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,
            0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6);

    __m256d *y0 = (__m256d*)&i0;
    __m256d *y1 = (__m256d*)&i1;

    int r = _mm256_testc_pd(*y0, *y1);
    printf("%d\n", r);

    i1 = _mm256_setzero_si256();
    r = _mm256_testc_pd(*y0, *y1);
    printf("%d\n", r);


    __m128i i2 = _mm_set_epi32(0x59595959,0x59595959,0x59595959,0x59595959);
    __m128i i3 = _mm_set_epi32(0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6);

    __m128d *y2 = (__m128d*)&i2;
    __m128d *y3 = (__m128d*)&i3;

    r = _mm_testc_pd(*y2, *y3);
    printf("%d\n", r);

    i3 = _mm_set_epi32(1,2,3,4);
    r = _mm_testc_pd(*y2, *y3);
    printf("%d\n", r);

    return 0;
}
