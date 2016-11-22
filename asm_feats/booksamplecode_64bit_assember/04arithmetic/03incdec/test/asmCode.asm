_TEXT       segment

            public incfunc
            align  16

incfunc     proc
            mov     eax, ecx
            inc     eax         ; a++
            inc     eax         ; a++
            inc     eax         ; a++
            inc     eax         ; a++
            inc     eax         ; a++
            ret
incfunc     endp


            public decfunc
            align  16

decfunc     proc
            mov     eax, ecx
            dec     eax         ; a--
            dec     eax         ; a--
            dec     eax         ; a--
            ret
decfunc     endp

_TEXT       ends
            end
