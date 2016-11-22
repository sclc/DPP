_TEXT           segment

                public reverseByte
                align  16

reverseByte     proc
                mov     ah, cl        ; source data
                mov     rcx, 8

            loop1:
                rcl     ah, 1
                rcr     al, 1
                loop    loop1

                ret
reverseByte     endp


                public reverseShort
                align  16

reverseShort    proc
                mov     dx, cx        ; source data
                mov     rcx, 16

            loop1:
                rcl     dx, 1
                rcr     ax, 1
                loop    loop1

                ret
reverseShort    endp



                public reverseInt
                align  16

reverseInt      proc
                mov     edx, ecx        ; source data
                mov     rcx, 32

            loop1:
                rcl     edx, 1
                rcr     eax, 1
                loop    loop1

                ret
reverseInt      endp

_TEXT           ends
                end
