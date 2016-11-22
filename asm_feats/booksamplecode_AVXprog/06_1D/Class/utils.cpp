//==========================================================================
// file i/o
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <immintrin.h>

//--------------------------------------------------------------------------
//countLines
size_t
countLines(const char* fname)
{
    FILE  *fp;
    float data;

    if ((fp = fopen(fname, "rt")) == NULL)
        throw "入力ファイルをオープンできません.";

    int count = 0;
    while (fscanf(fp, "%f", &data) == 1)
        count++;

    fclose(fp);

    if (count <= 0)
        throw "入力ファイルの読み込み失敗.";

    return count;
}

//--------------------------------------------------------------------------
//readData
void
readData(const char* fname, float data[], const size_t length)
{
    FILE *fp;

    if ((fp = fopen(fname, "rt")) == NULL)
        throw "入力ファイルをオープンできません.";

    for (size_t i = 0; i < length; i++)
    if (fscanf(fp, "%f", &data[i]) != 1)
        throw "入力ファイルの読み込み失敗.";

    fclose(fp);
}

//--------------------------------------------------------------------------
//short -> float
void
convS2F(const short sData[], float fData[], const size_t length)
{
    for (size_t i = 0; i < length; i++)
        fData[i] = (float)sData[i];
}

//--------------------------------------------------------------------------
//float -> short
void
convF2S(const float fData[], short sData[], const size_t length)
{
    for (size_t i = 0; i < length; i++)
        sData[i] = (short)fData[i];
}

//--------------------------------------------------------------------------
// allocate AVX aligned memory
float*
avxFloatAlloc(size_t *length)
{
    float *fData = NULL;

    size_t alignedLength = *length;

    alignedLength = (alignedLength%AVX_FLOAT_ALIGN == 0) ?    // AVX alignment
    alignedLength :
                  ((int)((alignedLength / AVX_FLOAT_ALIGN) + 1)*AVX_FLOAT_ALIGN);

    if ((fData = (float*)_mm_malloc(alignedLength*sizeof(float), AVX_ALIGN)) == NULL)
        throw "_mm_malloc失敗.";

    for (int i = *length - 1; i < alignedLength; i++)
        fData[i] = 0.0f;

    *length = alignedLength;

    return fData;
}
