//==========================================================================
// common.h
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================

#ifndef COMMONH__
#define COMMONH__

//--------------------------------------------------------------------------
//  �}�N���̐錾
#define SP_FREE(p)          if(p) {free(p);     p=NULL;}
#define SP_MM_FREE(p)       if(p) {_mm_free(p); p=NULL;}

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif


//--------------------------------------------------------------------------
// �萔��`
#define AVX_ALIGN           32
#define AVX_FLOAT_ALIGN     (32/sizeof(float))
#define SSE_ALIGN           16

//---------------------------------------------------------------------------
#endif  /* COMMONH__ */
