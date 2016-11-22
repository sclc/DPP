_TEXT       segment

            public asmSample
            align  16

asmSample   proc
            mov eax, 01020304h ; eax=0x01020304
            mov [rcx], al
            mov [rdx], ax
            mov [r8], eax
            ret
asmSample   endp

_TEXT       ends
            end
