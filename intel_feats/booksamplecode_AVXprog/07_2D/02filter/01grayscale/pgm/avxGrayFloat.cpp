//==========================================================================
// BGRA array -> float grayscale array
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>


//------------------------------------------------------------
//twoPixel
//
// input:
//          a(p0) = B0 G0 R0 G0(DWORD形式)
//          b(p1) = B1 G1 R1 G1(DWORD形式)
//
// return:
//          p0   p1   xx   xx,     xx=don't care(float形式)
//
#pragma warning(push)
#pragma warning(disable: 4700)
inline __m128
twoPixel(const __m128i a, const __m128i b)
{
    const __m256 grayK = _mm256_setr_ps(            // grayscale用の定数
                                0.114478f,0.586611f,0.298912f,0.000000f,
                                0.114478f,0.586611f,0.298912f,0.000000f);

    __m256i i256 = _mm256_insertf128_si256(i256, a, 0); //warning C4770, OK
                // i256 = B0 G0 R0 A0 B1 G1 R1 A1 (DWORD形式)
    i256 = _mm256_insertf128_si256(i256, b, 1);

                // s256 = B0 G0 R0 A0 B1 G1 R1 A1 (float形式)
    __m256 s256 = _mm256_cvtepi32_ps(i256);

                // s256 = B0 G0 R0 A0 B1 G1 R1 A1, 各要素に輝度係数を乗算
    s256 = _mm256_mul_ps(s256, grayK);

                // B0+G0 R0+A0 B0+G0 R0+A0 B1+G1 R1+A1 B1+G1 R1+A1
    s256 = _mm256_hadd_ps(s256, s256);

                // B0+G0+R0+A0 <-  <-  <-  B1+G1+R1+A1 <-  <-  <-
    s256 = _mm256_hadd_ps(s256, s256);

                // B0+G0+R0+A0  <-  <-  <-
    __m128 ps0 = _mm256_extractf128_ps(s256, 0);
                // B1+G1+R1+A1  <-  <-  <-
    __m128 ps1 = _mm256_extractf128_ps(s256, 1);
                // A1+R1+G1+B1, A0+R0+G0+B0, A1+R1+G1+B1, A0+R0+G0+B0
    ps0 = _mm_unpacklo_ps(ps0, ps1);

    return ps0;
}
#pragma warning(pop)

//------------------------------------------------------------
//rgba2gray
//
// in:       p0  p1  p2  p3,    BGRA (4bytes) x 4
// return:   g0  g1  g2  g3,    grayscale float形式 x 4
//
inline __m128d
rgba2gray(const __m128i in)
{
    const __m128i m128i_zero = _mm_set_epi32(0, 0, 0, 0);

    //...................
    // pixel 0,         ps0(in) = p0 p1 p2 p3,   BGRA (4bytes) x 4

    // pixel 1,         ps1 = p1 p1 p1 p1,   BGRA (4bytes) x 4
    __m128 *pps=(__m128 *)&in;
    __m128 ps1 = _mm_shuffle_ps(*pps, *pps, 0x55);


    // pixel 2,         ps2 = p2 p2 p2 p2,   BGRA (4bytes) x 4
    __m128 ps2 = _mm_shuffle_ps(*pps, *pps, 0xAA);


    // pixel 3,         ps3 = p3 p3 p3 p3,   BGRA (4bytes) x 4
    __m128 ps3 = _mm_shuffle_ps(*pps, *pps, 0xFF);


    //...................
    // pixel 0, byte -> word -> dword

                        // pdw0 = BBGG RRAA BBGG RRAA
    __m128i psw0 = _mm_unpacklo_epi8(in, m128i_zero);           //word
                        // psd0 = p0 = BBBB GGGG RRRR AAAA (DWORD形式)
    __m128i psd0 = _mm_unpacklo_epi16 (psw0, m128i_zero);       //dword

    // pixel 1, byte -> word -> dword
                        // psd1 = pixel1 = A R G B(DWORD形式)
    __m128i *p__m128i=(__m128i *)&ps1;
    __m128i psw1 = _mm_unpacklo_epi8(*p__m128i, m128i_zero);    //word
    __m128i psd1 = _mm_unpacklo_epi16 (psw1, m128i_zero);       //dword

    // pixel 2, byte -> word -> dword
                        // psd2 = pixel1 = A R G B(DWORD形式)
    p__m128i=(__m128i *)&ps2;
    __m128i psw2 = _mm_unpacklo_epi8(*p__m128i, m128i_zero);    //word
    __m128i psd2 = _mm_unpacklo_epi16 (psw2, m128i_zero);       //dword

    // pixel 3, byte -> word -> dword
                        // psd3 = pixel1 = A R G B(DWORD形式)
    p__m128i=(__m128i *)&ps3;
    __m128i psw3 = _mm_unpacklo_epi8(*p__m128i, m128i_zero);    //word
    __m128i psd3 = _mm_unpacklo_epi16 (psw3, m128i_zero);       //dword


    //...................
    __m128 ps01 = twoPixel(psd0, psd1);     // DWRD x4 -> glayscale float x 4
    __m128 ps23 = twoPixel(psd2, psd3);     // DWRD x4 -> glayscale float x 4


    //...................
                        //  ps0123= p0 p1 p2 p3 ,   glayscale float x 4
    __m128d ps0123 = _mm_unpacklo_pd(_mm_castps_pd(ps01), _mm_castps_pd(ps23));

    return ps0123;
}

//------------------------------------------------------------
//rgba8pixToGray
//
// in:     p0   p1   p2   p3   p4   p5   p6   p7,   p= BGRA形式 (4bytes) x 8
//
// return: G0   G1   G2   G3   G4   G5   G6   G7,   G=float x 8
//
#pragma warning(push)
#pragma warning(disable: 4700)
inline __m256d
rgba8pixToGray(const __m256i in)
{
                    // ps0 =  p0 p1 p2 p3,  BGRA (4bytes) x 4
    __m128i ps0 = _mm256_extractf128_si256(in, 0);  // p0 p1 p2 p3

                    // pd0123 = p0 p1 p2 p3 ,   grayscale float形式 x 4
    __m128d pd0123=rgba2gray(ps0);


                    // ps1 =  p4 p5 p6 p7,  BGRA (4bytes) x 4
    __m128i ps1 = _mm256_extractf128_si256(in, 1);  // p4 p5 p6 p7

                    // pd4567 = p4 p5 p6 p7 ,   grayscale float形式 x 4
    __m128d pd4567=rgba2gray(ps1);

                    // r = p0 p1 p2 p3, p4 p5 p6 p7, grayscale float形式 x 8(32bytes)
    __m256d r = _mm256_insertf128_pd(r, pd0123, 0); //warning C4770, OK
    r = _mm256_insertf128_pd(r, pd4567, 1);

    return r;
}
#pragma warning(pop)


//------------------------------------------------------------
//avxGray
//
// bgra(byte*4) -> graysclae(float array)
//
int
avxGray(const unsigned char* in, const float *out,
                        const size_t width, const size_t height)
{
    __m256i *pIn = (__m256i *)in;
    double *pDataf = (double *)out;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width / 8; x++)
        {
            __m256d r = rgba8pixToGray(*pIn++);
            _mm256_store_pd(pDataf, r);
            pDataf += 4;                               // 32/8=4
        }
    }
    return 0;
}
