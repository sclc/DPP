//==========================================================================
// SSE、XMMレジスタ、インラインアセンブラ
//
// x64はインラインアセンブラを許可しないので、x32でビルド。
//
// C:\>helloWorld128
//  source: (  1.0,   2.0,   3.0,   4.0)
//  dest. : (  1.1,   2.1,   3.1,   4.1)
//  result: (  2.1,   4.1,   6.1,   8.1)
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>

int
main(void)
{
    float a[]={1.0f, 2.0f, 3.0f, 4.0f};
    float b[]={1.1f, 2.1f, 3.1f, 4.1f};
    float c[4];

    __asm
    {
        movups      xmm0, a
        movups      xmm1, b
        addps       xmm0, xmm1
        movups      c,  xmm0
    }

    printf(" source: (%5.1f, %5.1f, %5.1f, %5.1f)\n", a[0], a[1], a[2], a[3]);
    printf(" dest. : (%5.1f, %5.1f, %5.1f, %5.1f)\n", b[0], b[1], b[2], b[3]);
    printf(" result: (%5.1f, %5.1f, %5.1f, %5.1f)\n", c[0], c[1], c[2], c[3]);

    return 0;
}
