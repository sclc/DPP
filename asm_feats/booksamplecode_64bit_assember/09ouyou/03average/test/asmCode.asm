_TEXT       segment

            public asmCode
            align  16

asmCode     proc
            mov     r8, rcx         ; save it
            xor     eax, eax        ; eax = 0

        loop1:                      ; for (int i = 0; i < length; i++)
            add     eax, [rdx]      ;   eax += [rdx];
            lea     rdx, [rdx+4]
            loop    loop1

            mov     rcx, r8         ; restore it
            mov     edx, eax        ; set upper
            sar     edx, 31         ; expand flag
            idiv    ecx             ; eax / ecx
            ret
asmCode     endp

_TEXT       ends
            end
