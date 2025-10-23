.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)

lw a1, -8(s0)
mv a0, a1
li a2, 0
sub a0, a2, a0
seqz a0, a0
beqz a0, endif_0
li a3, 0
mv a0, a3
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
endif_0:
lw a0, -8(s0)
lw a4, -8(s0)
add a0, a4, zero
li a4, 1
sub a0, a0, a4
mv a3, a0
call f
add a0, a0, a3
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
