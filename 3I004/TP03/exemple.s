	.file	1 "exemple.c"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$sp,8,$31		# vars= 8, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	addiu	$sp,$sp,-8
	li	$2,24			# 0x18
	sw	$2,0($sp)
	li	$2,16			# 0x10
	sw	$2,4($sp)
$L2:
	lw	$3,0($sp)
	lw	$2,4($sp)
	beq	$3,$2,$L3
	lw	$2,0($sp)
	lw	$3,4($sp)
	slt	$2,$3,$2
	beq	$2,$0,$L4
	lw	$2,0($sp)
	lw	$3,4($sp)
	subu	$2,$2,$3
	sw	$2,0($sp)
	j	$L2
$L4:
	lw	$2,4($sp)
	lw	$3,0($sp)
	subu	$2,$2,$3
	sw	$2,4($sp)
	j	$L2
$L3:
	move	$2,$0
	addiu	$sp,$sp,8
	j	$31
	.end	main
