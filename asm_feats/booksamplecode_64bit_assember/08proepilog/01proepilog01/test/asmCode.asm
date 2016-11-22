include ksamd64.inc

_TEXT       segment

            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            rex_push_reg rsi    ; push rsi by macro
            .endprolog ;

            mov rax, 100        ; set return value

            mov rsi, rax        ; destroy register

            ; epilog
            pop rsi             ; pop rsi
            ret
asmCode     endp

_TEXT       ends
            end
