	.file	"mul_double.c"
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
	fsd	fa0,-24(s0)
	fsd	fa1,-32(s0)
	fld	fa4,-24(s0)
	fld	fa5,-32(s0)
	fmul.d	fa5,fa4,fa5
	fmv.d	fa0,fa5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	f, .-f
	.ident	"GCC: () 12.2.0"
