//==========================================================================
// _mm256_broadcast_pd
//     パックド倍精度浮動小数点値をロードして、ブロードキャストします。
//     対応する AVX 命令は VBROADCAST128 です。
//
// _mm256_broadcast_ps
//     パックド単精度浮動小数点値をロードして、ブロードキャストします。
//     対応するAVX 命令は VBROADCAST128 です。
//
// C:\>broadcastPack
// dstPd.m256d_f64[0]=  1.0
// dstPd.m256d_f64[1]=  2.0
// dstPd.m256d_f64[2]=  1.0
// dstPd.m256d_f64[3]=  2.0
//
// dstPs.m256_f32[0]=  1.0
// dstPs.m256_f32[1]=  2.0
// dstPs.m256_f32[2]=  3.0
// dstPs.m256_f32[3]=  4.0
// dstPs.m256_f32[4]=  1.0
// dstPs.m256_f32[5]=  2.0
// dstPs.m256_f32[6]=  3.0
// dstPs.m256_f32[7]=  4.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m128d a={1.0, 2.0};
    __m128  b={1.0, 2.0, 3.0, 4.0};

    //_mm256_broadcast_pd
    __m256d dstPd = _mm256_broadcast_pd(&a);

    for(int i=0; i<sizeof(dstPd)/sizeof(dstPd.m256d_f64[0]); i++)
        printf("dstPd.m256d_f64[%d]=%5.1f\n", i, dstPd.m256d_f64[i]);

    printf("\n");


    //_mm256_broadcast_ps
    __m256 dstPs = _mm256_broadcast_ps(&b);

    for(int i=0; i<sizeof(dstPs)/sizeof(dstPs.m256_f32[0]); i++)
        printf("dstPs.m256_f32[%d]=%5.1f\n", i, dstPs.m256_f32[i]);

    return 0;
}
