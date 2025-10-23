.text
.globl f
f:
addi sp, sp,-1024
sw ra, 1020(sp)
sw s0, 1016(sp)
addi s0, sp,1024

lw a2, -8(s0)
li a1, 8
mv a2, a1
sw a2, -8(s0)
j condition__1
for__0:
lw a6, -8(s0)
add a5, a6, zero
li a6, 8
sub a5, a5, a6
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
li a4, 16
slt a3, a3, a4
bnez a3, for__0
endfor__3:
lw a5, -24(s0)
li a4, 0
mv a5, a4
sw a5, -24(s0)
lw a6, -8(s0)
li a5, 0
mv a6, a5
sw a6, -8(s0)
j condition__5
for__4:
