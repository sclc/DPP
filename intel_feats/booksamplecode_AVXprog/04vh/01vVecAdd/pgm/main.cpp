//==========================================================================
// vector 垂直加算
//
// 配列の垂直加算
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

#define FLOAT_LEN    262144

//-----------------------------------------------------------------
// verical add by AVX instructions
void
vVecAddAvx(const size_t length, const float* a, const float* b, float* c)
{
    __m256 *pA=(__m256 *)a;
    __m256 *pB=(__m256 *)b;

    for(size_t i=0;i<length/8; i++, pA++, pB++)
    {
        __m256 y = _mm256_add_ps(*pA, *pB);
        _mm256_store_ps(&c[i*8], y);
    }
}

//-----------------------------------------------------------------
// verical add by C++
void
vVecAddfCpp(const size_t length, const float* a, const float* b, float* c)
{
    for(size_t i=0;i<length; i++)
        c[i]=a[i]+b[i];
}

//-----------------------------------------------------------------
// verify
void
verifyVVec(const size_t length, const float* c, float* r)
{
    for(size_t i=0;i<FLOAT_LEN; i++)
        if(c[i]!=r[i])
            printf("c[%d]=%.2f, c[%d]=%.2f\n", i, c[i], i, r[i]);
}

//-----------------------------------------------------------------
// init
void
initData(const size_t length, float* a, float* b)
{
    for(size_t i=0;i<length ;i++)
    {
        a[i]=(float)i*1024.0f;
        b[i]=((float)i*1024.0f)+1.0f;
    }
}

//-----------------------------------------------------------------
// main
int
main(void)
{
    float* a=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);
    float* b=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);
    float* c=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);
    float* r=new float[FLOAT_LEN];

    initData(FLOAT_LEN, a, b);

    vVecAddAvx(FLOAT_LEN, a, b, c);

    vVecAddfCpp(FLOAT_LEN, a, b, r);

    verifyVVec(FLOAT_LEN, c, r);

    _mm_free(a);
    _mm_free(b);
    _mm_free(c);
    delete[] r;

    return 0;
}
