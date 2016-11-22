//==========================================================================
// _mm256_loadu_pd
//     パックド倍精度浮動小数点値を、アライメントされていないメモリー位置
//     からデスティネーション・ベクトルにロードします。対応する AVX 命令
//     は VMOVUPD です。
//
// _mm256_loadu_ps
//     パックド単精度浮動小数点値を、アライメントされていないメモリー位置
//     からデスティネーション・ベクトルにロードします。対応する AVX 命令は
//     VMOVUPS です。
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    double  a[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float   b[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};


    __m256d pd = _mm256_loadu_pd(a);

    for(int i=0; i<sizeof(pd)/sizeof(pd.m256d_f64[0]); i++)
        printf("pd.m256d_f64[%d]=%5.1f\n", i, pd.m256d_f64[i]);


    __m256 ps = _mm256_loadu_ps(b);

    for(int i=0; i<sizeof(ps)/sizeof(ps.m256_f32[0]); i++)
        printf("ps.m256_f32[%d]=%5.1f\n", i, ps.m256_f32[i]);




    __m256i c;
    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i32[0]); i++)
        c.m256i_i32[i]=i+10;

    __m256i si = _mm256_loadu_si256(&c);

    for(int i=0; i<sizeof(si)/sizeof(si.m256i_i32[0]); i++)
        printf("si.m256i_i32[%d]=%3d\n", i, si.m256i_i32[i]);


    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i8[0]); i++)
        c.m256i_i8[i]=i+50;

    si = _mm256_loadu_si256(&c);

    for(int i=0; i<sizeof(si)/sizeof(si.m256i_i8[0]); i++)
        printf("si.m256i_i8[%d]=%3d\n", i, si.m256i_i8[i]);

    return 0;
}
