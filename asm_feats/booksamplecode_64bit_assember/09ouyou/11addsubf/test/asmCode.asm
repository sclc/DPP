_TEXT   segment

        public addfunc
        align  16

addfunc proc
        addss   xmm0, xmm1
        ret
addfunc	endp


        public subfunc
        align  16

subfunc proc
        subss   xmm0, xmm1
        ret
subfunc	endp

_TEXT       ends
            end
