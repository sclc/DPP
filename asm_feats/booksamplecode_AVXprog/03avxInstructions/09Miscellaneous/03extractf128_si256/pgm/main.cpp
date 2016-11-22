//==========================================================================
// _mm256_extractf128_si256
//     128 ビットのスカラー整数値を抽出します。対応する AVX 命令は
//     VEXTRACTF128 です。
//
// C:\>extractf128_si256
// a: 1  2  3  4  5  6  7  8
//
// offset=0:
// fc: 1  2  3  4
//
// offset=1:
// fc: 5  6  7  8
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256i a=_mm256_setr_epi32(1,2,3,4,5,6,7,8);
    __m128i c;

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256i_i32[0]); i++)
        printf("%d  ", a.m256i_i32[i]);
    printf("\n");


    c = _mm256_extractf128_si256(a, 0);

    printf("\noffset=0:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m128i_i32[0]); i++)
        printf("%d  ", c.m128i_i32[i]);
    printf("\n");


    c = _mm256_extractf128_si256(a, 1);

    printf("\noffset=1:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m128i_i32[0]); i++)
        printf("%d  ", c.m128i_i32[i]);
    printf("\n");

    return 0;
}
