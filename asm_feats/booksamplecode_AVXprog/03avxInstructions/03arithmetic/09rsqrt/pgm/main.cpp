//==========================================================================
// _mm256_rsqrt_ps
// float32 値の平方根の逆数の近似値を計算します。対応する AVX 命令は 
// VRSQRTPS です。
//
// C:\>rsqrt
// out[0]=  0.999756
// out[1]=  0.706909
// out[2]=  0.577271
// out[3]=  0.499878
// out[4]=  0.447144
// out[5]=  0.408203
// out[6]=  0.377930
// out[7]=  0.353455
//
// out[0]=  1.000244
// out[1]=  1.414609
// out[2]=  1.732290
// out[3]=  2.000489
// out[4]=  2.236418
// out[5]=  2.449761
// out[6]=  2.645995
// out[7]=  2.829218
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

    __m256 dst = _mm256_rsqrt_ps(a);

    _mm256_storeu_ps(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%10.6f\n", i, out[i]);

    //逆数の逆数で平方根に戻る
    __m256 b=_mm256_setr_ps(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    dst = _mm256_div_ps(b, dst);
    _mm256_storeu_ps(out, dst);

    printf("\n");
    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%10.6f\n", i, out[i]);

    return 0;
}
