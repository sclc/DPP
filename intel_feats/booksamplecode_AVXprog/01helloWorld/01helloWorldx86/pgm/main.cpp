//==========================================================================
// intの単純加算プログラム
//
// C:\>helloWorldx86
// 2 + 4 = 6
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>

int
main(void)
{
    int a=2, b=4, c ;

    _asm
    {
        mov     eax, a
        add     eax, b
        mov     c, eax
    }

    printf("%d + %d = %d\n", a, b, c) ;

    return 0;
}
