.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)
sw a1, -16(s0)

lw a1, -8(s0)
bnez a1, or_true_0
lw a1, -16(s0)
bnez a1, or_true_0
li a0, 0
j or_false_1
or_true_0:
li a0, 1
or_false_1:
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
