_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            add     ecx, edx    ; b + c
            mov     eax, ecx
            ret
asmSample   endp

_TEXT       ends
            end
