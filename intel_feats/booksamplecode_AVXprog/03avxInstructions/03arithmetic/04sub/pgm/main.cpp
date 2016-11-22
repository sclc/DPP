//==========================================================================
// _mm256_sub_ps
// float32 ベクトルを減算します。対応する AVX 命令は VSUBPS です。
//
// _mm256_sub_pd
// float64 ベクトルを減算します。対応する AVX 命令は VSUBPD です。
//
// C:\>sub
// out[0]= -0.1
// out[1]= -0.2
// out[2]= -0.3
// out[3]= -0.4
// out[4]= -0.5
// out[5]= -0.6
// out[6]= -0.7
// out[7]= -0.8
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

    __m256 dst = _mm256_sub_ps(a, b);

    _mm256_storeu_ps(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%5.1f\n", i, out[i]);

    return 0;
}
