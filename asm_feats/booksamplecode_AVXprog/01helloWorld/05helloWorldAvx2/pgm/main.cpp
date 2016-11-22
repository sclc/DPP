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
    __m256 a={1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    __m256 b={1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f};
    __m256 c;

#ifdef  WIN32
    _asm
    {
        vmovaps ymm0, a
        vaddps  ymm1, ymm0, b
        vmovaps c, ymm1
    }
#else
    c = _mm256_add_ps(a, b);            // add
#endif

    printf(" source: (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        a.m256_f32[0], a.m256_f32[1], a.m256_f32[2], a.m256_f32[3],
            a.m256_f32[4], a.m256_f32[5], a.m256_f32[6], a.m256_f32[7]);
    printf(" dest. : (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        b.m256_f32[0], b.m256_f32[1], b.m256_f32[2], b.m256_f32[3],
            b.m256_f32[4], b.m256_f32[5], b.m256_f32[6], b.m256_f32[7]);
    printf(" result: (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        c.m256_f32[0], c.m256_f32[1], c.m256_f32[2], c.m256_f32[3],
            c.m256_f32[4], c.m256_f32[5], c.m256_f32[6], c.m256_f32[7]);
    printf("\n");

    return 0;
}
