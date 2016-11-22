//===================================================================
// Cbmp.cpp
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                               Hiro KITAYAMA
//
//===================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bitmapStruct.h"
#include "Cbmp.h"
#include <immintrin.h>


//-------------------------------------------------------------------
// コンストラクタ
Cbmp::Cbmp()
: mPdib(NULL), mPbitmap(NULL), mDibSize(0), mAlignedImgSize(0),
mImgSize(0), mRowPitch(0), mPixelPitch(0), mImageSize(0), mAbsHeight(0)
{
    assert(sizeof(char) == 1);
    assert(sizeof(short) == 2);
    assert(sizeof(int) == 4);
}


//-------------------------------------------------------------------
// デストラクタ
Cbmp::~Cbmp()
{
    SP_FREE(mPdib);                                 // free bmp
    SP_MM_FREE(mPbitmap);                           // free image body
}


//================ vvvvvv private vvvvvv ============================

//-------------------------------------------------------------------
// read bitmap file header
//
// return true :0
//        false:!0=error #
int
Cbmp::readHeader(FILE* fp)
{
    if (fread(&mBmpFileHdr, sizeof(bmpFileHdr), 1, fp) != 1)
        return -1;

    if (mBmpFileHdr.bfType != 'B' + 'M' * 256)
        return -2;                                  // not bitmap file

    return 0;
}


//-------------------------------------------------------------------
// read bitmap body
int
Cbmp::readDib(FILE* fp)
{
    mPdib = (bmpInfoHdr *)malloc(sizeof(bmpInfoHdr));   // alloc dib info. header
    if (mPdib == NULL)
        return -1;

    if (fread(mPdib, sizeof(bmpInfoHdr), 1, fp) != 1)   // read  dib info. header
        return -2;

    if (mPdib->biBitCount != 24 && mPdib->biBitCount != 32)
        return -3;                                      // no 24/32bpp

    mAlignedImgSize = (mImgSize%AVX_ALIGN == 0) ?       // AVX alignment
    mImgSize : ((int)(mImgSize / AVX_ALIGN)*AVX_ALIGN);
    if ((mPbitmap = (unsigned char*)_mm_malloc(mAlignedImgSize, AVX_ALIGN)) == NULL)
        return -4;

    if (fread(mPbitmap, mImgSize, 1, fp) != 1)
        return -1;

    return 0;
}


//-------------------------------------------------------------------
// write bitmap file header
int
Cbmp::writeHeader(FILE* fp)
{
    if (fwrite(&mBmpFileHdr, sizeof(bmpFileHdr), 1, fp) != 1)
        return -1;

    return 0;
}


//-------------------------------------------------------------------
// write bitmap file body
int
Cbmp::writeDib(FILE* fp)
{
    if (fwrite(mPdib, sizeof(bmpInfoHdr), 1, fp) != 1)// write dib info header
        return -1;

    if (fwrite(mPbitmap, mImgSize, 1, fp) != 1)       // write image body
        return -2;

    return 0;
}

//================ ^^^^^^ private ^^^^^^ ====================================



//-------------------------------------------------------------------
// load bitmap image from file
void
Cbmp::loadFromFile(const char* bmpFName)
{
    FILE* fp;

    SP_FREE(mPdib);                                 // delete image
    SP_MM_FREE(mPbitmap);                           // free image body

    if ((fp = fopen(bmpFName, "rb")) == 0)          // open bitmap file
        throw "input file open failed.";

    if (readHeader(fp) != 0)                        // read file header
    {
        fclose(fp);
        throw "failed to read bitmap file header.";
    }

    mDibSize = mBmpFileHdr.bfSize - sizeof(bmpFileHdr); // size of dib
    mImgSize = mDibSize - sizeof(bmpInfoHdr);       // body size

    if (readDib(fp) != 0)                           // read dib
    {
        SP_FREE(mPdib);
        SP_MM_FREE(mPbitmap);
        fclose(fp);
        throw "failed to read bitmap file body.";
    }
    fclose(fp);                                     // close bitmap file

    mPixelPitch = mPdib->biBitCount / 8;

    mRowPitch = (mPdib->biWidth*mPixelPitch);       // clac. row pitch by bytes
    if (mRowPitch % 4 != 0)
        mRowPitch += (4 - (mRowPitch % 4));

    mAbsHeight = mPdib->biHeight > 0 ? mPdib->biHeight : -(mPdib->biHeight);   //abs
    mImageSize = mRowPitch*mAbsHeight;
}


//-------------------------------------------------------------------
// save to bitmap file
void
Cbmp::saveToFile(const char* bmpFName)
{
    FILE* fp;

    if ((fp = fopen(bmpFName, "wb")) != 0)              // open file
    {
        if (writeHeader(fp) == 0)                       // write header
        {
            if (writeDib(fp) != 0)                      // write dib
                throw "output file, write dib failed.";
        }
        else
            throw "output file, write failed.";
    }
    else
        throw "output file, open failed.";

    fclose(fp);
}
