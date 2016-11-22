//==========================================================================
// _mm256_insertf128_si256
//     パックドスカラー整数値の 128 ビットを挿入します。対応する AVX 命令
//     は VINSERTF128 です。
//
// C:\>insertf128_si256
// a: 1  2  3  4  5  6  7  8
// b: 11  12  13  14
//
// offset=0:
// fc: 11  12  13  14  5  6  7  8
//
// offset=1:
// fc: 1  2  3  4  11  12  13  14
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256i a = _mm256_setr_epi32(1,2,3,4,5,6,7,8);
    __m128i b =_mm_setr_epi32(11,12,13,14);
    __m256i c;

    printf("a: ");
    for(int i=0; i<sizeof(a)/sizeof(a.m256i_i32[0]); i++)
        printf("%d  ", a.m256i_i32[i]);
    printf("\n");
    printf("b: ");
    for(int i=0; i<sizeof(b)/sizeof(b.m128i_i32[0]); i++)
        printf("%d  ", b.m128i_i32[i]);
    printf("\n");


    c = _mm256_setr_epi32(21,22,23,24,25,26,27,28);
    c = _mm256_insertf128_si256(a, b, 0);

    printf("\noffset=0:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i32[0]); i++)
        printf("%d  ", c.m256i_i32[i]);
    printf("\n");


    c = _mm256_setr_epi32(21,22,23,24,25,26,27,28);
    c = _mm256_insertf128_si256(a, b, 1);

    printf("\noffset=1:\nfc: ");
    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i32[0]); i++)
        printf("%d  ", c.m256i_i32[i]);
    printf("\n");

    return 0;
}
