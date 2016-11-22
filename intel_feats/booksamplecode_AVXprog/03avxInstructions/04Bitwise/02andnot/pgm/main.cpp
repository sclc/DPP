//==========================================================================
// _mm256_andnot_pd
//     float64 ベクトルのビット単位の AND NOT (否定論理積) 演算を行います。
//     対応する AVX 命令は VANDNPD です。
//
// _mm256_andnot_ps
//     float32 ベクトルのビット単位の AND NOT (否定論理積) 演算を行います。
//     対応する AVX 命令は VANDNPS です。
//
//
// VANDNPD (VEX.256 encoded version)
//     DEST[63:0]    ← (NOT(SRC1[63:0]))    BITWISE AND  SRC2[63:0]
//     DEST[127:64]  ← (NOT(SRC1[127:64]))  BITWISE AND  SRC2[127:64]
//     DEST[191:128] ← (NOT(SRC1[191:128])) BITWISE AND  SRC2[191:128]
//     DEST[255:192] ← (NOT(SRC1[255:192])) BITWISE AND  SRC2[255:192]
//
//
//   ~a & b = ~(0x59) & 0x95 = 0xA6 & 0x95
//
//           0xA6 = 1010 0110b
//           0x95 = 1001 0101b
//                     &
//                  1000 0100b = 0x84
//
//
// C:\>andnot
// 84848484 84848484 84848484 84848484 84848484 84848484 84848484 84848484
// 84848484 84848484 84848484 84848484 84848484 84848484 84848484 84848484
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

    //_mm256_andnot_pd
    __m256d pd = _mm256_andnot_pd(_mm256_castsi256_pd(a), _mm256_castsi256_pd(b));

    __m256i p = _mm256_castpd_si256(pd);
    for(int i=0; i<sizeof(p)/sizeof(p.m256i_u32[0]);i++)
        printf("%08X ", p.m256i_u32[i]);
    printf("\n");


    //_mm256_andnot_ps
    __m256 ps = _mm256_andnot_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b));

    p = _mm256_castps_si256(ps);

    for(int i=0; i<sizeof(p)/sizeof(p.m256i_u32[0]);i++)
        printf("%08X ", p.m256i_u32[i]);
    printf("\n");

    return 0;
}
