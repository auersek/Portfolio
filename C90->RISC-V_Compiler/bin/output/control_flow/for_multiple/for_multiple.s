.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lw a2, -16(s0)
li a1, 0
mv a2, a1
sw a2, -16(s0)
lw a3, -8(s0)
li a2, 0
mv a3, a2
sw a3, -8(s0)
j condition__1
for__0:
lw a4, -16(s0)
lw a5, -16(s0)
add a3, a5, zero
li a5, 1
sub a3, a3, a5
mv a4, a3
sw a4, -16(s0)
update__2:
lw a5, -8(s0)
lw a4, -8(s0)
li a6, 1
add a4, a4, a6
mv a5, a4
sw a5, -8(s0)
condition__1:
lw a4, -8(s0)
li a5, 10
slt a5, a4, a5
bnez a5, for__0
endfor__3:
lw a5, -16(s0)
mv a0, a5
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
