//==========================================================================
// _mm256_lddqu_si256
//     アライメントされていない整数をメモリからロードします。対応する
//      AVX 命令は VLDDQU です。
//
// C:\>lddqu_si256
// b.m256i_i32[0]=1
// b.m256i_i32[1]=2
// b.m256i_i32[2]=3
// b.m256i_i32[3]=4
// b.m256i_i32[4]=5
// b.m256i_i32[5]=6
// b.m256i_i32[6]=7
// b.m256i_i32[7]=8
//
// b.m256i_i32[0]=2
// b.m256i_i32[1]=3
// b.m256i_i32[2]=4
// b.m256i_i32[3]=5
// b.m256i_i32[4]=6
// b.m256i_i32[5]=7
// b.m256i_i32[6]=8
// b.m256i_i32[7]=9
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    _declspec(align(32)) int a[]={1,2,3,4,5,6,7,8,9,10};

    __m256i *ca = (__m256i *)a;

    __m256i b = _mm256_lddqu_si256(ca);

    for(int i=0; i<sizeof(b)/sizeof(b.m256i_i32[0]); i++)
        printf("b.m256i_i32[%d]=%d\n", i, b.m256i_i32[i]);


    printf("\n");
    ca = (__m256i *)&a[1];

    b = _mm256_lddqu_si256(ca);

    for(int i=0; i<sizeof(b)/sizeof(b.m256i_i32[0]); i++)
        printf("b.m256i_i32[%d]=%d\n", i, b.m256i_i32[i]);

    return 0;
}
