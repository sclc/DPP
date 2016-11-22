//==========================================================================
// fir, 係数の長さがK_ALIGNに揃ってない場合、調整する
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//==========================================================================
#include <stdio.h>
#include "common.h"
#include "utils.h"
#include "Cpfm.h"
#include <immintrin.h>


//--------------------------------------------------------------------------
//main
int
main(int argc, char* argv[])
{
    float *data = NULL, *k = NULL, *z = NULL;
    size_t dLength, kLength;
    Cpfm spCpfm;

    try
    {
        if (argc != 3)
            throw "<波形ファイル名> <係数ファイル名> を指定してください.";

        dLength = countLines(argv[1]);                  // データカウント
        kLength = countLines(argv[2]);                  // 係数カウント

        size_t dAlignedLength = dLength;
        data = avxFloatAlloc(&dAlignedLength);          // データ用メモリ割付
        fprintf(stderr, "データ長=%d, 調整後=%d\n",
            dLength, dAlignedLength);

        size_t kAlignedLength = kLength;
        k = avxFloatAlloc(&kAlignedLength);             // 係数用メモリ割付
        fprintf(stderr, "係数長=%d, 調整後=%d\n",
            kLength, kAlignedLength);

        readData(argv[1], data, dLength);               // データ読込
        readData(argv[2], k, kLength);                  // 係数読込

        size_t zAlignedLength = dAlignedLength;
        z = avxFloatAlloc(&zAlignedLength);

        //ここから、ベンチマーク開始 ----------------------------------
        spCpfm.getTime();
        // fir実行
        for (size_t n = 0; n < dAlignedLength - kAlignedLength; n++)
        {
            __m256 sum = _mm256_setzero_ps();
            for (size_t m = 0; m < kAlignedLength; m += 8)
            {
                __m256 a = _mm256_loadu_ps(k + m);          // k0, k1, k2, k3, k4, k5, k6, k7
                __m256 b = _mm256_loadu_ps(data + n + m);   // d0, d1, d2, d3, d4, d5, d6, d7
                __m256 mul = _mm256_mul_ps(a, b);           // z0, z1, z2, z3, z4, z5, z6, z7 (z=k*d)
                sum = _mm256_add_ps(sum, mul);              // z += (k * d)  [8vector]
            }
                // d0+d1, d2+d3, d0+d1, d2+d3, d4+d5, d6+d7, d4+d5, d6+d7
            sum = _mm256_hadd_ps(sum, sum);
                // d0+d1+d2+d3, <-,  <-,  <-, d4+d5+d6+d7,  <-,  <-,  <-
            sum = _mm256_hadd_ps(sum, sum);
            float tmp = sum.m256_f32[0] + sum.m256_f32[4];
            z[n] = min(32767.0f, max(tmp, -32768.0f));
        }
        //ここまで、ベンチマーク --------------------------------------
        spCpfm.getTime();

        //ベンチマーク表示 --------------------------------------------
        spCpfm.printTime();

        for (size_t n = 0; n < dLength; n++)                // 結果出力
            printf("%12.4f\n", z[n]);
    }
    catch (char *str)
    {
        fprintf(stderr, "error: %s\n", str);
    }
    SP_MM_FREE(data);
    SP_MM_FREE(k);
    SP_MM_FREE(z);

    return 0;
}
