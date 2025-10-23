.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024
fsd fa0, -16(sp)
fsd fa1, -32(sp)

fld f5, -16(sp)
fmv.d f4, f5
fld f5, -32(sp)
fmul.d f4, f4, f5
fmv.d fa0, f4
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
