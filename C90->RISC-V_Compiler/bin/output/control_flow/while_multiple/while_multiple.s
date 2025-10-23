.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lw a2, -8(s0)
li a1, 20
mv a2, a1
sw a2, -8(s0)
j condition_0
statement_1:
lw a4, -8(s0)
lw a5, -8(s0)
add a3, a5, zero
li a5, 1
sub a3, a3, a5
mv a4, a3
sw a4, -8(s0)
condition_0:
lw a4, -8(s0)
li a3, 10
sgt a4, a4, a3
bne a4, zero, statement_1
lw a3, -8(s0)
mv a0, a3
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
