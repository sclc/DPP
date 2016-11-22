//==========================================================================
// _mm256_xor_pd
//     float64 ベクトルのビット単位の XOR (排他的論理和) 演算を行います。
//     対応する AVX 命令は VXORPD です。
//
//     float32 ベクトルのビット単位の XOR (排他的論理和) 演算を行います。
//     対応する AVX 命令は VXORPS です。
//
// C:\>xor
// CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC
// CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    __m256i a = _mm256_set_epi32(0x59595959,0x59595959,0x59595959,0x59595959,
                                 0x59595959,0x59595959,0x59595959,0x59595959);
    __m256i b = _mm256_set_epi32(0x95959595,0x95959595,0x95959595,0x95959595,
                                 0x95959595,0x95959595,0x95959595,0x95959595);

    //_mm256_xor_pd
    __m256d pd = _mm256_xor_pd(_mm256_castsi256_pd(a), _mm256_castsi256_pd(b));

    __m256i p = _mm256_castpd_si256(pd);
    for(int i=0; i<sizeof(p)/sizeof(p.m256i_u32[0]);i++)
        printf("%08X ", p.m256i_u32[i]);
    printf("\n");


    //_mm256_xor_ps
    __m256 ps = _mm256_xor_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b));

    p = _mm256_castps_si256(ps);

    for(int i=0; i<sizeof(p)/sizeof(p.m256i_u32[0]);i++)
        printf("%08X ", p.m256i_u32[i]);
    printf("\n");

    return 0;
}
