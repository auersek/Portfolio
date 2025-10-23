.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)
sw a1, -16(s0)

lw a2, -24(s0)
lw a4, -8(s0)
lw a3, -16(s0)
sgt a1, a4, a3
xori a1, a1, 1
mv a2, a1
sw a2, -24(s0)
lw a1, -24(s0)
mv a0, a1
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
