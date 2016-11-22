_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            mov byte ptr [rcx], 04h
            mov word ptr [rdx], 0304h
            mov dword ptr [r8], 01020304h
            ret
asmSample   endp

_TEXT       ends
            end
