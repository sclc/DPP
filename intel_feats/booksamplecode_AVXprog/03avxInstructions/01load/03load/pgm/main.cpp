//==========================================================================
// _mm256_load_pd
//     パックド倍精度浮動小数点値を、アライメントされたメモリー位置から
//     デスティネーション・ベクトルにロードします。対応する AVX 命令は
//     VMOVAPD です。
//
// _mm256_load_ps
//     パックド単精度浮動小数点値を、アライメントされたメモリー位置から
//     デスティネーション・ベクトルにロードします。対応する AVX 命令は
//     VMOVAPS です。
//
// _mm256_load_si256
//     整数値をアライメントされたメモリー位置からデスティネーション・ベク
//     トルにロードします。対応する AVX 命令は VMOVDQA です。
//
// C:\>load
// pd.m256d_f64[0]=  1.0
// pd.m256d_f64[1]=  2.0
// pd.m256d_f64[2]=  3.0
// pd.m256d_f64[3]=  4.0
//
// ps.m256_f32[0]=  1.0
// ps.m256_f32[1]=  2.0
// ps.m256_f32[2]=  3.0
// ps.m256_f32[3]=  4.0
// ps.m256_f32[4]=  5.0
// ps.m256_f32[5]=  6.0
// ps.m256_f32[6]=  7.0
// ps.m256_f32[7]=  8.0
//
// si.m256i_i32[0]= 10
// si.m256i_i32[1]= 11
// si.m256i_i32[2]= 12
// si.m256i_i32[3]= 13
// si.m256i_i32[4]= 14
// si.m256i_i32[5]= 15
// si.m256i_i32[6]= 16
// si.m256i_i32[7]= 17
//
// si.m256i_i8[0]= 50
// si.m256i_i8[1]= 51
// si.m256i_i8[2]= 52
// si.m256i_i8[3]= 53
// si.m256i_i8[4]= 54
// si.m256i_i8[5]= 55
// si.m256i_i8[6]= 56
// si.m256i_i8[7]= 57
// si.m256i_i8[8]= 58
// si.m256i_i8[9]= 59
// si.m256i_i8[10]= 60
// si.m256i_i8[11]= 61
// si.m256i_i8[12]= 62
// si.m256i_i8[13]= 63
// si.m256i_i8[14]= 64
// si.m256i_i8[15]= 65
// si.m256i_i8[16]= 66
// si.m256i_i8[17]= 67
// si.m256i_i8[18]= 68
// si.m256i_i8[19]= 69
// si.m256i_i8[20]= 70
// si.m256i_i8[21]= 71
// si.m256i_i8[22]= 72
// si.m256i_i8[23]= 73
// si.m256i_i8[24]= 74
// si.m256i_i8[25]= 75
// si.m256i_i8[26]= 76
// si.m256i_i8[27]= 77
// si.m256i_i8[28]= 78
// si.m256i_i8[29]= 79
// si.m256i_i8[30]= 80
// si.m256i_i8[31]= 81
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __declspec(align(32)) double  a[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    __declspec(align(32)) float   b[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};


    //_mm256_load_pd
    __m256d pd = _mm256_load_pd(a);

    for(int i=0; i<sizeof(pd)/sizeof(pd.m256d_f64[0]); i++)
        printf("pd.m256d_f64[%d]=%5.1f\n", i, pd.m256d_f64[i]);


    //_mm256_load_ps
    __m256 ps = _mm256_load_ps(b);

    for(int i=0; i<sizeof(ps)/sizeof(ps.m256_f32[0]); i++)
        printf("ps.m256_f32[%d]=%5.1f\n", i, ps.m256_f32[i]);




    //_mm256_load_si256
    __m256i c;
    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i32[0]); i++)
        c.m256i_i32[i]=i+10;

    __m256i si = _mm256_load_si256(&c);

    for(int i=0; i<sizeof(si)/sizeof(si.m256i_i32[0]); i++)
        printf("si.m256i_i32[%d]=%3d\n", i, si.m256i_i32[i]);


    for(int i=0; i<sizeof(c)/sizeof(c.m256i_i8[0]); i++)
        c.m256i_i8[i]=i+50;

    si = _mm256_load_si256(&c);

    for(int i=0; i<sizeof(si)/sizeof(si.m256i_i8[0]); i++)
        printf("si.m256i_i8[%d]=%3d\n", i, si.m256i_i8[i]);

    return 0;
}
