	.file	"logical_or.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_f2p0_d2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	f
	.type	f, @function
f:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lw	a5,-20(s0)
	bne	a5,zero,.L2
	lw	a5,-24(s0)
	beq	a5,zero,.L3
.L2:
	li	a5,1
	j	.L5
.L3:
	li	a5,0
.L5:
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	f, .-f
	.ident	"GCC: () 12.2.0"
