.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)

li a1, 1
li a0, 4
mul a1, a1, a0
li a0, -8
sub a0, a0, a1
add a0, a0, sp
mv a1, a0
lw a0, 0(a1)
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
