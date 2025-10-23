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
lw a3, -8(s0)
lw a2, -8(s0)
li a4, 1
add a2, a2, a4
mv a3, a2
sw a3, -8(s0)
condition__1:
lw a2, -8(s0)
li a3, 0
slt a3, a2, a3
bnez a3, for__0
endfor__3:
li a3, 19937
mv a0, a3
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
