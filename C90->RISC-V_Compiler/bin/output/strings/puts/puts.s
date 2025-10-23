.text
.globl g
g:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lui a0, %hi(string_0)
addi a0, a0, %lo(string_0)
mv a1, a0
call fakeputs
