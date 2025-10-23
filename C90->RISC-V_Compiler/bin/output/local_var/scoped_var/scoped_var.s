.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lw a2, -8(s0)
li a1, 5678
mv a2, a1
sw a2, -8(s0)
lw a3, -16(s0)
li a2, 1234
mv a3, a2
sw a3, -16(s0)
lw a2, -8(s0)
mv a0, a2
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
