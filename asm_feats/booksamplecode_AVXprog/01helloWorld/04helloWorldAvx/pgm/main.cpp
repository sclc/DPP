//==========================================================================
// floatの単純加算プログラム、AVX命令を使用するため、1回に256ビット
// の処理が可能になる。
//
// ヘッダ
//     AVXを使用するためimmintrin.hを使用した。x32でも問題ないが
//     以降は、x64のみを対象として説明する。
//
// C:\>helloWorldAvx
//  source: (  1.0,   2.0,   3.0,   4.0,   5.0,   6.0,   7.0,   8.0)
//  dest. : (  1.1,   2.1,   3.1,   4.1,   5.1,   6.1,   7.1,   8.1)
//  result: (  2.1,   4.1,   6.1,   8.1,  10.1,  12.1,  14.1,  16.1)
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
    float  c[8];

#ifdef  WIN32
    _asm
    {
        vmovaps ymm0, a
        vaddps  ymm1, ymm0, b
        vmovups c, ymm1
    }
#else
    __m256 ps = _mm256_add_ps(a, b);        // add
    _mm256_storeu_ps(c, ps);                // store
#endif

    printf(" source: (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        a.m256_f32[0], a.m256_f32[1], a.m256_f32[2], a.m256_f32[3],
            a.m256_f32[4], a.m256_f32[5], a.m256_f32[6], a.m256_f32[7]);
    printf(" dest. : (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        b.m256_f32[0], b.m256_f32[1], b.m256_f32[2], b.m256_f32[3],
            b.m256_f32[4], b.m256_f32[5], b.m256_f32[6], b.m256_f32[7]);
    printf(" result: (%5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f, %5.1f)\n",
        c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
    printf("\n");

    return 0;
}
