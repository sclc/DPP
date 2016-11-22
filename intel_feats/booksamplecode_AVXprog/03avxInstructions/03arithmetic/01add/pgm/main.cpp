//==========================================================================
// float64 ベクトルを加算します。対応する AVX 命令は VADDPD です。
// _mm256_add_psはfloat32になるだけで、同様。
//
// C:\>add
// out[0]= 2.1
// out[1]= 4.2
// out[2]= 6.3
// out[3]= 8.4
//
// ---処理結果
//  1.0,  2.0,  3.0,  4.0
//   +     +     +     +
//  1.1,  2.2,  3.3,  4.4
// ------------------------
//  2.1,  4.2,  6.3,  8.4
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

    __m256d dst = _mm256_add_pd(a, b);

    _mm256_store_pd(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%5.1f\n", i, out[i]);

    return 0;
}
