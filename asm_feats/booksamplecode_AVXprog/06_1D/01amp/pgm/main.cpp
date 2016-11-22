//==========================================================================
// amp -- volume control
//
// program名 <入力.txt> <amp>
//
// 入力ファイル：
//     STEREO or Monaraul
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
// amp C++
static void
effectCpp(float fData[], const float amp, const size_t length)
{
    for (size_t i = 0; i<length; i++)
        fData[i] = fData[i] * amp;
}

//--------------------------------------------------------------------------
// amp AVX
static void
effectAvx(float fData[], const float amp, const size_t length)
{
    __m256 psAmp = _mm256_broadcast_ss(&amp);
    __m256 *pIn = (__m256 *)fData;

    for (size_t i = 0; i < length; i += 8, pIn++)
    {
        __m256 a = _mm256_mul_ps(*pIn, psAmp);
        _mm256_store_ps(&fData[i], a);
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
        if (argc < 3)
            throw "引数に <入力.txt> <ボリューム> を指定してください.";

        float ampValue = atof(argv[2]);
        size_t wavLength = countLines(argv[1]);
        size_t alignedLength = wavLength;
        wavCpp = avxFloatAlloc(&alignedLength);
        wavAvx = avxFloatAlloc(&alignedLength);

        readData(argv[1], wavAvx, wavLength);           // 読み込み
        memcpy((void*)wavCpp, (void*)wavAvx, (size_t)wavLength*sizeof(float));

        effectCpp(wavCpp, ampValue, wavLength);
        effectAvx(wavAvx, ampValue, wavLength);

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
