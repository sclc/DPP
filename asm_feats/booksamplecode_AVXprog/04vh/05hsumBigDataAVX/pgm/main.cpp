//==========================================================================
//水平演算、長いデータ
//
// C:\>hsumBigDataAVX
// AVX sum = 4193.7920
// C++ sum = 4193.7920
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

#define DATA_LENGTH         8192

int
main(void)
{
    float* in=(float*)_mm_malloc(sizeof(float)*DATA_LENGTH, 32);
    __m256 *pIn = (__m256 *)in;

    for(size_t i=0; i<DATA_LENGTH; i++)         //init
        in[i]=(float)i*0.000125f;

    __m256 sum = _mm256_setzero_ps();
    for(size_t i=0; i<DATA_LENGTH/(sizeof(__m256)/sizeof(float)); i++)
        sum = _mm256_add_ps(sum, *pIn++);       // sd0, sd1, sd2, sd3,
                                                //      sd4, sd5, sd6, sd7


    sum = _mm256_hadd_ps(sum, sum);             // sd0+sd1,  sd2+d3,  sd0+d1,  sd2+d3,
                                                //          sd4+d5, sd6+d7, sd4+d5, sd6+d7
    sum = _mm256_hadd_ps(sum, sum);             // sd0+sd1+sd2+sd3,  ←,  ←,  ←,
                                                //          sd4+sd5+sd6+sd7,  ←,  ←,  ←

    float tmp=sum.m256_f32[0]+sum.m256_f32[4];  // sd0+sd1+sd2+sd3+sd4+sd5+sd6+sd7
    printf("AVX sum = %.4f\n", tmp);

    tmp = 0;                                    // C++
    for (size_t i = 0; i<DATA_LENGTH; i++)
        tmp += in[i];
    printf("C++ sum = %.4f\n", tmp);

    _mm_free(in);

    return 0;
}
