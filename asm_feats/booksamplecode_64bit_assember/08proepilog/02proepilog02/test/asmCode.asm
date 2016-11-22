include ksamd64.inc

_TEXT       segment

            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            rex_push_reg rbx        ; push registers by macro
            push_reg     rsi
            push_reg     rdi
            push_reg     rbp
            push_reg     r12
            push_reg     r13
            push_reg     r14
            push_reg     r15
            .endprolog ;

            mov rax, 100            ; set return value

            mov rbx, rax            ; destroy registers
            mov rsi, rax
            mov rdi, rax
            mov r12, rax
            mov r13, rax
            mov r14, rax
            mov r15, rax

            ; epilog
            pop          r15        ; pop registers
            pop          r14
            pop          r13
            pop          r12
            pop          rbp
            pop          rdi
            pop          rsi
            pop          rbx
            ret
asmCode     endp

_TEXT       ends
            end
