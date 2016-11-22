//==========================================================================
// _mm256_maskload_pd、_mm_maskload_pd
// mask の値に応じて、パックド倍精度浮動小数点値をロードします。
// 対応する AVX 命令は VMASKMOVPD です。
//
// _mm256_maskload_ps、_mm_maskload_ps
// mask の値に応じて、パックド単精度浮動小数点値をロードします。
// 対応する AVX 命令は VMASKMOVPS です。
//
// C:\>maskload
// before:
//  pd.m256d_f64[0]=  1.0
//  pd.m256d_f64[1]=  2.0
//  pd.m256d_f64[2]=  3.0
//  pd.m256d_f64[3]=  4.0
//
// after:
//  pd.m256d_f64[0]=  1.0
//  pd.m256d_f64[1]=  0.0
//  pd.m256d_f64[2]=  0.0
//  pd.m256d_f64[3]=  4.0
//
//
// before:
//  ps.m256_f32[0]=  1.0
//  ps.m256_f32[1]=  2.0
//  ps.m256_f32[2]=  3.0
//  ps.m256_f32[3]=  4.0
//  ps.m256_f32[4]=  5.0
//  ps.m256_f32[5]=  6.0
//  ps.m256_f32[6]=  7.0
//  ps.m256_f32[7]=  8.0
//
// after:
//  ps.m256_f32[0]=  0.0
//  ps.m256_f32[1]=  2.0
//  ps.m256_f32[2]=  0.0
//  ps.m256_f32[3]=  4.0
//  ps.m256_f32[4]=  0.0
//  ps.m256_f32[5]=  6.0
//  ps.m256_f32[6]=  0.0
//  ps.m256_f32[7]=  8.0
//
//
// before:
//  pd128.m128d_f64[0]=  1.0
//  pd128.m128d_f64[1]=  2.0
//
// after:
//  pd128.m128d_f64[0]=  1.0
//  pd128.m128d_f64[1]=  0.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

typedef unsigned long long int uint64;

int
main(void)
{
    // pd
    double  a[]={1.0, 2.0, 3.0, 4.0};
    __m256d pd=_mm256_setr_pd(1.0, 2.0, 3.0, 4.0);

    puts("before:");
    for(int i=0; i<sizeof(pd)/sizeof(pd.m256d_f64[0]); i++)
        printf(" pd.m256d_f64[%d]=%5.1f\n", i, pd.m256d_f64[i]);

    __m256i mask;
    mask.m256i_u64[0]=(uint64)1<<63;
    mask.m256i_u64[1]=0;
    mask.m256i_u64[2]=0;
    mask.m256i_u64[3]=(uint64)1<<63;

    pd = _mm256_maskload_pd(a, mask);

    puts("\nafter:");
    for(int i=0; i<sizeof(pd)/sizeof(pd.m256d_f64[0]); i++)
        printf(" pd.m256d_f64[%d]=%5.1f\n", i, pd.m256d_f64[i]);



    // ps
    float  b[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    __m256 ps=_mm256_setr_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    puts("\n\nbefore:");
    for(int i=0; i<sizeof(ps)/sizeof(ps.m256_f32[0]); i++)
        printf(" ps.m256_f32[%d]=%5.1f\n", i, ps.m256_f32[i]);

    __m256i mask_ps;
    for(int i=0; i<sizeof(mask_ps)/sizeof(mask_ps.m256i_u32[0]); i++)
        if(i%2)
            mask_ps.m256i_u32[i]=1<<31;

    ps = _mm256_maskload_ps(b, mask_ps);

    puts("\nafter:");
    for(int i=0; i<sizeof(ps)/sizeof(ps.m256_f32[0]); i++)
        printf(" ps.m256_f32[%d]=%5.1f\n", i, ps.m256_f32[i]);


    // pd 128
    __m128d pd128=_mm_setr_pd(1.0, 2.0);
    __m128i mask128;
    mask128.m128i_u64[0]=(uint64)1<<63;
    mask128.m128i_u64[1]=0;

    puts("\n\nbefore:");
    for(int i=0; i<sizeof(pd128)/sizeof(pd128.m128d_f64[0]); i++)
        printf(" pd128.m128d_f64[%d]=%5.1f\n", i, pd128.m128d_f64[i]);

    pd128 = _mm_maskload_pd(a, mask128);

    puts("\nafter:");
    for(int i=0; i<sizeof(pd128)/sizeof(pd128.m128d_f64[0]); i++)
        printf(" pd128.m128d_f64[%d]=%5.1f\n", i, pd128.m128d_f64[i]);

    // ps は省略

    return 0;
}
