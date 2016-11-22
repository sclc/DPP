_TEXT       segment

            public addfunc
            align  16

addfunc     proc
            add     ecx, edx    ; b + c
            mov     eax, ecx
            ret
addfunc     endp


            public subfunc
            align  16

subfunc     proc
            sub     ecx, edx    ; b - c
            mov     eax, ecx
            ret
subfunc     endp

_TEXT       ends
            end
