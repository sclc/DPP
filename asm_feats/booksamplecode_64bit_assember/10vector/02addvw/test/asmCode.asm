
_TEXT   segment

        public asmCode
        align  16

asmCode proc
        sar     rcx, 3
        xor     r10, r10

    loop1:
        movdqu  xmm0, [rdx+r10]
        movdqu  xmm1, [r8+r10]
        paddw   xmm0, xmm1
        movdqu  [r9+r10], xmm0
        add     r10, 16
        loop    loop1

        ret
asmCode endp

_TEXT   ends
        end
