//==========================================================================
// _mm256_maskstore_pd、_mm_maskstore_pd
// mask の値に応じて、パックド倍精度浮動小数点値をストアします。対応する
//  AVX 命令は VMASKMOVPD です。
//
// _mm256_maskstore_ps、_mm_maskstore_ps
// mask の値に応じて、パックド単精度浮動小数点値をストアします。対応する
//  AVX 命令は VMASKMOVPS です。
//
// C:\>maskstore
// before:
//  a[0]=  1.0
//  a[1]=  2.0
//  a[2]=  3.0
//  a[3]=  4.0
//
// after:
//  a[0]= 11.0
//  a[1]=  2.0
//  a[2]=  3.0
//  a[3]= 14.0
//
//
// before:
//  b[0]=  1.0
//  b[1]=  2.0
//  b[2]=  3.0
//  b[3]=  4.0
//  b[4]=  5.0
//  b[5]=  6.0
//  b[6]=  7.0
//  b[7]=  8.0
//
// after:
//  b[0]=  1.0
//  b[1]= 12.0
//  b[2]=  3.0
//  b[3]= 14.0
//  b[4]=  5.0
//  b[5]= 16.0
//  b[6]=  7.0
//  b[7]= 18.0
//
//
// before:
//  c[0]=  1.0
//  c[1]=  2.0
//
// after:
//  c[0]= 11.0
//  c[1]=  2.0
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
    __declspec(align(32)) double  a[]={1.0, 2.0, 3.0, 4.0};
    __m256d pd=_mm256_setr_pd(11.0, 12.0, 13.0, 14.0);

    puts("before:");
    for(int i=0; i<sizeof(a)/sizeof(a[0]); i++)
        printf(" a[%d]=%5.1f\n", i, a[i]);

    __m256i mask;
    mask.m256i_u64[0]=(uint64)1<<63;
    mask.m256i_u64[1]=0;
    mask.m256i_u64[2]=0;
    mask.m256i_u64[3]=(uint64)1<<63;

    _mm256_maskstore_pd(a, mask, pd);

    puts("\nafter:");
    for(int i=0; i<sizeof(a)/sizeof(a[0]); i++)
        printf(" a[%d]=%5.1f\n", i, a[i]);



    // ps
    __declspec(align(32)) float  b[]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    __m256 ps=_mm256_setr_ps(11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0);

    puts("\n\nbefore:");
    for(int i=0; i<sizeof(b)/sizeof(b[0]); i++)
        printf(" b[%d]=%5.1f\n", i, b[i]);

    __m256i mask_ps;
    for(int i=0; i<sizeof(mask_ps)/sizeof(mask_ps.m256i_u32[0]); i++)
        if(i%2)
            mask_ps.m256i_u32[i]=1<<31;

    _mm256_maskstore_ps(b, mask_ps, ps);

    puts("\nafter:");
    for(int i=0; i<sizeof(b)/sizeof(b[0]); i++)
        printf(" b[%d]=%5.1f\n", i, b[i]);


    // pd 128
    __declspec(align(32)) double  c[]={1.0, 2.0};
    __m128d pd128=_mm_setr_pd(11.0, 12.0);
    __m128i mask128;
    mask128.m128i_u64[0]=(uint64)1<<63;
    mask128.m128i_u64[1]=0;

    puts("\n\nbefore:");
    for(int i=0; i<sizeof(c)/sizeof(c[0]); i++)
        printf(" c[%d]=%5.1f\n", i, c[i]);

    _mm_maskstore_pd(c, mask128, pd128);

    puts("\nafter:");
    for(int i=0; i<sizeof(c)/sizeof(c[0]); i++)
        printf(" c[%d]=%5.1f\n", i, c[i]);

    // ps は省略

    return 0;
}
