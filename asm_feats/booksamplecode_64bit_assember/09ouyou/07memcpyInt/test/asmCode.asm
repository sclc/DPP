include ksamd64.inc

_TEXT       segment

            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            rex_push_reg rsi        ; push rsi
            push_reg rdi            ; push rdi
            .endprolog ;

            mov     rsi, rdx        ; source      address
            mov     rdi, rcx        ; destination address

            mov     rcx, r8         ; length
            sar     rcx, 2          ; byte length to dword length

            cld
            rep movsd               ; move it

            ; epilog
            pop rdi                 ; pop rdi
            pop rsi                 ; pop rsi
            ret
asmCode     endp

_TEXT       ends
            end
