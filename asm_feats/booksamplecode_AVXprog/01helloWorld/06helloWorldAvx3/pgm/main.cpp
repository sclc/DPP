//==========================================================================
// すべてを__m256にしてintrinsic命令数を削った。
// インラインアセンブラのcへの格納をvmovupsをvmovupsへ。
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

int
main(void)
{
    float __declspec(align(32)) a[]={1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float __declspec(align(32)) b[]={1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f, 9.0f};
    float __declspec(align(32)) c[9];

#ifdef  WIN32
    _asm
    {
        vmovaps ymm0, a
        vaddps  ymm1, ymm0, b
        vmovaps c, ymm1
    }
#else
    __m256 *pa=(__m256*)a;
    __m256 *pb=(__m256*)b;
    __m256 *pc=(__m256*)c;
    *pc = _mm256_add_ps(*pa, *pb);            // add
#endif

    printf(" source: (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    printf(" dest. : (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
    printf(" result: (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
    printf("\n");

    return 0;
}
