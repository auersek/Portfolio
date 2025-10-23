# [Info] No var_name in VariableDeclare
.text
.globl g
g:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

vvli a1, 1
add a0, a0, a1
mv a0, a0
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
