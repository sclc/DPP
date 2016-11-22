//==========================================================================
// __declspec定義
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>

int
main(void)
{
    __declspec(align(32)) double a[]={1.0, 2.0, 3.0, 4.0, 5.0};

    return 0;
}
