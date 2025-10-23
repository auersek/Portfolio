.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
fsw fa0, -8(s0)
fsw fa1, -16(s0)
fsw fa2, -24(s0)

flw f6, -8(s0)
fmv.s f5, f6
flw f6, -16(s0)
fmul.s f5, f5, f6
fmv.s f4, f5
flw f5, -24(s0)
fadd.s f4, f4, f5
fmv.s fa0, f4
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
