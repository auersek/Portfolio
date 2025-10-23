	.file	"multiply.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_f2p0_d2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	multiply
	.type	multiply, @function
multiply:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	zero,-20(s0)
	lw	a5,-36(s0)
	bge	a5,zero,.L4
	lw	a5,-36(s0)
	neg	a5,a5
	lw	a1,-40(s0)
	mv	a0,a5
	call	multiply
	mv	a5,a0
	neg	a5,a5
	j	.L3
.L5:
	lw	a4,-20(s0)
	lw	a5,-40(s0)
	add	a5,a4,a5
	sw	a5,-20(s0)
	lw	a5,-36(s0)
	addi	a5,a5,-1
	sw	a5,-36(s0)
.L4:
	lw	a5,-36(s0)
	bgt	a5,zero,.L5
	lw	a5,-20(s0)
.L3:
	mv	a0,a5
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	multiply, .-multiply
	.ident	"GCC: () 12.2.0"
