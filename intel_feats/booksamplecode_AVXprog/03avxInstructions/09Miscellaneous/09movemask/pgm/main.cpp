//==========================================================================
// _mm256_movemask_pd
//     float64 の符号マスクを抽出します。対応する AVX 命令は VMOVMSKPD です。
//
// _mm256_movemask_ps
//     float32 の符号マスクを抽出します。対応する AVX 命令は VMOVMSKPS です。
//
// C:\>movemask
// 0A
// 55
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    //_mm256_movemask_pd
    __m256d da = _mm256_setr_pd(1,-2,3,-4);

    int b = _mm256_movemask_pd(da);

    printf("%02X\n", b);


    //_mm256_movemask_ps
    __m256 fa = _mm256_setr_ps(-1,2,-3,4,-5,6,-7,8);

    b = _mm256_movemask_ps(fa);

    printf("%02X\n", b);

    return 0;
}
