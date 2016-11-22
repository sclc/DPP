_TEXT   segment

eq5     proc
        xor eax, eax    ; eax = 0
        cmp ecx, 5
        jne label1
        mov eax, 1      ; eax = 1
    label1:
        ret
eq5     endp

_TEXT   ends
        end
