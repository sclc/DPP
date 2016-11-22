//==========================================================================
// mm_malloc
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

//-----------------------------------------------------------------
//main
int
main(void)
{
    float* a=(float*)_mm_malloc(sizeof(float)*1024, 32);

    a[1]=10.0f;

    _mm_free(a);

    return 0;
}
