	.file	"switch2.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_f2p0_d2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	g
	.type	g, @function
g:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	zero,-20(s0)
	lw	a4,-36(s0)
	li	a5,2
	beq	a4,a5,.L2
	lw	a4,-36(s0)
	li	a5,2
	bgt	a4,a5,.L3
	lw	a5,-36(s0)
	beq	a5,zero,.L4
	lw	a4,-36(s0)
	li	a5,1
	beq	a4,a5,.L5
	j	.L3
.L4:
	li	a5,1
	sw	a5,-20(s0)
	j	.L6
.L2:
	li	a5,2
	sw	a5,-20(s0)
.L5:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	j	.L6
.L3:
	lw	a5,-36(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L6:
	lw	a5,-20(s0)
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	g, .-g
	.ident	"GCC: () 12.2.0"
