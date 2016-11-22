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

            cld
        loop1:
            lodsb                   ; get source
            or      al, al          ; if zero
            jz      exit_loop       ;       break
            or      al, 20h         ; tolower
            stosb                   ; set destination
            jmp     loop1           ; loop next char

        exit_loop:
            stosb                   ; set destination


            ; epilog
            pop rdi                 ; pop rdi
            pop rsi                 ; pop rsi
            ret
asmCode     endp

_TEXT       ends
            end
