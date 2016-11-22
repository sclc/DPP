_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            addsd   xmm0, xmm1
            ret
asmSample   endp

_TEXT       ends
            end
