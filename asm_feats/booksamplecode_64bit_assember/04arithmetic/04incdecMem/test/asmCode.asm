_TEXT       segment

            public incfunc
            align  16

incfunc     proc
            inc     dword ptr[rcx]  ; (*a)++
            inc     dword ptr[rcx]  ; (*a)++
            inc     dword ptr[rcx]  ; (*a)++
            inc     dword ptr[rcx]  ; (*a)++
            inc     dword ptr[rcx]  ; (*a)++
            ret
incfunc     endp


            public decfunc
            align  16

decfunc     proc
            dec     dword ptr[rcx]  ; (*a)--
            dec     dword ptr[rcx]  ; (*a)--
            dec     dword ptr[rcx]  ; (*a)--
            ret
decfunc     endp

_TEXT       ends
            end
