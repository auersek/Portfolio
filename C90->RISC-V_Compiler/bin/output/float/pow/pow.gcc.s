	.file	"pow.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_f2p0_d2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	f
	.type	f, @function
f:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	fsw	fa0,-36(s0)
	sw	a0,-40(s0)
	lui	a5,%hi(.LC0)
	flw	fa5,%lo(.LC0)(a5)
	fsw	fa5,-20(s0)
	sw	zero,-24(s0)
	j	.L2
.L3:
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
	flw	fa4,-20(s0)
	flw	fa5,-36(s0)
	fmul.s	fa5,fa4,fa5
	fsw	fa5,-20(s0)
.L2:
	lw	a4,-24(s0)
	lw	a5,-40(s0)
	blt	a4,a5,.L3
	flw	fa5,-20(s0)
	fmv.s	fa0,fa5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	f, .-f
	.section	.rodata
	.align	2
.LC0:
	.word	1065353216
	.ident	"GCC: () 12.2.0"
