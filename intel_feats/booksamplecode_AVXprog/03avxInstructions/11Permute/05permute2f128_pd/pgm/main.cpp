//==========================================================================
// _mm256_permute2f128_pd
//     フィールドを含む 128 ビットの倍精度浮動小数点を 256 ビットの
//     デスティネーション・ベクトルに並べ替えます。対応する AVX 命令は
//     VPERM2F128 です。
//
// C:\>permute2f128_pd
// da:   1.0    2.0    3.0    4.0
// db:  11.0   12.0   13.0   14.0
//
// dc:  11.0   12.0    1.0    2.0
// dc:   0.0    0.0    1.0    2.0
// dc:   3.0    4.0   11.0   12.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

void printDc(char* prompt, __m256d dc);

int
main(void)
{
    __m256d da = _mm256_setr_pd(1,2,3,4);
    __m256d db = _mm256_setr_pd(11,12,13,14);
    __m256d dc;

    printDc("da: ", da);
    printDc("db: ", db);
    printf("\n");


    dc = _mm256_permute2f128_pd(da, db, 0x02);
    printDc("dc: ", dc);

    dc = _mm256_permute2f128_pd(da, db, 0x0A);
    printDc("dc: ", dc);

    dc = _mm256_permute2f128_pd(da, db, 0x21);
    printDc("dc: ", dc);


    return 0;
}

void
printDc(char* prompt, __m256d dc)
{
    printf("%s", prompt);
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256d_f64[0]); i++)
        printf("%5.1f  ", dc.m256d_f64[i]);
    printf("\n");
}
