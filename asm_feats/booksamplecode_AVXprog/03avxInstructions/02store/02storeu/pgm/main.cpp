﻿//==========================================================================
// _mm256_storeu_pd
//     float64 ベクトルのパックド倍精度浮動小数点値をアライメントされて
//     いないメモリー位置へストアします。対応する AVX 命令は MOVAPD です。
//
// _mm256_storeu_ps
//     float32 ベクトルのパックド単精度浮動小数点値をアライメントされて
//     いないメモリー位置へストアします。対応する AVX 命令は VMOVAPS です。
//
// _mm256_storeu_si256
//     整数ベクトルの値をアライメントされていないメモリー位置へストア
//     します。対応する AVX 命令は VMOVDQA です。
//
// C:\>storeu
// before:
// da[0]=  1.0
// da[1]=  2.0
// da[2]=  3.0
// da[3]=  4.0
// da[4]=  5.0
// da[5]=  6.0
// da[6]=  7.0
// da[7]=  8.0
//
// after:
// da[0]=  1.0
// da[1]=  4.0
// da[2]=  3.0
// da[3]=  2.0
// da[4]=  1.0
// da[5]=  6.0
// da[6]=  7.0
// da[7]=  8.0
//
//
// before:
// fa[0]=  1.0
// fa[1]=  2.0
// fa[2]=  3.0
// fa[3]=  4.0
// fa[4]=  5.0
// fa[5]=  6.0
// fa[6]=  7.0
// fa[7]=  8.0
//
// after:
// fa[0]=  8.0
// fa[1]=  7.0
// fa[2]=  6.0
// fa[3]=  5.0
// fa[4]=  4.0
// fa[5]=  3.0
// fa[6]=  2.0
// fa[7]=  1.0
//
//
// before:
// ia.m256i_i32[0]=1
// ia.m256i_i32[1]=2
// ia.m256i_i32[2]=3
// ia.m256i_i32[3]=4
// ia.m256i_i32[4]=5
// ia.m256i_i32[5]=6
// ia.m256i_i32[6]=7
// ia.m256i_i32[7]=8
//
// after:
// ia.m256i_i32[0]=4
// ia.m256i_i32[1]=3
// ia.m256i_i32[2]=2
// ia.m256i_i32[3]=1
// ia.m256i_i32[4]=5
// ia.m256i_i32[5]=6
// ia.m256i_i32[6]=7
// ia.m256i_i32[7]=8
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    //_mm256_storeu_pd ---------------------------------------------
    double  da[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    puts("before:");
    for(int i=0; i<sizeof(da)/sizeof(da[0]); i++)
        printf("da[%d]=%5.1f\n", i, da[i]);

    __m256d y0 = _mm256_setr_pd(4, 3, 2, 1);
    _mm256_storeu_pd(&da[1], y0);

    puts("\nafter:");
    for(int i=0; i<sizeof(da)/sizeof(da[0]); i++)
        printf("da[%d]=%5.1f\n", i, da[i]);



    //_mm256_storeu_ps ---------------------------------------------
    float  fa[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    puts("\n\nbefore:");
    for(int i=0; i<sizeof(fa)/sizeof(fa[0]); i++)
        printf("fa[%d]=%5.1f\n", i, fa[i]);

    __m256 y1 = _mm256_setr_ps(8, 7, 6, 5, 4, 3, 2, 1);
    _mm256_storeu_ps(fa, y1);

    puts("\nafter:");
    for(int i=0; i<sizeof(fa)/sizeof(fa[0]); i++)
        printf("fa[%d]=%5.1f\n", i, fa[i]);



    //_mm256_storeu_si256 ---------------------------------------------
    __m256i ia = _mm256_setr_epi32(1,2,3,4,5,6,7,8);

    puts("\n\nbefore:");
    for(int i=0; i<sizeof(ia)/sizeof(ia.m256i_i32[0]); i++)
        printf("ia.m256i_i32[%d]=%d\n", i, ia.m256i_i32[i]);

    ia.m256i_i32[0]=4;
    ia.m256i_i32[1]=3;
    ia.m256i_i32[2]=2;
    ia.m256i_i32[3]=1;
    _mm256_storeu_si256(&ia, ia);

    puts("\nafter:");
    for(int i=0; i<sizeof(ia)/sizeof(ia.m256i_i32[0]); i++)
        printf("ia.m256i_i32[%d]=%d\n", i, ia.m256i_i32[i]);

    return 0;
}
