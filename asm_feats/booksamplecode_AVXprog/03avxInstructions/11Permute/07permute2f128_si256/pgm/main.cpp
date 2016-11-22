//==========================================================================
// _mm256_permute2f128_si256
//     フィールドを含む 128 ビットの整数を 256 ビットのデスティネーション・
//     ベクトルに並べ替えます。対応する AVX 命令は VPERM2F128 です。
//
// C:\>permute2f128_si256
// da:   1    2    3    4    5    6    7    8
// db:  11   12   13   14   15   16   17   18
//
// dc:  11   12   13   14    1    2    3    4
// dc:   0    0    0    0    1    2    3    4
// dc:   5    6    7    8   11   12   13   14
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

void printDc(char* prompt, __m256i dc);

int
main(void)
{
    __m256i  da = _mm256_setr_epi32(1,2,3,4,5,6,7,8);
    __m256i  db = _mm256_setr_epi32(11,12,13,14,15,16,17,18);
    __m256i  dc;

    printDc("da: ", da);
    printDc("db: ", db);
    printf("\n");

    dc = _mm256_permute2f128_si256(da, db, 0x02);
    printDc("dc: ", dc);

    dc = _mm256_permute2f128_si256(da, db, 0x02|0x08);
    printDc("dc: ", dc);

    dc = _mm256_permute2f128_si256(da, db, 0x21);
    printDc("dc: ", dc);

    return 0;
}

void
printDc(char* prompt, __m256i dc)
{
    printf("%s", prompt);
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256i_i32[0]); i++)
        printf("%3d  ", dc.m256i_i32[i]);
    printf("\n");
}
