_TEXT   segment


        public aos2soaAsm
        align  16

aos2soaAsm proc

                                            ;RCX  = &xyz
                                            ;RDX  = &px
                                            ;R8   = &py
                                            ;R9   = &pz
                                            ;SP+40= length

    mov     r11, rcx                        ; r11 = &xyz
    mov     rcx, qword ptr [rsp+40]         ; rcx =length

loopx:
                                            ; 下半分のロード
    vmovups ymm0, YMMWORD PTR [r11+(16*0)]
    vmovups ymm1, YMMWORD PTR [r11+(16*1)]
    vmovups ymm2, YMMWORD PTR [r11+(16*2)]

                                            ; 上半分のロード
    vinsertf128 ymm0, ymm0, XMMWORD PTR [r11+(16*3)], 1
    vinsertf128 ymm1, ymm1, XMMWORD PTR [r11+(16*4)], 1
    vinsertf128 ymm2, ymm2, XMMWORD PTR [r11+(16*5)], 1


    vshufps ymm3, ymm1, ymm2, 10011110b     ; (2,1,3,2) x と y の上部分
    vshufps ymm4, ymm0, ymm1, 01001001b     ; (1,0,2,1) y と z の下部分
    vshufps ymm0, ymm0, ymm3, 10001100b     ; (2,0,3,0)
    vshufps ymm1, ymm4, ymm3, 11011000b     ; (3,1,2,0)
    vshufps ymm2, ymm4, ymm2, 11001101b     ; (3,0,3,1)

    vmovups YMMWORD PTR [rdx], ymm0
    vmovups YMMWORD PTR [r8],  ymm1
    vmovups YMMWORD PTR [r9],  ymm2

    add     r11, 4*24                       ; r11=&xyz, xyz+=sizeof(float)*24
    add     rdx, 32                         ; rdx=&x,   x+=32
    add     r8,  32                         ; r8 =&y,   y+=32
    add     r9,  32                         ; r9 =&z,   z+=32

    sub     rcx, 24                         ; rcx=length, lengh-=24
    jnz     loopx                           ; if(length>0) goto loop

    ret

aos2soaAsm endp






        public soa2aosAsm
        align  16

soa2aosAsm proc

                                            ;RCX  = &px
                                            ;RDX  = &py
                                            ;R8   = &pz
                                            ;R9   = &xyz
                                            ;SP+40= length

    mov     r11, rcx                        ; r11 = &x
    mov     rcx, qword ptr [rsp+40]         ; rcx =length

loopx:

    vmovups ymm0, YMMWORD PTR [r11]         ; x
    vmovups ymm1, YMMWORD PTR [rdx]         ; y
    vmovups ymm2, YMMWORD PTR [r8]          ; z

    vshufps ymm3, ymm0, ymm1, 10001000b     ; (2, 0, 2, 0)
    vshufps ymm4, ymm1, ymm2, 11011101b     ; (3, 1, 3, 1)
    vshufps ymm5, ymm2, ymm0, 11011000b     ; (3, 1, 2, 0)

    vshufps ymm0, ymm3, ymm5, 10001000b     ; (2, 0, 2, 0)
    vshufps ymm1, ymm4, ymm3, 11011000b     ; (3, 1, 2, 0)
    vshufps ymm2, ymm5, ymm4, 11011101b     ; (3, 1, 3, 1)

    vextractf128 XMMWORD PTR [r9+(16*0)], ymm0, 0
    vextractf128 XMMWORD PTR [r9+(16*1)], ymm1, 0
    vextractf128 XMMWORD PTR [r9+(16*2)], ymm2, 0
    vextractf128 XMMWORD PTR [r9+(16*3)], ymm0, 1
    vextractf128 XMMWORD PTR [r9+(16*4)], ymm1, 1
    vextractf128 XMMWORD PTR [r9+(16*5)], ymm2, 1

    add     r9,  4*24                       ; r9 =&xyz, xyz+=sizeof(float)*24
    add     r11, 32                         ; r11=&x,   x+=32
    add     rdx, 32                         ; r8 =&y,   y+=32
    add     r8,  32                         ; r9 =&z,   z+=32

    sub     rcx, 24                         ; rcx=length, lengh-=24
    jnz     loopx                           ; if(length>0) goto loop

    ret

soa2aosAsm endp

_TEXT   ends
        end
