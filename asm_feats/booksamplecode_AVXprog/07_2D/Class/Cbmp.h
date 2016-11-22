//==========================================================================
//             _________________________
//            |                         |
//            |       mBmpFileHdr       | Bitmap File Header
//            |                         |
//            |_________________________|
// mPdib----->|                         | }
//            |    Bitmap Info Header   | }
//            |                         | }
//            |_________________________| }
// mPbitmap-->|                         | } -> DIB
//            |                         | }
//            |      image  data        | }
//            |        RGB(BGRA)        | }
//            |                         | }
//            |_________________________| }
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#ifndef __CBMPH__
#define __CBMPH__

#include "common.h"


//-------------------------------------------------------------------
class Cbmp
{
private:
    // ----- Methods -----
    int readHeader(FILE* fp);
    int readDib(FILE* fp);
    int writeHeader(FILE* fp);
    int writeDib(FILE* fp);


    // ----- Members -------------------------------
    bmpFileHdr  mBmpFileHdr;                            // ヘッダ

public:
    // ----- Constructor/Destructor ----------------
    Cbmp();                                             // コンストラクタ
    virtual ~Cbmp();                                    // デストラクタ

    // ----- Methods -----
    void loadFromFile(const char* bmpFName);
    int getWidth(void) const { return (mPdib==0 ? 0 : mPdib->biWidth); }
    int getHeight(void) const { return (mPdib==0 ? 0 : mPdib->biHeight); }
    int getAbsHeight(void) const { return (mPdib==0 ? 0 : mAbsHeight); }
    unsigned char* getPbitmapBody(void) const { return (unsigned char*)(mPbitmap==0 ? 0 : mPbitmap); }
    int getBitsPerPixcel(void) const { return mPdib->biBitCount; }
    void saveToFile(const char* bmpFName);


    // ----- Members -------------------------------
    pBmpInfoHdr mPdib;                                  // pointer to BITMAP(DIB)
    unsigned char* mPbitmap;                            // pointer to image
    int mDibSize;                                       // size of BITMAP(DIB)
    int mImgSize;                                       // size of image
    int mAlignedImgSize;                                // size of AVX aligned image
    int mRowPitch;                                      // row per bytes
    int mPixelPitch;                                    // pixel per bytes
    int mImageSize;                                     // size of image
    int mAbsHeight;                                     // absolute height
};
//-------------------------------------------------------------------

#endif  /* __CBMPH__ */
