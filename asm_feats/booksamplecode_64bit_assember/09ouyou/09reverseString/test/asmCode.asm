include ksamd64.inc

INT_MAX = 2147483647                ; 2^31 - 1

_TEXT       segment

            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            rex_push_reg rsi        ; push rsi
            push_reg     rdi        ; push rdi
            .endprolog ;


            mov     rdi, rcx        ; source address
            mov     rcx, INT_MAX    ; length
            xor     al, al          ; al = NULL•¶Žš
            cld                     ; clear direction flag
            repne   scasb           ; NULL•¶Žš‚ð’T‚·

            mov     rax, INT_MAX-1
            sub     rax, rcx        ; rax = •¶Žš—ñ’·
            mov     rcx, rax        ; length

            mov     rsi, rdi
            sub     rsi, 2
            mov     rdi, rdx        ; address of destination

        loop1:
            movsb
            sub     rsi, 2
            loop    loop1           ; loop if ecx not ZERO

            xor     al, al
            stosb                   ; set NULL•¶Žš


            ; epilog
            pop rdi                 ; pop rdi
            pop rsi                 ; pop rsi
            ret
asmCode     endp

_TEXT       ends
            end
