//==========================================================================
// utils
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================

#ifndef UTILSH__
#define UTILSH__

size_t countLines(const char* fname);
void readData(const char* fname, float data[], const size_t length);
void convS2F(const short sData[], float fData[], const size_t length);
void convF2S(const float fData[], short sData[], const size_t length);
float* avxFloatAlloc(size_t *length);

//---------------------------------------------------------------------------
#endif  /* UTILSH__ */
