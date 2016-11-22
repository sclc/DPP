//==========================================================================
// _mm_cmp_ps、_mm256_cmp_ps
//     2 つのベクトルのパックド float32 要素を比較します。
//     対応する AVX 命令は VCMPPS です。
//
// C:\>cpmps
// -1 -1 0 -1
// -1 -1 -1 -1 0 0 0 0
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
    //_mm_cmp_pd
    __m128 fa = _mm_setr_ps( 1, 2,  3, 4);
    __m128 fb = _mm_setr_ps( 1, 2,  2, 4);

    __m128 fd = _mm_cmp_ps(fa, fb, EQ);

    for(int i=0; i<sizeof(fd)/sizeof(fd.m128_u32[0]);i++)
        printf("%d ", fd.m128_i32[i]);
    printf("\n");



    //_m256_cmp_ps
    __m256 da = _mm256_setr_ps(1, 2, 3, 4, 5,  6, 7, 8);
    __m256 db = _mm256_setr_ps(8, 7, 6, 5, 4, 3,  2, 1);

    __m256 pd = _mm256_cmp_ps(da, db, LT);

    for(int i=0; i<sizeof(pd)/sizeof(pd.m256_f32[0]);i++)
        printf("%.0f ", pd.m256_f32[i]);
    printf("\n");

    return 0;
}
