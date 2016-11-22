//==========================================================================
// fir, �W���̒�����K_ALIGN�ɑ����ĂȂ��ꍇ�A��������
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
            throw "<�g�`�t�@�C����> <�W���t�@�C����> ���w�肵�Ă�������.";

        dLength = countLines(argv[1]);                  // �f�[�^�J�E���g
        kLength = countLines(argv[2]);                  // �W���J�E���g

        size_t dAlignedLength = dLength;
        data = avxFloatAlloc(&dAlignedLength);          // �f�[�^�p���������t
        fprintf(stderr, "�f�[�^��=%d, ������=%d\n",
            dLength, dAlignedLength);

        size_t kAlignedLength = kLength;
        k = avxFloatAlloc(&kAlignedLength);             // �W���p���������t
        fprintf(stderr, "�W����=%d, ������=%d\n",
            kLength, kAlignedLength);

        readData(argv[1], data, dLength);               // �f�[�^�Ǎ�
        readData(argv[2], k, kLength);                  // �W���Ǎ�

        size_t zAlignedLength = dAlignedLength;
        z = avxFloatAlloc(&zAlignedLength);

        //��������A�x���`�}�[�N�J�n ----------------------------------
        spCpfm.getTime();
        // fir���s
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
        //�����܂ŁA�x���`�}�[�N --------------------------------------
        spCpfm.getTime();

        //�x���`�}�[�N�\�� --------------------------------------------
        spCpfm.printTime();

        for (size_t n = 0; n < dLength; n++)                // ���ʏo��
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
