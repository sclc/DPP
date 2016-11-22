_TEXT   segment

        public aos2soaAsm
        align  16

;*******************************************************************
;xmm0=x0y0z0x1;
;xmm1=y1z1x2y2;
;xmm2=z2x3y3z3;
;
;xmm3=x2y2x3y3;
;xmm4=y0z0y1z1;
;
;xmm5=x;
;xmm6=y;
;xmm7=z;
;
;//-----------------------------------------------------------------
;// AOS -> SOA
;//
;//    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...
;// ->
;//    x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3, ...
;//
;void
;aos2soa(float *xyz)
;{
;    __m128 *m = (__m128 *)xyz;
;
;    __m256 m03 = _mm256_castps128_ps256(m[0]);  // 下半分のロード
;    __m256 m14 = _mm256_castps128_ps256(m[1]);
;    __m256 m25 = _mm256_castps128_ps256(m[2]);
;    m03 = _mm256_insertf128_ps(m03, m[3], 1);   // 上半分のロード
;    m14 = _mm256_insertf128_ps(m14, m[4], 1);
;    m25 = _mm256_insertf128_ps(m25, m[5], 1);
;
;    __m256 xy = _mm256_shuffle_ps(m14, m25, _MM_SHUFFLE( 2,1,3,2)); // x と y の上部分
;    __m256 yz = _mm256_shuffle_ps(m03, m14, _MM_SHUFFLE( 1,0,2,1)); // y と z の下部分
;    __m256 x  = _mm256_shuffle_ps(m03, xy , _MM_SHUFFLE( 2,0,3,0));
;    __m256 y  = _mm256_shuffle_ps(yz , xy , _MM_SHUFFLE( 3,1,2,0));
;    __m256 z  = _mm256_shuffle_ps(yz , m25, _MM_SHUFFLE( 3,0,3,1));
;
;    _mm256_store_ps(xyz+0,  x);
;    _mm256_store_ps(xyz+8,  y);
;    _mm256_store_ps(xyz+16, z);
;}
;*******************************************************************

aos2soaAsm proc

        vmovups ymm0, YMMWORD PTR [rcx+(16*0)]  ; 下半分のロード
        vmovups ymm1, YMMWORD PTR [rcx+(16*1)]
        vmovups ymm2, YMMWORD PTR [rcx+(16*2)]

                                                ; 上半分のロード
        vinsertf128 ymm0, ymm0, XMMWORD PTR [rcx+(16*3)], 1
        vinsertf128 ymm1, ymm1, XMMWORD PTR [rcx+(16*4)], 1
        vinsertf128 ymm2, ymm2, XMMWORD PTR [rcx+(16*5)], 1

        vshufps ymm3, ymm1, ymm2, 10011110b     ; (2,1,3,2) ; x と y の上部分
        vshufps ymm4, ymm0, ymm1, 01001001b     ; (1,0,2,1) ; y と z の下部分
        vshufps ymm0, ymm0, ymm3, 10001100b     ; (2,0,3,0)
        vshufps ymm1, ymm4, ymm3, 11011000b     ; (3,1,2,0)
        vshufps ymm2, ymm4, ymm2, 11001101b     ; (3,0,3,1)

        vmovups YMMWORD PTR [rcx+(4*0)], ymm0
        vmovups YMMWORD PTR [rcx+(4*8)], ymm1
        vmovups YMMWORD PTR [rcx+(4*16)], ymm2

        ret

aos2soaAsm endp





        public soa2aosAsm
        align  16

;///-----------------------------------------------------------------
;// SOA -> AOS
;//
;//    x0,x1,x2,x3, y0,y1,y2,y3, z0,z1,z2,z3, ...
;// ->
;//    x0,y0,z0, x1,y1,z1, x2,y2,z2, x3,y3,z3, ...
;//
;void
;soa2aos(float *xyz)
;{
;    __m256 x = _mm256_load_ps(xyz+0);
;    __m256 y = _mm256_load_ps(xyz+8);
;    __m256 z = _mm256_load_ps(xyz+16);
;
;    __m128 *m = (__m128 *)xyz;
;
;    __m256 rxy = _mm256_shuffle_ps(x, y, _MM_SHUFFLE(2, 0, 2, 0));
;    __m256 ryz = _mm256_shuffle_ps(y, z, _MM_SHUFFLE(3, 1, 3, 1));
;    __m256 rzx = _mm256_shuffle_ps(z, x, _MM_SHUFFLE(3, 1, 2, 0));
;
;    __m256 r03 = _mm256_shuffle_ps(rxy, rzx, _MM_SHUFFLE(2, 0, 2, 0));
;    __m256 r14 = _mm256_shuffle_ps(ryz, rxy, _MM_SHUFFLE(3, 1, 2, 0));
;    __m256 r25 = _mm256_shuffle_ps(rzx, ryz, _MM_SHUFFLE(3, 1, 3, 1));
;
;    m[0] = _mm256_castps256_ps128(r03);
;    m[1] = _mm256_castps256_ps128(r14);
;    m[2] = _mm256_castps256_ps128(r25);
;    m[3] = _mm256_extractf128_ps(r03, 1);
;    m[4] = _mm256_extractf128_ps(r14, 1);
;    m[5] = _mm256_extractf128_ps(r25, 1);
;*******************************************************************

soa2aosAsm proc

        vmovups ymm0, YMMWORD PTR [rcx+(4*0)]
        vmovups ymm1, YMMWORD PTR [rcx+(4*8)]
        vmovups ymm2, YMMWORD PTR [rcx+(4*16)]

        vshufps ymm3, ymm0, ymm1, 10001000b     ; (2, 0, 2, 0)
        vshufps ymm4, ymm1, ymm2, 11011101b     ; (3, 1, 3, 1)
        vshufps ymm5, ymm2, ymm0, 11011000b     ; (3, 1, 2, 0)

        vshufps ymm0, ymm3, ymm5, 10001000b     ; (2, 0, 2, 0)
        vshufps ymm1, ymm4, ymm3, 11011000b     ; (3, 1, 2, 0)
        vshufps ymm2, ymm5, ymm4, 11011101b     ; (3, 1, 3, 1)

        vextractf128 XMMWORD PTR [rcx+(16*0)], ymm0, 0
        vextractf128 XMMWORD PTR [rcx+(16*1)], ymm1, 0
        vextractf128 XMMWORD PTR [rcx+(16*2)], ymm2, 0
        vextractf128 XMMWORD PTR [rcx+(16*3)], ymm0, 1
        vextractf128 XMMWORD PTR [rcx+(16*4)], ymm1, 1
        vextractf128 XMMWORD PTR [rcx+(16*5)], ymm2, 1

        ret

soa2aosAsm endp


_TEXT   ends
        end
