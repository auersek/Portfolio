	.file	"call_mutual_recursive.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_f2p0_d2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	r1
	.type	r1, @function
r1:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	lw	a5,-20(s0)
	bne	a5,zero,.L2
	li	a5,1
	j	.L3
.L2:
	lw	a5,-20(s0)
	addi	a5,a5,-1
	mv	a0,a5
	call	r2
	mv	s1,a0
	lw	a5,-20(s0)
	addi	a5,a5,-1
	mv	a0,a5
	call	r2
	mv	a5,a0
	add	a5,s1,a5
.L3:
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	addi	sp,sp,32
	jr	ra
	.size	r1, .-r1
	.ident	"GCC: () 12.2.0"
