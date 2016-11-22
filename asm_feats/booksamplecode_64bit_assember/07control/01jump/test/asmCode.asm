_TEXT   segment

jump    proc
        mov eax, 100
        jmp label1
        mov eax, 1000
    label1:
        ret
jump    endp

_TEXT   ends
        end
