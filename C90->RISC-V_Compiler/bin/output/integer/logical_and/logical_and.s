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
beqz a1, and_false_1
lw a1, -16(s0)
beqz a1, and_false_1
li a0, 1
j and_true_0
and_false_1:
li a0, 0
and_true_0:
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
