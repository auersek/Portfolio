.text
.globl g
g:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)
sw a1, -16(s0)
sw a2, -24(s0)
sw a3, -32(s0)
sw a4, -40(s0)

lw a0, -8(s0)
lw a4, -16(s0)
add a0, a0, a4
lw a3, -24(s0)
add a0, a0, a3
lw a2, -32(s0)
add a0, a0, a2
lw a1, -40(s0)
add a0, a0, a1
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

li a0, 1
li a1, 2
li a2, 3
li a3, 4
li a4, 5
mv a0, a0
call g
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
