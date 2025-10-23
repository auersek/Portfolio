.text
.globl g
g:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
sw a0, -8(s0)

lw a2, -16(s0)
li a1, 0
mv a2, a1
sw a2, -16(s0)
