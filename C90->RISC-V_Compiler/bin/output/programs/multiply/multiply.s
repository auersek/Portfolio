.text
.globl multiply
multiply:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)
sw a1, -16(s0)

li a0, 0
sw a0, -24(s0)
lw a1, -8(s0)
li a2, 0
slt a0, a1, a2
beqz a0, endif_0
lw a4, -8(s0)
neg a0, a4
lw a1, -16(s0)
mv a3, a0
call multiply
neg a2, a3
mv a0, a2
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
endif_0:
j condition_1
statement_2:
lw a4, -24(s0)
lw a5, -16(s0)
add a4, a4, a5
sw a4, -24(s0)
lw a4, -8(s0)
mv a4, a4
addi a4, a4, -1
sw a4, -8(s0)
condition_1:
lw a5, -8(s0)
li a4, 0
sgt a4, a5, a4
bne a4, zero, statement_2
lw a4, -24(s0)
mv a0, a4
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
