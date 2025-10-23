.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lw a2, -8(s0)
li a1, 0
mv a2, a1
sw a2, -8(s0)
j condition__1
for__0:
li a1, 1
mv a0, a1
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
update__2:
lw a1, -8(s0)
mv a2, a1
addi a1, a1, 1
sw a1, -8(s0)
condition__1:
lw a1, -8(s0)
li a2, 0
slt a2, a1, a2
bnez a2, for__0
endfor__3:
li a2, 19937
mv a0, a2
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
