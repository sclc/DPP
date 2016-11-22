//==========================================================================
// extract Green, BGRA or BGRX only
//
// program名 <入力.bmp> <出力.bmp>
//
//
//
// -------------------------------------
// C:\temp>extractGreen
// error: 引数に以下の値を指定してください.
//   <入力ファイル>  <出力ファイル>
//
// -------------------------------------
// C:\temp>extractGreen obj2_256x256.bmp a.bmp
// ビットマップサイズ= 256 x 256, 24/pixel
// error: 32 ビット画像ファイルでない.
//
// -------------------------------------
// C:\temp>extractGreen obj2_1999x2452BGRA.bmp a.bmp
//
// ビットマップサイズ= 1999 x 2452, 32/pixel
// error: 横幅が8ピクセル単位でない.
//
// -------------------------------------
// C:\temp>extractGreen obj2_256x256BGRA.bmp a.bmp
// ビットマップサイズ= 256 x 256, 32/pixel
//
// -------------------------------------
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
effectCpp(Cbmp *bmp)
{
    int x, y;
    unsigned char *pMem = bmp->getPbitmapBody();

    for (y = 0; y < bmp->getAbsHeight(); y++)
        for (x = 0; x < bmp->getWidth(); x++)
        {
            *pMem++ = 0;           // B
            pMem++;                // skip G
            *pMem++ = 0;           // R
            *pMem++ = 0;           // A
        }
}

//-------------------------------------------------------------------
// effect AVX
static void
effectAvx(Cbmp *bmp)
{
    __m256i mask = _mm256_set_epi32(0xFF00, 0xFF00, 0xFF00, 0xFF00,
                                    0xFF00, 0xFF00, 0xFF00, 0xFF00);
    __m256d maskPd = _mm256_castsi256_pd(mask);

    double *pData = (double *)(bmp->getPbitmapBody());

    for (size_t y = 0; y < bmp->getAbsHeight(); y++)
        for (size_t x = 0; x < bmp->getWidth() / 8; x++)
        {
            __m256d d = _mm256_load_pd(pData);
            __m256d r = _mm256_and_pd(d, maskPd);
            _mm256_store_pd(pData, r);

            pData += sizeof(__m256d) / sizeof(double);
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

        if (cppBmp.getBitsPerPixcel() != 32)
            throw "32 ビット画像ファイルでない.";

        if ((cppBmp.getWidth() % 8) != 0)
            throw "横幅が8ピクセル単位でない.";

        effectCpp(&cppBmp);   // filter
        effectAvx(&avxBmp);   // filter

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
