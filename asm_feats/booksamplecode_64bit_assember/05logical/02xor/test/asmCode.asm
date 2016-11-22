_TEXT       segment

            public xorfunc
            align  16

xorfunc     proc
            xor     ecx, edx
            mov     eax, ecx
            ret
xorfunc     endp

_TEXT       ends
            end
