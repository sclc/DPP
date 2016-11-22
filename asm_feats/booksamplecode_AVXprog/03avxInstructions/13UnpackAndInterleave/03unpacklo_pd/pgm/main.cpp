//==========================================================================
// _mm256_unpacklo_pd
//     下位のパックド倍精度浮動小数点値をアンパックして、インターリーブ
//     します。対応する AVX 命令は VUNPCKLPD です。
//
// C:\>unpacklo_pd
// da:   1.0    2.0    3.0    4.0
// db:   5.0    6.0    7.0    8.0
//
// dc:   1.0    5.0    3.0    7.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256d da = _mm256_setr_pd(1,2,3,4);
    __m256d db = _mm256_setr_pd(5,6,7,8);

    printf("da: ");
    for(int i=0; i<sizeof(da)/sizeof(da.m256d_f64[0]); i++)
        printf("%5.1f  ", da.m256d_f64[i]);
    printf("\n");
    printf("db: ");
    for(int i=0; i<sizeof(db)/sizeof(db.m256d_f64[0]); i++)
        printf("%5.1f  ", db.m256d_f64[i]);
    printf("\n\n");


    __m256d dc = _mm256_unpacklo_pd(da, db);

    printf("dc: ");
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256d_f64[0]); i++)
        printf("%5.1f  ", dc.m256d_f64[i]);
    printf("\n");

    return 0;
}
