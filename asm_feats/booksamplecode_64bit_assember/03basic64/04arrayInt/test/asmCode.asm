_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            mov dword ptr[rcx+4*0], 1
            mov dword ptr[rcx+4*1], 2
            mov dword ptr[rcx+4*2], 3
            mov dword ptr[rcx+4*3], 4
            mov dword ptr[rcx+4*4], 5
            ret
asmSample   endp

_TEXT       ends
            end
