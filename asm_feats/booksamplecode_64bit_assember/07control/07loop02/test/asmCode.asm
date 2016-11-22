_TEXT       segment

arrayAdd    proc
            mov rax, rcx
            mov rcx, rdx

    loop1:
            add dword ptr[rax], 2
            add rax, 4
            ;lea rax, [rax+4]
            loop loop1

            ret
arrayAdd    endp

_TEXT       ends
            end
