//==========================================================================
// extract Green, BGRA or BGRX only
//
// program�� <����.bmp> <�o��.bmp>
//
//
//
// -------------------------------------
// C:\temp>extractGreen
// error: �����Ɉȉ��̒l���w�肵�Ă�������.
//   <���̓t�@�C��>  <�o�̓t�@�C��>
//
// -------------------------------------
// C:\temp>extractGreen obj2_256x256.bmp a.bmp
// �r�b�g�}�b�v�T�C�Y= 256 x 256, 24/pixel
// error: 32 �r�b�g�摜�t�@�C���łȂ�.
//
// -------------------------------------
// C:\temp>extractGreen obj2_1999x2452BGRA.bmp a.bmp
//
// �r�b�g�}�b�v�T�C�Y= 1999 x 2452, 32/pixel
// error: ������8�s�N�Z���P�ʂłȂ�.
//
// -------------------------------------
// C:\temp>extractGreen obj2_256x256BGRA.bmp a.bmp
// �r�b�g�}�b�v�T�C�Y= 256 x 256, 32/pixel
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
            throw "�����Ɉȉ����w�肵�Ă�������.\n" \
                            "  <���̓t�@�C��>  <�o�̓t�@�C��>";

        Cbmp cppBmp, avxBmp;
        cppBmp.loadFromFile(argv[1]);   // load bitmap
        avxBmp.loadFromFile(argv[1]);   // load bitmap

        // print image size
        fprintf(stdout, "�r�b�g�}�b�v�T�C�Y= %d x %d, %d/pixel\n",
            cppBmp.getWidth(), cppBmp.getHeight(), cppBmp.getBitsPerPixcel());

        if (cppBmp.getBitsPerPixcel() != 32)
            throw "32 �r�b�g�摜�t�@�C���łȂ�.";

        if ((cppBmp.getWidth() % 8) != 0)
            throw "������8�s�N�Z���P�ʂłȂ�.";

        effectCpp(&cppBmp);   // filter
        effectAvx(&avxBmp);   // filter

        if (memcmp((void*)cppBmp.getPbitmapBody(),
                            (void*)avxBmp.getPbitmapBody(),
                                        (size_t)avxBmp.mImageSize))
            throw "C++��AVX�ŏ����������ʂ��قȂ�.";

        avxBmp.saveToFile(argv[2]);  // save bitmap
    }
    catch (char *str)
    {
        fprintf(stderr, "error: %s\n", str);
        return -1;
    }

    return 0;
}
