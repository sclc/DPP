//==========================================================================
// negative
//
// program名 <入力.bmp> <出力.bmp>
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "bitmapStruct.h"
#include "Cbmp.h"
#include <immintrin.h>

//-------------------------------------------------------------------
// effect C++
static void
effectCpp(unsigned char* pBitmap, const size_t imageSize)
{
    for (size_t i = 0; i < imageSize; i++)
        pBitmap[i] = (unsigned char)~pBitmap[i];
}

//-------------------------------------------------------------------
// effect AVX
static void
effectAvx(unsigned char* pBitmap, const size_t imageSize)
{
    __m256i y = _mm256_set_epi32(-1, -1, -1, -1, -1, -1, -1, -1);
    __m256d *ff = (__m256d *)&y;

    double *pData = (double *)pBitmap;
    for (size_t i = 0; i < imageSize / sizeof(__m256d);
                i++, pData += sizeof(__m256d) / sizeof(double))
    {
        __m256d d = _mm256_xor_pd(*ff, _mm256_load_pd(pData));
        _mm256_store_pd(pData, d);
    }
}


//-------------------------------------------------------------------
// main
int
main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
            throw "引数に以下を指定してください.\n" \
                            "  <入力ファイル>  <出力ファイル>";

        Cbmp cppBmp, avxBmp;
        cppBmp.loadFromFile(argv[1]);   // load bitmap
        avxBmp.loadFromFile(argv[1]);   // load bitmap

        // print image size
        fprintf(stdout, "ビットマップサイズ= %d x %d, %d/pixel\n",
            cppBmp.getWidth(), cppBmp.getHeight(), cppBmp.getBitsPerPixcel());

        effectCpp(cppBmp.getPbitmapBody(), cppBmp.mImageSize);   // filter
        effectAvx(avxBmp.getPbitmapBody(), avxBmp.mImageSize);   // filter

        if (memcmp((void*)cppBmp.getPbitmapBody(),
                            (void*)avxBmp.getPbitmapBody(),
                                        (size_t)avxBmp.mImageSize))
            throw "C++とAVXで処理した結果が異なる.";

        avxBmp.saveToFile(argv[2]);  // save bitmap
    }
    catch (char *str)
    {
        fprintf(stderr, "error: %s\n", str);
        return -1;
    }

    return 0;
}
