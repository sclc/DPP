_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            mov    [rcx], edx  ; *a =  b
            ret
asmSample   endp

_TEXT       ends
            end
