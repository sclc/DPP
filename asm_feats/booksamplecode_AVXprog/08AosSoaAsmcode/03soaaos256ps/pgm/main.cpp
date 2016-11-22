//==========================================================================
// AOS
//
//
// C:\>soaaos256ps
//
//
// x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...
// ->
// x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3, ...
// ->
// x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...
//
//
// org: 01 02 03 11 12 13 21 22 23 31 32 33 41 42 43 51 52 53 61 62 63 71 72 73
// SOA: 01 11 21 31 41 51 61 71 02 12 22 32 42 52 62 72 03 13 23 33 43 53 63 73
// AOS: 01 02 03 11 12 13 21 22 23 31 32 33 41 42 43 51 52 53 61 62 63 71 72 73
//
// --------------
//
// org: 01 02 03 11 12 13 21 22 23 31 32 33 41 42 43 51 52 53 61 62 63 71 72 73
// SOA: 01 11 21 31 41 51 61 71 02 12 22 32 42 52 62 72 03 13 23 33 43 53 63 73
// AOS: 01 02 03 11 12 13 21 22 23 31 32 33 00 00 00 00 52 53 61 62 63 71 72 73
// ------------------
//
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include <immintrin.h>

static const size_t FLOAT_LEN=24;

extern "C" {
    void aos2soaAsm(float *xyz);
    void soa2aosAsm(float *xyz);
}

//-----------------------------------------------------------------
//init
void
init(float *a, const size_t length)
{
    int i=0;

    a[i++]=01;    //x0
    a[i++]=02;    //y0
    a[i++]=03;    //z0

    a[i++]=11;    //x1
    a[i++]=12;    //y1
    a[i++]=13;    //z1

    a[i++]=21;    //x2
    a[i++]=22;    //y2
    a[i++]=23;    //z2

    a[i++]=31;    //x3
    a[i++]=32;    //y3
    a[i++]=33;    //z3

    a[i++]=41;    //x4
    a[i++]=42;    //y4
    a[i++]=43;    //z4

    a[i++]=51;    //x5
    a[i++]=52;    //y5
    a[i++]=53;    //z5

    a[i++]=61;    //x6
    a[i++]=62;    //y6
    a[i++]=63;    //z6

    a[i++]=71;    //x7
    a[i++]=72;    //y7
    a[i++]=73;    //z7
}

//-----------------------------------------------------------------
//prin Array
void
printArray(const char* prmt, const float *a, const size_t length)
{
    printf("%s", prmt);
    for(size_t i=0;i<length;i++)
        printf("%02.0f ", a[i]);
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
    puts("    x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3, ... ");
    puts(" ->");
    puts("    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...");
    puts("\n");
}

//-----------------------------------------------------------------
//main
int
main(void)
{
    float* a=(float*)_mm_malloc(sizeof(float)*FLOAT_LEN, 32);

    init(a, FLOAT_LEN);

    printHelp();

    printArray("org: ", a, FLOAT_LEN);

    aos2soaAsm(a);                              // AOS -> SOA

    printArray("SOA: ", a, FLOAT_LEN);

    soa2aosAsm(a);                              // SOA -> AOS

    printArray("AOS: ", a, FLOAT_LEN);

    _mm_free(a);

    return 0;
}
