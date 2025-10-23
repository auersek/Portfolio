.text
.globl fib
fib:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)

lw a2, -8(s0)
li a1, 0
sgt a0, a2, a1
xori a0, a0, 1
beqz a0, endif_0
li a1, 0
mv a0, a1
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
endif_0:
lw a1, -8(s0)
mv a0, a1
li a3, 1
sub a0, a3, a0
seqz a0, a0
beqz a0, endif_1
li a4, 1
mv a0, a4
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
endif_1:
lw a5, -8(s0)
add a0, a5, zero
li a5, 1
sub a0, a0, a5
mv a0, a0
call fib
lw a5, -8(s0)
add a0, a5, zero
li a5, 2
sub a0, a0, a5
mv a4, a0
call fib
add a0, a0, a4
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
