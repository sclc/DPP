include ksamd64.inc

_TEXT       segment

            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            rex_push_reg rsi        ; push rsi
            push_reg rdi            ; push rdi
            push_reg rbx            ; push rbx
            .endprolog ;


            mov     rsi, r8         ; source address
            mov     rdi, r9         ; destination address
            mov     r8d, ecx        ; save small loop counter
            sub     edx, ecx        ; big loop counter
            mov     r9d, edx        ; save big loop counter

            cld

        loop1:
            mov     ecx, r8d        ; restore small loop counter
            xor     ebx, ebx        ; ebx(sum) = 0

            mov     r10, rsi        ; save source address
        loop2:
            lodsd
            add     ebx, eax
            loop    loop2

            mov     rsi, r10        ; restore source address
            add     rsi, 4          ; next source address

            mov     eax, ebx
            mov     edx, eax        ; set upper
            sar     edx, 31         ; expand flag
            idiv    r8d             ; moving avarage
            stosd

            dec     r9d
            jnz     loop1

            ; epilog
            pop rbx                 ; pop rbx
            pop rdi                 ; pop rdi
            pop rsi                 ; pop rsi
            ret
asmCode     endp

_TEXT       ends
            end
