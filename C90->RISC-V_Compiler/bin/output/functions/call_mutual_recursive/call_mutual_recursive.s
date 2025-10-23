.text
.globl r1
r1:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -16(s0)

lw a1, -16(s0)
mv a0, a1
li a2, 0
sub a0, a2, a0
seqz a0, a0
beqz a0, else_0
li a3, 1
mv a0, a3
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
j endif_1
else_0:
lw a5, -16(s0)
add a0, a5, zero
li a5, 1
sub a0, a0, a5
mv a3, a0
call r2
lw a5, -16(s0)
add a0, a5, zero
li a5, 1
sub a0, a0, a5
mv a4, a0
call r2
add a3, a3, a4
mv a0, a3
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
endif_1:
