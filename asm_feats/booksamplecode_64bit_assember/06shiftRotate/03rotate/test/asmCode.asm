_TEXT       segment

            public left
            align  16

left        proc
            mov     eax, ecx
            mov     cl,  dl
            rol     eax, cl
            ret
left        endp


            public right
            align  16

right       proc
            mov     eax, ecx
            mov     cl,  dl
            ror     eax, cl
            ret
right       endp


            public stcLeft
            align  16

stcLeft     proc
            mov     eax, ecx
            mov     cl,  dl
            stc
            rcl     eax, cl
            ret
stcLeft     endp


            public clcRight
            align  16

clcRight    proc
            mov     eax, ecx
            mov     cl,  dl
            clc
            rcr     eax, cl
            ret
clcRight    endp


_TEXT       ends
            end
