	.file	"switch1.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_f2p0_d2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	g
	.type	g, @function
g:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	lw	a4,-20(s0)
	li	a5,1
	beq	a4,a5,.L2
	lw	a4,-20(s0)
	li	a5,2
	beq	a4,a5,.L3
	j	.L6
.L2:
	li	a5,10
	j	.L1
.L3:
	li	a5,11
	j	.L1
.L6:
.L1:
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	g, .-g
	.ident	"GCC: () 12.2.0"
