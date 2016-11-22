//==========================================================================
// floatの単純加算プログラム
//
// x64はインラインアセンブラを許可しないので、instrinsicを使用し
// x32/x64両方で記述できるようにした。
//
//
// ヘッダ
//     MSDNのサイトに各intrinsicごとに必要なヘッダファイルが明記
//     されていえる。本書ではAVX命令を使用するためimmintrin.hで
//     構わないが、本プログラムはSSE使用なので、xmmintrin.hを使用
//     した。
//
//     mmintrin.h      // for MMX
//     xmmintrin.h     // for SSE  (Pentium3)
//     emmintrin.h     // for SSE2 (Pentium4,AMD64アーキテクチャ)
//     pmmintrin.h     // for SSE3 (Pentium4のPrescottコア,AMD AM2+ クアッドコア
//     immintrin.h     // for AVX
//
// 動作：x32/x64共通
//
// C:\>helloWorld128Intrin
//
//  source: (  1.0,   2.0,   3.0,   4.0)
//  dest. : (  1.1,   2.1,   3.1,   4.1)
//  result: (  2.1,   4.1,   6.1,   8.1)
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <xmmintrin.h>

int
main(void)
{
    __m128 a={1.0f, 2.0f, 3.0f, 4.0f};
    __m128 b={1.1f, 2.1f, 3.1f, 4.1f};
    float  c[4];

    __m128 ps = _mm_add_ps(a, b);         // add

    _mm_storeu_ps(c, ps);                 // store


    printf(" source: (%5.1f, %5.1f, %5.1f, %5.1f)\n",
        a.m128_f32[0], a.m128_f32[1], a.m128_f32[2], a.m128_f32[3]);
    printf(" dest. : (%5.1f, %5.1f, %5.1f, %5.1f)\n",
        b.m128_f32[0], b.m128_f32[1], b.m128_f32[2], b.m128_f32[3]);
    printf(" result: (%5.1f, %5.1f, %5.1f, %5.1f)\n",
        c[0], c[1], c[2], c[3]);

    return 0;
}
