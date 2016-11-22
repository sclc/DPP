//==========================================================================
// _mm_cmp_sd
//     スカラー float64 ベクトルを比較します。対応する AVX 命令は
//     VCMPSD です。
//
// C:\>cpmsd
// 0 12
// -1 12
//
// -1:真
//  0:偽
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

#define EQ      0x00    //Dの要素＝Sの要素ならば真
#define LT      0x01    //Dの要素くSの要素ならば真
#define LE      0x02    //Dの要素≦Sの要素ならば真
#define UNORD   0x03    //Dの要素とS の要素が非順序対であれば真
#define NE      0x04    //Dの要素＝Sの要素でなければ真
#define NLT     0x05    //Dの要素くSの要素でなければ真
#define NLE     0x06    //Dの要素≦Sの要素でなければ頁
#define ORD     0x07    //Dの要素とSの要素が順序対であれば真

int
main(void)
{
    __m128d fa = _mm_setr_pd(1, 12);
    __m128d fb = _mm_setr_pd(5, 12);


    __m128d fd = _mm_cmp_sd(fa, fb, EQ);

    for(int i=0; i<sizeof(fd)/sizeof(fd.m128d_f64[0]);i++)
        printf("%.0f ", fd.m128d_f64[i]);
    printf("\n");


    fd = _mm_cmp_sd(fa, fb, NE);

    for(int i=0; i<sizeof(fd)/sizeof(fd.m128d_f64[0]);i++)
        printf("%.0f ", fd.m128d_f64[i]);
    printf("\n");


    return 0;
}
