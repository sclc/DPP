﻿//==========================================================================
// ベクトルの奇数の float32 要素を加算し、偶数の float32 要素を減算します。
// 対応する AVX 命令は VADDSUBPS です。
//
// _mm256_addsub_pd はfloat64になるだけで、同様。
// ベクトルの奇数の float64 要素を加算し、偶数の float64 要素を減算します。
// 対応する AVX 命令は VADDSUBPD です。
//
// C:\>addsub
// out[0]= -0.1
// out[1]=  4.2
// out[2]= -0.3
// out[3]=  8.4
// out[4]= -0.5
// out[5]= 12.6
// out[6]= -0.7
// out[7]= 16.8
//
// ---処理結果
//   1.0,   2.0,   3.0,  4.0,  5.0,  6.0,  7.0,   8.0
//    -      +      -     +     -     +     -      +
//   1.1,   2.2,   3.3,  4.4,  5.5,  6.6,  7.7,   8.8
// -----------------------------------------------------
//  -0.1,   4.2,  -0.3,  8.4, -0.5, 12.6, -0.70, 16.8
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    float out[8];

    __m256 a=_mm256_setr_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
    __m256 b=_mm256_setr_ps(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f);

    __m256 dst = _mm256_addsub_ps(a, b);

    _mm256_storeu_ps(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%5.1f\n", i, out[i]);

    return 0;
}
