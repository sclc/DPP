//==========================================================================
// _mm256_permute_ps
//     256 ビットまたは 128 ビットの float32 値を 256 ビットまたは
//     128 ビットのデスティネーション・ベクトルに並べ替えます。
//     対応する AVX 命令は VPERMILPS です。
//
// C:\>permute_ps
// da:   1.0    2.0    3.0    4.0    5.0    6.0    7.0    8.0
// dc:   3.0    1.0    1.0    1.0    7.0    5.0    5.0    5.0
// dc:   2.0    1.0    1.0    1.0    6.0    5.0    5.0    5.0
//
// fa:   1.0    2.0    3.0    4.0
// fc:   3.0    1.0    1.0    1.0
// fc:   2.0    1.0    1.0    1.0
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    //_mm256_permute_ps
    __m256 da = _mm256_setr_ps(1,2,3,4,5,6,7,8);
    __m256 dc;

    printf("da: ");
    for(int i=0; i<sizeof(da)/sizeof(da.m256_f32[0]); i++)
        printf("%5.1f  ", da.m256_f32[i]);
    printf("\n");

    dc = _mm256_permute_ps(da, 0x02);

    printf("dc: ");
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256_f32[0]); i++)
        printf("%5.1f  ", dc.m256_f32[i]);
    printf("\n");


    dc = _mm256_permute_ps(da, 0x01);

    printf("dc: ");
    for(int i=0; i<sizeof(dc)/sizeof(dc.m256_f32[0]); i++)
        printf("%5.1f  ", dc.m256_f32[i]);
    printf("\n\n");

    //_mm_permute_ps
    __m128 fa = _mm_setr_ps(1,2,3,4);
    __m128 fc;

    printf("fa: ");
    for(int i=0; i<sizeof(fa)/sizeof(fa.m128_f32[0]); i++)
        printf("%5.1f  ", fa.m128_f32[i]);
    printf("\n");


    fc = _mm_permute_ps(fa, 0x02);

    printf("fc: ");
    for(int i=0; i<sizeof(fc)/sizeof(fc.m128_f32[0]); i++)
        printf("%5.1f  ", fc.m128_f32[i]);
    printf("\n");


    fc = _mm_permute_ps(fa, 0x01);

    printf("fc: ");
    for(int i=0; i<sizeof(fc)/sizeof(fc.m128_f32[0]); i++)
        printf("%5.1f  ", fc.m128_f32[i]);
    printf("\n");

    return 0;
}
