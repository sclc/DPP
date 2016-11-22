//==========================================================================
// _mm256_shuffle_ps
//     float32 ベクトルをシャッフルします。対応する AVX 命令は VSHUFPS です。
//
// C:\>shuffle_ps
// da:   1.0    2.0    3.0    4.0    5.0    6.0    7.0    8.0
// db:  11.0   12.0   13.0   14.0   15.0   16.0   17.0   18.0
//
// dc:   1.0    2.0   13.0   14.0    5.0    6.0   17.0   18.0
// dc:   4.0    3.0   12.0   11.0    8.0    7.0   16.0   15.0
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
    __m256 da = _mm256_setr_ps(1,2,3,4,5,6,7,8);
    __m256 db = _mm256_setr_ps(11,12,13,14,15,16,17,18);
    __m256 dc;

    printDc("da: ", da);
    printDc("db: ", db);
    printf("\n");


    dc = _mm256_shuffle_ps(da, db, 0xE4);
    printDc("dc: ", dc);


    dc = _mm256_shuffle_ps(da, db, 0x1B);
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
