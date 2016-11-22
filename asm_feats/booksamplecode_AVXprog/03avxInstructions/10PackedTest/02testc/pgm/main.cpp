//==========================================================================
// _mm256_testc_si256
//     2 つの整数ベクトルのパックド・ビット･テストを実行して、CF フラグ
//     を設定します。対応する AVX 命令は VPTEST です。
//
// IF (SRC[255:0] BITWISE AND NOT DEST[255:0] == 0) THEN CF ← 1;
//     ELSE CF ← 0;
//
// C:\>testc
// 0
// 1
//
// ~a & b = ~(0x59) & 0xA6 = 0xA6 & 0xA6
//
//         0xA6 = 1010 0110b
//         0xA6 = 1010 0110b
//                 &
//                1010 0110b = 0xA6
//
// ~a & b = ~(0x59) & 0x00 = 0xA6 & 0x00
//
//         0xA6 = 1010 0110b
//         0x00 = 0000 0000b
//                 &
//                0000 0000b = 0x00
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256i y0 = _mm256_set_epi32(0x59595959,0x59595959,0x59595959,
            0x59595959,0x59595959,0x59595959,0x59595959,0x59595959);
    __m256i y1 = _mm256_set_epi32(0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,
            0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6,0xA6A6A6A6);

    int r = _mm256_testc_si256(y0, y1);
    printf("%d\n", r);


    y1 = _mm256_setzero_si256();
    r = _mm256_testc_si256(y0, y1);
    printf("%d\n", r);

    return 0;
}
