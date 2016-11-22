//==========================================================================
// _mm256_sqrt_pd
// 倍精度浮動小数点値の平方根を計算します。対応する AVX 命令は VSQRTPD です。
//
// C:\>sqrt
// out[0]=  1.000000
// out[1]=  1.414214
// out[2]=  1.732051
// out[3]=  2.000000
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

    __m256d dst = _mm256_sqrt_pd(a);

    _mm256_storeu_pd(out, dst);

    for(int i=0; i<sizeof(out)/sizeof(out[0]); i++)
        printf("out[%d]=%10.6f\n", i, out[i]);

    return 0;
}
