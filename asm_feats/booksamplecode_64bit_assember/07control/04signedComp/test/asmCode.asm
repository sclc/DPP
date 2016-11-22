_TEXT   segment

comp    proc
        xor eax, eax    ; eax = 0
        cmp ecx, edx
        jl  label1
        mov eax, 1      ; eax = 1
    label1:
        ret
comp    endp

_TEXT   ends
        end
