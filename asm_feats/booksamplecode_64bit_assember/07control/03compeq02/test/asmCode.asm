_TEXT   segment

equal   proc
        xor eax, eax    ; eax = 0
        cmp ecx, edx
        jne label1
        mov eax, 1      ; eax = 1
    label1:
        ret
equal   endp

_TEXT   ends
        end
