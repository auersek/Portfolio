.text
.globl bsqrt
bsqrt:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)
sw a1, -16(s0)
sw a2, -24(s0)

j condition_0
statement_1:
lw a1, -8(s0)
lw a2, -16(s0)
add a1, a1, a2
li a2, 1
sra a1, a1, a2
sw a1, -32(s0)
lw a2, -32(s0)
add a1, a2, zero
lw a2, -32(s0)
mul a1, a1, a2
sw a1, -40(s0)
lw a3, -40(s0)
lw a2, -24(s0)
sgt a1, a3, a2
xori a1, a1, 1
beqz a1, else_2
lw a5, -8(s0)
lw a6, -32(s0)
mv a5, a6
sw a5, -8(s0)
j endif_3
else_2:
