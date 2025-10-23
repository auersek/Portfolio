.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)

lw a2, -8(s0)
lw a1, -8(s0)
li a3, 1
addi a1, a1, 4
mv a2, a1
sw a2, -8(s0)
lw a1, -8(s0)
lw a1, 0(a1)
mv a0, a1
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
