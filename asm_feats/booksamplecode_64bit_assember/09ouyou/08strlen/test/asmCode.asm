include ksamd64.inc

INT_MAX = 2147483647                ; 2^31 - 1

_TEXT       segment

            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            rex_push_reg rdi        ; push rdi
            .endprolog ;


            mov     rdi, rcx        ; source address
            mov     rcx, INT_MAX    ; max string length
            xor     al, al          ; al = NULL  char
            cld                     ; clear direction flag
            repne   scasb           ; search NULL char

            mov     rax, INT_MAX-1
            sub     rax, rcx        ; length of string


            ; epilog
            pop rdi                 ; pop rdi
            ret
asmCode     endp

_TEXT       ends
            end
