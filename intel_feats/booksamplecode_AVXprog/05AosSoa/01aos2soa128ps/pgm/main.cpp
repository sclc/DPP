//==========================================================================
// AOS
// http://software.intel.com/en-us/articles/3d-vector-normalization-using-256-bit-intel-advanced-vector-extensions-intel-avx/
// http://www.isus.jp/article/avx/3d-vector-normalization/
//
//
// C:\>aos2soa128ps
//
//
//     x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3
//  ->
//     x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3
//
//
// org: 01 02 03 11 12 13 21 22 23 31 32 33
// SOA: 01 11 21 31 02 12 22 32 03 13 23 33
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

static const size_t FLOAT_LEN=12;

//-----------------------------------------------------------------
//init
void
init(float *a, const size_t length)
{
    int i=0;

    a[i++]=01;    //x0
    a[i++]=02;    //y0
    a[i++]=03;    //z0

    a[i++]=11;    //x1
    a[i++]=12;    //y1
    a[i++]=13;    //z1

    a[i++]=21;    //x2
    a[i++]=22;    //y2
    a[i++]=23;    //z2

    a[i++]=31;    //x3
    a[i++]=32;    //y3
    a[i++]=33;    //z3
}

//-----------------------------------------------------------------
//prin Array
void
printArray(const char* prmt, const float *a, const size_t length)
{
    printf("%s", prmt);
    for(size_t i=0;i<length;i++)
        printf("%02.0f ", a[i]);
    printf("\n");
}

//-----------------------------------------------------------------
//prin Array
void
printHelp(void)
{
    puts("\n");
    puts("    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3");
    puts(" ->");
    puts("    x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3 ");
    puts("\n");
}

//-----------------------------------------------------------------
// AOS -> SOA
//
//    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3
// ->
//    x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3
//
void
aos2soa(float *xyz)
{
    __m128 x0y0z0x1 = _mm_load_ps(xyz+0);
    __m128 y1z1x2y2 = _mm_load_ps(xyz+4);
    __m128 z2x3y3z3 = _mm_load_ps(xyz+8);

    __m128 x2y2x3y3 = _mm_shuffle_ps(y1z1x2y2, z2x3y3z3, _MM_SHUFFLE( 2,1,3,2));
    __m128 y0z0y1z1 = _mm_shuffle_ps(x0y0z0x1, y1z1x2y2, _MM_SHUFFLE( 1,0,2,1));
    __m128 x        = _mm_shuffle_ps(x0y0z0x1, x2y2x3y3, _MM_SHUFFLE( 2,0,3,0));  // x0x1x2x3
    __m128 y        = _mm_shuffle_ps(y0z0y1z1, x2y2x3y3, _MM_SHUFFLE( 3,1,2,0));  // y0y1y2y3
    __m128 z        = _mm_shuffle_ps(y0z0y1z1, z2x3y3z3, _MM_SHUFFLE( 3,0,3,1));  // z0z1z2z3

    _mm_store_ps(xyz+0, x);
    _mm_store_ps(xyz+4, y);
    _mm_store_ps(xyz+8, z);
}

//-----------------------------------------------------------------
//main
int
main(void)
{
    float* a=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);

    init(a, FLOAT_LEN);

    printHelp();

    printArray("org: ", a, FLOAT_LEN);

    aos2soa(a);                             // AOS -> SOA

    printArray("SOA: ", a, FLOAT_LEN);

    _mm_free(a);

    return 0;
}
