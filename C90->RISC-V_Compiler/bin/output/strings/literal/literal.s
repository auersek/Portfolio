.text
.globl g
g:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lui a0, %hi(string_0)
addi a0, a0, %lo(string_0)
li a2, 0
li a1, 1
mul a2, a2, a1
li a1, -2
sub a1, a1, a2
add a1, a1, sp
mv a2, a1
lbu a1, 0(a2)
mv a0, a1
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
