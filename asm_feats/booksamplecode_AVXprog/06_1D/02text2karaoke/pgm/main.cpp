//==========================================================================
// karaoke -- eliminate vocal
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
#include <math.h>
#include "common.h"
#include "utils.h"
#include <immintrin.h>


//--------------------------------------------------------------------------
//to Karaoke C++
static void
effectCpp(float fData[], const size_t length)
{
    for (size_t i = 0; i < length; i += 2)
    {
        float L = fData[i + 0] - fData[i + 1];
        float R = fData[i + 1] - fData[i + 0];
        fData[i + 0] = max(-32768.0f, min(32767.0f, L));
        fData[i + 1] = max(-32768.0f, min(32767.0f, R));
    }
}

//--------------------------------------------------------------------------
//to Karaoke AVX
static void
effectAvx(float fData[], const size_t length)
{
    const float  fMax = powf(2.0f, 15.0f) - 1.0f;   // + (2^15 - 1)
    const float  fMin = -powf(2.0f, 15.0f);         // -  2^15
    __m256 psMax = _mm256_broadcast_ss(&fMax);
    __m256 psMin = _mm256_broadcast_ss(&fMin);

    for (size_t i = 0; i < length; i += 8)
    {
        __m256 a = _mm256_load_ps(&fData[i]);
        __m256 b = _mm256_shuffle_ps(a, a, 0xb1);

        __m256 c = _mm256_sub_ps(a, b);

        c = _mm256_min_ps(c, psMax);
        c = _mm256_max_ps(c, psMin);

        _mm256_store_ps(&fData[i], c);
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

        if (memcmp((void*)wavCpp, (void*)wavAvx, (size_t)wavLength*sizeof(float)))
            throw "C++とAVXで処理した結果が異なる.";

        for (size_t i = 0; i < wavLength; i++)          // dump it
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
