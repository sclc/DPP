//==========================================================================
// extract Green, 24bpp only
//
// program名 <入力.bmp> <出力.bmp>
//
// (c)Copyright Spacesoft corp., 2013 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "bitmapStruct.h"
#include "Cbmp.h"
#include <immintrin.h>


//--------------------------------------------------------------------------
//byte -> float
void
convB2F(const unsigned char bBgr[], float fBgr[], const size_t length)
{
    for (size_t i = 0; i < length; i++)
        fBgr[i] = (float)bBgr[i];
}

//--------------------------------------------------------------------------
//float -> byte
void
convF2B(const float fBgr[], unsigned char bBgr[], const size_t length)
{
    for (size_t i = 0; i < length; i++)
        bBgr[i] = (unsigned char)fBgr[i];
}


//-------------------------------------------------------------------
// effect
static void
effect(float *pBlu, float *pGrn, float *pRed, const size_t height, const size_t width)
{
    __m256 zeroPs = _mm256_set_ps(0, 0, 0, 0, 0, 0, 0, 0);
    float *b = pBlu;
    float *r = pRed;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width / 8; x++, b += 8, r += 8)
        {
            _mm256_store_ps(b, zeroPs); // B
                                        // G, skip
            _mm256_store_ps(r, zeroPs); // R
        }
    }
}


//-----------------------------------------------------------------
// AOS -> SOA
//
//    pBgr: b0,g0,r0, b1,g1,r1, b2,g2,r2, b3,g3,r3, b4,g4,r4, ...
// ->
//    pBlu:  b0, b1, b2, b3, b4, ...
//    pGrn:  g0, g1, g2, g3, g4, ...
//    pRed:  r0, r1, r2, r3, r4, ...
void
aos2soa(float *pBgr, float *pBlu, float *pGrn, float *pRed, const size_t length)
{
    __m128 *bgr = (__m128 *)pBgr;
    float *b = pBlu;
    float *g = pGrn;
    float *r = pRed;

    for (size_t i = 0; i < length; i += 24, b += 8, g += 8, r += 8)
    {
        __m256 m03 = _mm256_castps128_ps256(*bgr++);  // 下半分のロード
        __m256 m14 = _mm256_castps128_ps256(*bgr++);
        __m256 m25 = _mm256_castps128_ps256(*bgr++);
        m03 = _mm256_insertf128_ps(m03, *bgr++, 1);   // 上半分のロード
        m14 = _mm256_insertf128_ps(m14, *bgr++, 1);
        m25 = _mm256_insertf128_ps(m25, *bgr++, 1);

        __m256 bg = _mm256_shuffle_ps(m14, m25, _MM_SHUFFLE(2, 1, 3, 2)); // b と g の上部分
        __m256 gr = _mm256_shuffle_ps(m03, m14, _MM_SHUFFLE(1, 0, 2, 1)); // g と r の下部分
        __m256 bb = _mm256_shuffle_ps(m03, bg,  _MM_SHUFFLE(2, 0, 3, 0));
        __m256 gg = _mm256_shuffle_ps(gr, bg,   _MM_SHUFFLE(3, 1, 2, 0));
        __m256 rr = _mm256_shuffle_ps(gr, m25,  _MM_SHUFFLE(3, 0, 3, 1));

        _mm256_store_ps(b, bb);
        _mm256_store_ps(g, gg);
        _mm256_store_ps(r, rr);
    }
}

