.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

li a3, 0
li a2, 4
mul a3, a3, a2
li a2, -8
sub a2, a2, a3
add a2, a2, sp
mv a3, a2
lw a2, 0(a3)
li a1, 23
mv a2, a1
sw a2, -8(s0)
sw a2, 0(a3)
li a2, 0
li a1, 4
mul a2, a2, a1
li a1, -8
sub a1, a1, a2
add a1, a1, sp
mv a2, a1
lw a1, 0(a2)
mv a0, a1
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
