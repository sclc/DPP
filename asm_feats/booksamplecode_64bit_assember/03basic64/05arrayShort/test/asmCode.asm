_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            mov word ptr[rcx+2*0], 1
            mov word ptr[rcx+2*1], 2
            mov word ptr[rcx+2*2], 3
            mov word ptr[rcx+2*3], 4
            mov word ptr[rcx+2*4], 5
            ret
asmSample   endp

_TEXT       ends
            end
