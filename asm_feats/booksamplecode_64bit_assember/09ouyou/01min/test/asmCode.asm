_TEXT       segment

            public asmCode
            align  16

asmCode     proc
            mov     eax, 7FFFFFFFh  ; eax = INT_MAX

        loop1:                      ; for (int i = 0; i < length; i++)
            cmp     [rdx], eax
            jg      label1          ;   eax = [rdx] > eax ? eax : [rdx];
            mov     eax, [rdx]
        label1:
            lea     rdx, [rdx+4]    ; next data addr
            loop    loop1

            ret
asmCode     endp

_TEXT       ends
            end
