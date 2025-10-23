	.file	"call_five_args_internal.c"
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
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	sw	a2,-28(s0)
	sw	a3,-32(s0)
	sw	a4,-36(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	add	a4,a4,a5
	lw	a5,-28(s0)
	add	a4,a4,a5
	lw	a5,-32(s0)
	add	a4,a4,a5
	lw	a5,-36(s0)
	add	a5,a4,a5
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	g, .-g
	.align	2
	.globl	f
	.type	f, @function
f:
	addi	sp,sp,-16
	sw	ra,12(sp)
	sw	s0,8(sp)
	addi	s0,sp,16
	li	a4,5
	li	a3,4
	li	a2,3
	li	a1,2
	li	a0,1
	call	g
	mv	a5,a0
	mv	a0,a5
	lw	ra,12(sp)
	lw	s0,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	f, .-f
	.ident	"GCC: () 12.2.0"
