//==========================================================================
// _mm256_permute2f128_ps
//     フィールドを含む 128 ビットの単精度浮動小数点を 256 ビットの
//     デスティネーション・ベクトルに並べ替えます。対応する AVX 命令は
//      VPERM2F128 です。
//
// C:\>permute2f128_ps
// da:   1.0    2.0    3.0    4.0    5.0    6.0    7.0    8.0
// db:  11.0   12.0   13.0   14.0   15.0   16.0   17.0   18.0
//
// dc:  11.0   12.0   13.0   14.0    1.0    2.0    3.0    4.0
// dc:   0.0    0.0    0.0    0.0    1.0    2.0    3.0    4.0
// dc:   5.0    6.0    7.0    8.0   11.0   12.0   13.0   14.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

void printDc(char* prompt, __m256 dc);

int
main(void)
{
    __m256  da = _mm256_setr_ps(1,2,3,4,5,6,7,8);
    __m256  db = _mm256_setr_ps(11,12,13,14,15,16,17,18);
    __m256  dc;

    printDc("da: ", da);
    printDc("db: ", db);
    printf("\n");


    dc = _mm256_permute2f128_ps(da, db, 0x02);
    printDc("dc: ", dc);

    dc = _mm256_permute2f128_ps(da, db, 0x02|0x08);
    printDc("dc: ", dc);

    dc = _mm256_permute2f128_ps(da, db, 0x21);
    printDc("dc: ", dc);

    return 0;
}

void
printDc(char* prompt, __m256 dc)
{
    printf("%s", prompt);
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256_f32[0]); i++)
        printf("%5.1f  ", dc.m256_f32[i]);
    printf("\n");
}
