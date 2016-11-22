_TEXT   segment

loopSum proc
        mov eax, 0
        mov ecx, 0

    loop1:
        add eax, ecx
        inc ecx
        cmp ecx,100
        jb  loop1

        ret
loopSum endp

_TEXT   ends
        end
