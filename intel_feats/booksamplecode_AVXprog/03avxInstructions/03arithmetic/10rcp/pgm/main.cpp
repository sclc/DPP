//==========================================================================
// _mm256_rcp_ps
// float32 値の逆数の近似値を計算します。対応する AVX 命令は VRCPPS です。
//
// C:\>rcp
// out[0]=  0.999756
// out[1]=  0.499878
// out[2]=  0.333252
// out[3]=  0.249939
// out[4]=  0.199951
// out[5]=  0.166626
// out[6]=  0.142822
// out[7]=  0.124969
//
// out[0]=  1.000244
// out[1]=  2.000488
// out[2]=  3.000000
// out[3]=  4.000977
// out[4]=  5.000000
// out[5]=  6.000000
// out[6]=  7.000000
// out[7]=  8.001953
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

    __m256 dst = _mm256_rcp_ps(a);

    _mm256_storeu_ps(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%10.6f\n", i, out[i]);

    //逆数の逆数で元に戻る
    dst = _mm256_rcp_ps(dst);
    _mm256_storeu_ps(out, dst);

    printf("\n");
    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%10.6f\n", i, out[i]);

    return 0;
}
