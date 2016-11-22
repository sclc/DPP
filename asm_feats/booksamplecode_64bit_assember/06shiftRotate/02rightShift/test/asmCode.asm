_TEXT       segment

            public rightSigned
            align  16

rightSigned proc
            mov     eax, ecx
            mov     cl,  dl
            sar     eax, cl
            ret
rightSigned endp

            public rightUnsigned
            align  16

rightUnsigned proc
            mov     eax, ecx
            mov     cl,  dl
            shr     eax, cl
            ret
rightUnsigned endp


_TEXT       ends
            end
