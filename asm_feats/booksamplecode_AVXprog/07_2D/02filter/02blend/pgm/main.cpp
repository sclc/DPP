//==========================================================================
// blend
//
// program名 <入力1.bmp> <入力2.bmp> <出力.bmp>
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "bitmapStruct.h"
#include "Cbmp.h"
#include <immintrin.h>

int avxGray(const unsigned char* in, const float *out,
                        const size_t width, const size_t height);


//-------------------------------------------------------------------
// chang format, float array to BGRA format
void
cnvFormat(void *pBuffer, Cbmp *bmp)
{
    size_t width = bmp->getWidth();
    size_t height = bmp->getAbsHeight();

    unsigned char *pMem = bmp->getPbitmapBody();
    float *pGrayF = (float *)pBuffer;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++, pGrayF++, pMem += 4)
            *(pMem + 0) = *(pMem + 1) = *(pMem + 2) =
                        (unsigned char)max(0, min(255, *pGrayF));
    }
}

//-------------------------------------------------------------------
// toGrayscale
//
// return: float array
//
static float*
toGrayscale(Cbmp *bmp)
{
    size_t width = bmp->getWidth();
    size_t height = bmp->getAbsHeight();

    float *pOut = NULL;
    if ((pOut = (float *)_mm_malloc(width*sizeof(float)*height, AVX_ALIGN)) == NULL)
        return NULL;

    if (avxGray(bmp->getPbitmapBody(), pOut, width, height) != 0)
        return NULL;

    return pOut;
}


//-------------------------------------------------------------------
// blend
void
effect(float *pBuffer[], const Cbmp *bmp)
{
    size_t width = bmp->getWidth();
    size_t height = bmp->getAbsHeight();

    const float fdiv = 2.0f;
    __m256 div = _mm256_broadcast_ss(&fdiv);

    float *pF[2];
    pF[0] = pBuffer[0];
    pF[1] = pBuffer[1];

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x += 8, pF[0] += 8, pF[1] += 8)
        {
            __m256 p0 = _mm256_load_ps(pF[0]);
            __m256 p1 = _mm256_load_ps(pF[1]);

            __m256 r = _mm256_add_ps(p0, p1);
            r = _mm256_div_ps(r, div);

            _mm256_store_ps(pF[0], r);
        }
    }
}

//-------------------------------------------------------------------
// main
int
main(int argc, char* argv[])
{
    try
    {
        float* pBuffer[2];
        Cbmp bmp[2];

        if (argc != 4)
            throw "引数に以下を指定してください.\n" \
                    " <入力ファイル1> <入力ファイル2> <出力ファイル>";

        bmp[0].loadFromFile(argv[1]);           // load bitmap
        bmp[1].loadFromFile(argv[2]);           // load bitmap

        if (bmp[0].getBitsPerPixcel() != 32)
            throw "32 ビット画像ファイルでない.";

        if ((bmp[0].getWidth() % 8) != 0)
            throw "横幅が8ピクセル単位でない.";

        if (bmp[0].getWidth() != bmp[1].getWidth() ||
                bmp[0].getHeight() != bmp[1].getHeight() ||
                    bmp[0].getBitsPerPixcel() != bmp[1].getBitsPerPixcel())
            throw "二つの画像のサイズや属性が異なる.";

        // print image size
        fprintf(stdout, "ビットマップサイズ= %d x %d, %d/pixel\n",
            bmp[0].getWidth(), bmp[0].getHeight(), bmp[0].getBitsPerPixcel());

        pBuffer[0] = toGrayscale(&bmp[0]);      // toGrayscale
        pBuffer[1] = toGrayscale(&bmp[1]);      // toGrayscale

        effect(pBuffer, &bmp[0]);

        cnvFormat(pBuffer[0], &bmp[0]);         // chang format

        SP_MM_FREE(pBuffer[0]);
        SP_MM_FREE(pBuffer[1]);

        bmp[0].saveToFile(argv[3]);             // save bitmap
    }
    catch (char *str)
    {
        fprintf(stderr, "error: %s\n", str);
    }

    return 0;
}
