_TEXT       segment

            public mulfunc
            align  16

mulfunc     proc
            mov     eax, ecx
            imul    edx         ; b * c
            ret
mulfunc     endp


            public divfunc
            align  16

divfunc     proc
            mov     eax, ecx
            mov     ecx, edx
            mov     edx, eax
            sar     edx, 31     ; set sign flag
            idiv    ecx         ; b / c
            ret
divfunc     endp

_TEXT       ends
            end