//-----------------------------------------------------------------
// SOA -> AOS
//
//    pBlu:  b0, b1, b2, b3, b4, ...
//    pGrn:  g0, g1, g2, g3, g4, ...
//    pRed:  r0, r1, r2, r3, r4, ...
// ->
//    pBgr: b0,g0,r0, b1,g1,r1, b2,g2,r2, b3,g3,r3, b4,g4,r4, ...
//
void
soa2aos(float *pBlu, float *pGrn, float *pRed, float *pBgr, const size_t length)
{
    __m128 *bgr = (__m128 *)pBgr;

    //1回に24ユニット、8x+8y+8z、x,y,z=float
    for (size_t i = 0; i < length; i += 24)
    {
        __m256 b = _mm256_load_ps(pBlu + (i / 3));
        __m256 g = _mm256_load_ps(pGrn + (i / 3));
        __m256 r = _mm256_load_ps(pRed + (i / 3));

        __m256 bg = _mm256_shuffle_ps(b, g, _MM_SHUFFLE(2, 0, 2, 0));
        __m256 gr = _mm256_shuffle_ps(g, r, _MM_SHUFFLE(3, 1, 3, 1));
        __m256 rb = _mm256_shuffle_ps(r, b, _MM_SHUFFLE(3, 1, 2, 0));

        __m256 r03 = _mm256_shuffle_ps(bg, rb, _MM_SHUFFLE(2, 0, 2, 0));
        __m256 r14 = _mm256_shuffle_ps(gr, bg, _MM_SHUFFLE(3, 1, 2, 0));
        __m256 r25 = _mm256_shuffle_ps(rb, gr, _MM_SHUFFLE(3, 1, 3, 1));

        *bgr++ = _mm256_castps256_ps128(r03);
        *bgr++ = _mm256_castps256_ps128(r14);
        *bgr++ = _mm256_castps256_ps128(r25);
        *bgr++ = _mm256_extractf128_ps(r03, 1);
        *bgr++ = _mm256_extractf128_ps(r14, 1);
        *bgr++ = _mm256_extractf128_ps(r25, 1);
    }
}


//-------------------------------------------------------------------
// main
int
main(int argc, char* argv[])
{
    float *fBgr = NULL, *fRed = NULL, *fGrn = NULL, *fBlu = NULL;

    try
    {
        if (argc != 3)
            throw "引数に以下を指定してください.\n" \
                            "  <入力ファイル>  <出力ファイル>";

        Cbmp bmp;
        bmp.loadFromFile(argv[1]);      // load bitmap

        // print image size
        fprintf(stdout, "ビットマップサイズ= %d x %d, %d/pixel\n",
            bmp.getWidth(), bmp.getHeight(), bmp.getBitsPerPixcel());

        if (bmp.getBitsPerPixcel() != 24)
            throw "24 ビット画像ファイルでない.";

        if ((bmp.getWidth() % 8) != 0)
            throw "横幅が8ピクセル単位でない.";

        // allocate memory
        size_t fSize = bmp.getAbsHeight()*bmp.getWidth()*sizeof(float)* 3;
        if ((fBgr = (float *)_mm_malloc(fSize, AVX_ALIGN)) == NULL)
            throw "_mm_malloc failed.";

        if ((fBlu = (float *)_mm_malloc(fSize / 3, AVX_ALIGN)) == NULL)
            throw "_mm_malloc failed.";

        if ((fGrn = (float *)_mm_malloc(fSize / 3, AVX_ALIGN)) == NULL)
            throw "_mm_malloc failed.";

        if ((fRed = (float *)_mm_malloc(fSize / 3, AVX_ALIGN)) == NULL)
            throw "_mm_malloc failed.";

        // byte -> float
        convB2F(bmp.getPbitmapBody(), fBgr, bmp.getAbsHeight()*bmp.getWidth() * 3);


        aos2soa(fBgr, fBlu, fGrn, fRed, bmp.getAbsHeight()*bmp.getWidth() * 3);

        effect(fBlu, fGrn, fRed, bmp.getAbsHeight(), bmp.getWidth());

        soa2aos(fBlu, fGrn, fRed, fBgr, bmp.getAbsHeight()*bmp.getWidth() * 3);


        // float -> byte
        convF2B(fBgr, bmp.getPbitmapBody(), bmp.getAbsHeight()*bmp.getWidth() * 3);

        bmp.saveToFile(argv[2]);                        // save bitmap
    }
    catch (char *str)
    {
        fprintf(stderr, "error: %s\n", str);
    }
    SP_MM_FREE(fBlu);
    SP_MM_FREE(fGrn);
    SP_MM_FREE(fRed);
    SP_MM_FREE(fBgr);

    return 0;
}
