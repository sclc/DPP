//==========================================================================
//  bitmap structs
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#ifndef __BITMAPSTRUCT__
#define __BITMAPSTRUCT__


#pragma pack(push, 1)

typedef struct
{
    unsigned short  bfType;
    unsigned int    bfSize;
    unsigned short  bfReserved1;
    unsigned short  bfReserved2;
    unsigned int    bfOffBits;
}
bmpFileHdr, *pBmpFileHdr;

typedef struct
{
    unsigned int    biSize;
    int             biWidth;
    int             biHeight;
    unsigned short  biPlanes;
    unsigned short  biBitCount;
    unsigned int    biCompression;
    unsigned int    biSizeImage;
    int             biXPelsPerMeter;
    int             biYPelsPerMeter;
    unsigned int    biClrUsed;
    unsigned int    biClrImportant;
}
bmpInfoHdr, *pBmpInfoHdr;

#pragma pack(pop)

#endif // __BITMAPSTRUCT__
