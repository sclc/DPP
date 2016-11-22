//==========================================================================
// convert stereo float text to monaral wav faile
//
// program名 <入力.txt>
//
// 入力ファイル：
//     STEREO:  L, R, L, R, L, R, L, R, L, R, L, R, . . .
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "utils.h"
#include <immintrin.h>


//--------------------------------------------------------------------------
//to Monaural C++
static void
effectCpp(float fData[], const size_t length)
{
    for (size_t i = 0; i < length; i += 2)
        fData[i / 2] = (fData[i] + fData[i + 1]) / 2.0f;
}

//--------------------------------------------------------------------------
//to Monaural AVX
static void
effectAvx(float fData[], const size_t length)
{
    float  sDiv = 2.0f;
    __m256 div = _mm256_broadcast_ss(&sDiv);

    for (size_t i = 0; i < length; i += 16)
    {
        __m256 a = _mm256_load_ps(&fData[i]);
        __m256 b = _mm256_load_ps(&fData[i + 8]);

        __m256 c = _mm256_hadd_ps(a, b);
        c = _mm256_div_ps(c, div);                  // PD format -> 0 2 1 3

        __m256d *pc = (__m256d *)&c;                // PD format -> 0 1 2 3
        __m256d c1 = _mm256_permute2f128_pd(*pc, *pc, 0);
        __m256d c2 = _mm256_permute2f128_pd(*pc, *pc, 0x33);
        *pc = _mm256_shuffle_pd(c1, c2, 0xc);

        _mm256_store_ps(&fData[i / 2], c);
    }
}


//--------------------------------------------------------------------------
// main
int
main(int argc, char *argv[])
{
    float *wavCpp = NULL;
    float *wavAvx = NULL;

    try
    {
        if (argc != 2)
            throw "引数に <入力.txt> を指定してください.";

        size_t wavLength = countLines(argv[1]);
        size_t alignedLength = wavLength;
        wavCpp = avxFloatAlloc(&alignedLength);
        wavAvx = avxFloatAlloc(&alignedLength);

        readData(argv[1], wavAvx, wavLength);           // 読み込み
        memcpy((void*)wavCpp, (void*)wavAvx, (size_t)wavLength*sizeof(float));

        effectCpp(wavCpp, wavLength);
        effectAvx(wavAvx, wavLength);

        if (memcmp((void*)wavCpp, (void*)wavAvx, (size_t)(wavLength / 2)*sizeof(float)))
            throw "C++とAVXで処理した結果が異なる.";

        for (size_t i = 0; i < wavLength / 2; i++)        // dump it
            printf("%12.4f\n", wavAvx[i]);
    }
    catch (char *str)
    {
        fputs(str, stderr);
    }
    SP_MM_FREE(wavCpp);
    SP_MM_FREE(wavAvx);

    return 0;
}
