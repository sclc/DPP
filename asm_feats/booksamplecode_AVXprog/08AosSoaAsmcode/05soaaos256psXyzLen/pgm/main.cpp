//==========================================================================
// AOS length
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

extern "C" {
    void aos2soaAsm(float *xyz, float *px, float *py, float *pz, size_t length);
    void soa2aosAsm(float *px, float *py, float *pz, float *xyz, size_t length);
}

static const size_t FLOAT_LEN=1536;

//-----------------------------------------------------------------
//init
void
init(float *a, const size_t length)
{
    for(int i=0; i< length/3; i++)
    {
        a[i * 3 + 0] = (float)0x10 * i + 1;
        a[i * 3 + 1] = (float)0x10 * i + 2;
        a[i * 3 + 2] = (float)0x10 * i + 3;
    }
}

//-----------------------------------------------------------------
//prin Array
void
printArray(const char* prmt, const float *a, const size_t length)
{
    printf("%s", prmt);
    for(size_t i=0;i<length;i++)
        printf("%02X ", (unsigned int)a[i]);
    printf("\n");
}

//-----------------------------------------------------------------
//prin Array
void
printHelp(void)
{
    puts("\n");
    puts("    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...");
    puts(" ->");
    puts("    x0,x1,x2,x3, ... ");
    puts("    y0,y1,y2,y3, ... ");
    puts("    z0,z1,z2,z3, ... ");
    puts(" ->");
    puts("    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...");
    puts("\n");
}

//-----------------------------------------------------------------
// AOS -> SOA
//
//    xyz: x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, x4,y4,z4, ...
// ->
//    px:  x0, x1, x2, x3, z4, ...
//    py:  y0, y1, y2, y3, z4, ...
//    pz:  z0, z1, z2, z3, z4, ...
//
void
aos2soa(float *xyz, float *px, float *py, float *pz, size_t length)
{
    __m128 *m = (__m128 *)xyz;
    float *tmpx = px;
    float *tmpy = py;
    float *tmpz = pz;

    for(size_t i=0; i<length; i+=24, tmpx+=8, tmpy+=8, tmpz+=8)
    {
        __m256 m03 = _mm256_castps128_ps256(*m++);  // 下半分のロード
        __m256 m14 = _mm256_castps128_ps256(*m++);
        __m256 m25 = _mm256_castps128_ps256(*m++);
        m03 = _mm256_insertf128_ps(m03, *m++, 1);   // 上半分のロード
        m14 = _mm256_insertf128_ps(m14, *m++, 1);
        m25 = _mm256_insertf128_ps(m25, *m++, 1);

        __m256 xy = _mm256_shuffle_ps(m14, m25, _MM_SHUFFLE( 2,1,3,2)); // x と y の上部分
        __m256 yz = _mm256_shuffle_ps(m03, m14, _MM_SHUFFLE( 1,0,2,1)); // y と z の下部分
        __m256 x  = _mm256_shuffle_ps(m03, xy , _MM_SHUFFLE( 2,0,3,0));
        __m256 y  = _mm256_shuffle_ps(yz , xy , _MM_SHUFFLE( 3,1,2,0));
        __m256 z  = _mm256_shuffle_ps(yz , m25, _MM_SHUFFLE( 3,0,3,1));

        _mm256_store_ps(tmpx, x);
        _mm256_store_ps(tmpy, y);
        _mm256_store_ps(tmpz, z);
    }
}


//-----------------------------------------------------------------
// SOA -> AOS
//
//    px:  x0, x1, x2, x3, z4, ...
//    py:  y0, y1, y2, y3, z4, ...
//    pz:  z0, z1, z2, z3, z4, ...
// ->
//    xyz: x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, x4,y4,z4, ...
//
void
soa2aos(float *px, float *py, float *pz, float *xyz, size_t length)
{
    __m128 *m = (__m128 *)xyz;

    //1回に24ユニット、8x+8y+8z、x,y,z=float
    for(size_t i=0; i<length; i+=24)
    {
        __m256 x = _mm256_load_ps(px+(i/3));
        __m256 y = _mm256_load_ps(py+(i/3));
        __m256 z = _mm256_load_ps(pz+(i/3));

        __m256 rxy = _mm256_shuffle_ps(x, y, _MM_SHUFFLE(2, 0, 2, 0));
        __m256 ryz = _mm256_shuffle_ps(y, z, _MM_SHUFFLE(3, 1, 3, 1));
        __m256 rzx = _mm256_shuffle_ps(z, x, _MM_SHUFFLE(3, 1, 2, 0));

        __m256 r03 = _mm256_shuffle_ps(rxy, rzx, _MM_SHUFFLE(2, 0, 2, 0));
        __m256 r14 = _mm256_shuffle_ps(ryz, rxy, _MM_SHUFFLE(3, 1, 2, 0));
        __m256 r25 = _mm256_shuffle_ps(rzx, ryz, _MM_SHUFFLE(3, 1, 3, 1));

        *m++ = _mm256_castps256_ps128(r03);
        *m++ = _mm256_castps256_ps128(r14);
        *m++ = _mm256_castps256_ps128(r25);
        *m++ = _mm256_extractf128_ps(r03, 1);
        *m++ = _mm256_extractf128_ps(r14, 1);
        *m++ = _mm256_extractf128_ps(r25, 1);
    }
}

//-----------------------------------------------------------------
//main
int
main(void)
{
    if(FLOAT_LEN%24!=0)
        return -1;

    float* a=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);
    float* s=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);
    float* x=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN/3, 32);
    float* y=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN/3, 32);
    float* z=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN/3, 32);

    init(a, FLOAT_LEN);

    aos2soa(a, x, y, z, FLOAT_LEN);             // AOS -> SOA
    soa2aos(x, y, z, s, FLOAT_LEN);             // SOA -> AOS

    for(int i=0; i<FLOAT_LEN; i++)              // error check
    if (a[i] != s[i])
    {
        fprintf(stderr, "error at %d\n",i);
        break;
    }

    aos2soaAsm(a, x, y, z, FLOAT_LEN);          // AOS -> SOA
    soa2aosAsm(x, y, z, s, FLOAT_LEN);          // SOA -> AOS
    for (int i = 0; i<FLOAT_LEN; i++)           // error check
    if (a[i] != s[i])
    {
        fprintf(stderr, "error at %d\n", i);
        break;
    }

    _mm_free(a);
    _mm_free(s);
    _mm_free(x);
    _mm_free(y);
    _mm_free(z);

    return 0;
}
