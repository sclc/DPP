_TEXT       segment

            public andfunc
            align  16

andfunc     proc
            and     ecx, edx
            mov     eax, ecx
            ret
andfunc     endp

            public orfunc
            align  16

orfunc      proc
            or      ecx, edx
            mov     eax, ecx
            ret
orfunc      endp

_TEXT       ends
            end
