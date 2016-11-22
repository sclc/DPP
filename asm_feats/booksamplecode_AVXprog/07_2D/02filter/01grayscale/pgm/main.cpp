//==========================================================================
// grayscale
//
// brga -> float grayscale -> ggga
//
// program�� <����.bmp> <�o��.bmp>
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
// main
int
main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
            throw "�����Ɉȉ����w�肵�Ă�������.\n" \
                        "  <���̓t�@�C��>  <�o�̓t�@�C��>";

        Cbmp bmp;
        bmp.loadFromFile(argv[1]);              // load bitmap

        // print image size
        fprintf(stdout, "�r�b�g�}�b�v�T�C�Y= %d x %d, %d/pixel\n",
            bmp.getWidth(), bmp.getHeight(), bmp.getBitsPerPixcel());

        if (bmp.getBitsPerPixcel() != 32)
            throw "32 �r�b�g�摜�t�@�C���łȂ�.";

        if ((bmp.getWidth() % 8) != 0)
            throw "������8�s�N�Z���P�ʂłȂ�.";

        float* pBuffer = toGrayscale(&bmp);     // toGrayscale

        cnvFormat(pBuffer, &bmp);               // chang format

        SP_MM_FREE(pBuffer);

        bmp.saveToFile(argv[2]);                // save bitmap
    }
    catch (char *str)
    {
        fprintf(stderr, "error: %s\n", str);
    }

    return 0;
}
