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
lw a5, -8(s0)
li a3, 4
mul a5, a5, a3
li a3, -16
sub a3, a3, a5
add a3, a3, sp
mv a5, a3
lw a3, 0(a5)
lw a4, -8(s0)
mv a3, a4
sw a3, -16(s0)
sw a3, 0(a5)
update__2:
lw a3, -8(s0)
mv a3, a3
addi a3, a3, 1
sw a3, -8(s0)
condition__1:
lw a3, -8(s0)
li a4, 8
slt a3, a3, a4
bnez a3, for__0
endfor__3:
li a4, 4
li a3, 4
mul a4, a4, a3
li a3, -16
sub a3, a3, a4
add a3, a3, sp
mv a4, a3
lw a3, 0(a4)
mv a0, a3
lw s0,1016(sp)
lw ra,1020(sp)
addi sp, sp,1024
jr ra
