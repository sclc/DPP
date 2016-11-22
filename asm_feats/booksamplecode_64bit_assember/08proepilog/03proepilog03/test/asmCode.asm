include ksamd64.inc

_TEXT           segment

SkFrame         struct
    sv_xmm6     xmmword ?
    sv_xmm7     xmmword ?
    sv_xmm8     xmmword ?
    sv_xmm9     xmmword ?
    sv_rbx      dq      ?
    sv_rsi      dq      ?
    sv_rdi      dq      ?
    sv_rbp      dq      ?
    sv_rsp      dq      ?
    sv_r12      dq      ?
    sv_r13      dq      ?
    sv_r14      dq      ?
    sv_r15      dq      ?
    local_var   dq      ?   ; local var.
    dummy       dq      ?   ; dummy
SkFrame         ends

; structure size mest be (16*n+8) bytes.
.erre (size SkFrame mod 16) eq 8, <stack frame size must be 16n+8>


            public asmCode
            align  16

asmCode     proc    frame
            ; prolog
            alloc_stack(size SkFrame)
            save_xmm128 xmm6, SkFrame.sv_xmm6
            save_xmm128 xmm7, SkFrame.sv_xmm7
            save_xmm128 xmm8, SkFrame.sv_xmm8
            save_xmm128 xmm9, SkFrame.sv_xmm9
            save_reg rbx, SkFrame.sv_rbx
            save_reg rsi, SkFrame.sv_rsi
            save_reg rdi, SkFrame.sv_rdi
            save_reg rbp, SkFrame.sv_rbp
            save_reg rsp, SkFrame.sv_rsp
            save_reg r12, SkFrame.sv_r12
            save_reg r13, SkFrame.sv_r13
            save_reg r14, SkFrame.sv_r14
            save_reg r15, SkFrame.sv_r15
            .endprolog ;


            mov     rax, 85
            mov     [rsp+SkFrame.local_var], rax    ; use local value
            mov     rax, 15
            add     rax, [rsp+SkFrame.local_var]


            pxor    xmm6, xmm6                      ; destroy registers
            pxor    xmm7, xmm7
            pxor    xmm8, xmm8
            pxor    xmm9, xmm9
            mov     rbx, rax
            mov     rsi, rax
            mov     rdi, rax
            mov     rbp, rax
            mov     r12, rax
            mov     r13, rax
            mov     r14, rax
            mov     r15, rax


            ; epilog
            movaps xmm6, [rsp + SkFrame.sv_xmm6]
            movaps xmm7, [rsp + SkFrame.sv_xmm7]
            movaps xmm8, [rsp + SkFrame.sv_xmm8]
            movaps xmm9, [rsp + SkFrame.sv_xmm9]
            mov rbx, [rsp + SkFrame.sv_rbx]
            mov rsi, [rsp + SkFrame.sv_rsi]
            mov rdi, [rsp + SkFrame.sv_rdi]
            mov rbp, [rsp + SkFrame.sv_rbp]
            mov rsp, [rsp + SkFrame.sv_rsp]
            mov r12, [rsp + SkFrame.sv_r12]
            mov r13, [rsp + SkFrame.sv_r13]
            mov r14, [rsp + SkFrame.sv_r14]
            mov r15, [rsp + SkFrame.sv_r15]
            add rsp, size SkFrame
            ret
asmCode     endp

_TEXT       ends
            end
