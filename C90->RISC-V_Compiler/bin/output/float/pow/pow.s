.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
fsw fa0, -8(s0)
sw a0, -16(s0)

flw f4, 1
fsw f4, -24(s0)
li a0, 0
sw a0, -32(s0)
j condition_0
statement_1:
lw a1, -32(s0)
mv a0, a1
addi a1, a1, 1
sw a1, -32(s0)
flw f4, -24(s0)
flw f5, -24(s0)
fmv.s a2, f5
flw f5, -8(s0)
fmul.s a2, a2, f5
mv f4, a2
sw f4, -24(s0)
condition_0:
lw a2, -32(s0)
lw a3, -16(s0)
slt f4, a2, a3
bne f4, zero, statement_1
flw f5, -24(s0)
fmv.s fa0, f5
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
