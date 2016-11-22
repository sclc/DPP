//==========================================================================
// _mm_cmp_ss
//     スカラー float32 ベクトルを比較します。対応する AVX 命令は
//     VCMPSS です。
//
// C:\>cpmss
// FFFFFFFF 40000000 40400000 40800000
// 00000000 40000000 40400000 40800000
//
// -1(0xFFFFFFFF):真
//  0(0x00000000):偽
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
    __m128 fa = _mm_setr_ps( 1, 2,  3, 4);
    __m128 fb = _mm_setr_ps( 1, 2,  2, 4);


    __m128 fd = _mm_cmp_ss(fa, fb, EQ);

    for(int i=0; i<sizeof(fd)/sizeof(fd.m128_u32[0]);i++)
        printf("%08X ", fd.m128_i32[i]);
    printf("\n");



    fd = _mm_cmp_ss(fa, fb, NE);

    for(int i=0; i<sizeof(fd)/sizeof(fd.m128_u32[0]);i++)
        printf("%08X ", fd.m128_i32[i]);
    printf("\n");

    return 0;
}
