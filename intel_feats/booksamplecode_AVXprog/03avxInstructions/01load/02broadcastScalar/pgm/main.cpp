//==========================================================================
// _mm256_broadcast_sd
//     スカラー倍精度浮動小数点値をロードして、256 ビットのデスティ
//     ネーション・オペランドにブロードキャストします。対応する
//     AVX 命令はVBROADCASTSD です。
//
// _mm256_broadcast_ss、_mm_broadcast_ss
//     256 ビットまたは 128 ビットのスカラー単精度浮動小数点値をロード
//     して、256 ビットまたは 128 ビットのデスティネーション・オペランド
//     にブロードキャストします。対応する AVX 命令は VBROADCASTSS です。
//
// C:\>broadcastScalar
// dstSd.m256d_f64[0]=  1.0
// dstSd.m256d_f64[1]=  1.0
// dstSd.m256d_f64[2]=  1.0
// dstSd.m256d_f64[3]=  1.0
//
// dstSs.m256_f32[0]=  2.0
// dstSs.m256_f32[1]=  2.0
// dstSs.m256_f32[2]=  2.0
// dstSs.m256_f32[3]=  2.0
// dstSs.m256_f32[4]=  2.0
// dstSs.m256_f32[5]=  2.0
// dstSs.m256_f32[6]=  2.0
// dstSs.m256_f32[7]=  2.0
//
// dstMmSs.m128_f32[0]=  2.0
// dstMmSs.m128_f32[1]=  2.0
// dstMmSs.m128_f32[2]=  2.0
// dstMmSs.m128_f32[3]=  2.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    double a=1.0;
    float  b=2.0f;


    //_mm256_broadcast_sd
    __m256d dstSd = _mm256_broadcast_sd(&a);

    for(int i=0; i<sizeof(dstSd)/sizeof(dstSd.m256d_f64[0]); i++)
        printf("dstSd.m256d_f64[%d]=%5.1f\n", i, dstSd.m256d_f64[i]);
    printf("\n");


    //_mm256_broadcast_ss
    __m256 dstSs = _mm256_broadcast_ss(&b);

    for(int i=0; i<sizeof(dstSs)/sizeof(dstSs.m256_f32[0]); i++)
        printf("dstSs.m256_f32[%d]=%5.1f\n", i, dstSs.m256_f32[i]);
    printf("\n");


    //_mm_broadcast_ss
    __m128 dstMmSs = _mm_broadcast_ss(&b);

    for(int i=0; i<sizeof(dstMmSs)/sizeof(dstMmSs.m128_f32[0]); i++)
        printf("dstMmSs.m128_f32[%d]=%5.1f\n", i, dstMmSs.m128_f32[i]);

    return 0;
}
