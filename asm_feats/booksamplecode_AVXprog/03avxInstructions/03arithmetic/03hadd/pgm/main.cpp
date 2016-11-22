//==========================================================================
// _mm256_hadd_pd
//     2 つのベクトルの float64 要素のペアを水平加算します。
//     対応する AVX 命令は VHADDPD です。
//
// _mm256_hadd_ps
//     2 つのベクトルの float32 要素のペアを水平加算します。
//     対応する AVX 命令は VHADDPS です。
//
// C:\>hadd
// out[0]= 3.0
// out[1]= 3.3
// out[2]= 7.0
// out[3]= 7.7
//
//  1.0,  2.0,  3.0,  4.0
//  1.1,  2.2,  3.3,  4.4
// ------------------------
//  3.0,  3.3,  7.0,  7.7
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    double out[4];

    __m256d a=_mm256_setr_pd(1.0, 2.0, 3.0, 4.0);
    __m256d b=_mm256_setr_pd(1.1, 2.2, 3.3, 4.4);

    __m256d dst = _mm256_hadd_pd(a, b);

    _mm256_storeu_pd(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%4.1f\n", i, out[i]);

    return 0;
}
