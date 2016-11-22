_TEXT       segment

            public leftSigned
            align  16

leftSigned  proc
            mov     eax, ecx
            mov     cl,  dl
            sal     eax, cl
            ret
leftSigned  endp

            public leftUnsigned
            align  16

leftUnsigned proc
            mov     eax, ecx
            mov     cl,  dl
            shl     eax, cl
            ret
leftUnsigned endp


_TEXT       ends
            end
