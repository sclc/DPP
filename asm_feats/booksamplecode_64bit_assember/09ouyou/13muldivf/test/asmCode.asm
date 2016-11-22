_TEXT   segment

        public mulfunc
        align  16

mulfunc proc
        mulss   xmm0, xmm1
        ret
mulfunc endp


        public divfunc
        align  16

divfunc proc
        divss   xmm0, xmm1
        ret
divfunc endp

_TEXT       ends
            end
