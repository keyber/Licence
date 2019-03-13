	.text
	.globl	echange
echange:		# vars= 8, regs= 0/0, args= 0, gp= 0
	addiu	$sp,$sp,-8
#ne sauvegarde pas $31 car terminal
#r�serve une case supplementaire
	sw	$4,8($sp)#tab
	sw	$5,12($sp)#i
	sw	$6,16($sp)#j
	lw	$2,12($sp)#i
	sll	$3,$2,2#i*4
	lw	$2,8($sp)#tab
	addu	$2,$3,$2#&tabi
	lw	$2,0($2)#tabi
	sw	$2,0($sp)#tmp=tab[i]
	lw	$2,12($sp)#i
	sll	$3,$2,2#i*4
	lw	$2,8($sp)#tab
	addu	$4,$3,$2#&tabi
	lw	$2,16($sp)#j
	sll	$3,$2,2#j*4
	lw	$2,8($sp)#tab
	addu	$2,$3,$2#&tabj
	lw	$2,0($2)#tabj
	sw	$2,0($4)#tab[i]=tab[j]
	lw	$2,16($sp)#j
	sll	$3,$2,2#j*4
	lw	$2,8($sp)#tab
	addu	$3,$3,$2#&tabj
	lw	$2,0($sp)#tmp
	sw	$2,0($3)#tab[j]=tmp
	addiu	$sp,$sp,8
	jr	$31

	.globl	tri
tri:#fn recursive nv=3
#r�serve plus que n�cessaire dans la pile
# vars= 16, regs= 1/0, args= 16, gp= 0
	addiu	$sp,$sp,-40
	sw	$31,32($sp)
	sw	$4,40($sp)	#tab
	sw	$5,44($sp)	#taille
	lw	$2,44($sp)	#taille
	slti	$2,$2,2	#taille<2
	beq	$2,$0,$L3	#=false continue
	j	$L2		#sinon return
$L3:				
	sw	$0,16($sp)	#valmax=0
	sw	$0,20($sp)	#i=0
$L4:	#FOR			
	lw	$2,20($sp)	#i
	lw	$3,44($sp)	#taille
	slt	$2,$2,$3	#i<taille
	beq	$2,$0,$L5	#=false break
	lw	$2,20($sp)	#i
	sll	$3,$2,2	#i*4
	lw	$2,40($sp)	#tab
	addu	$2,$3,$2	#&abi
	lw	$3,0($2)	#tabi
	lw	$2,16($sp)	#valmax
	slt	$2,$2,$3	#valmax<tabi
	beq	$2,$0,$L6	#=false 
	lw	$2,20($sp)	#i
	sll	$3,$2,2	#i*4
	lw	$2,40($sp)	#tab
	addu	$2,$3,$2	#&tabi
	lw	$2,0($2)	#tabi
	sw	$2,16($sp)	#valmax=tab[i]
	lw	$2,20($sp)	#i
	sw	$2,24($sp)	#imax=i
$L6:				
	lw	$2,20($sp)	#i
	addiu	$2,$2,1	#i+1
	sw	$2,20($sp)	#i++
	j	$L4 #boucle vers FOR		
$L5:				
	lw	$2,44($sp)	#taille
	addiu	$2,$2,-1	#taille-1
	lw	$4,40($sp)	#tab
	lw	$5,24($sp)	#imax
	move	$6,$2		#taille-1
	jal	echange	#swap (tab, imax, taille-1)
	lw	$2,44($sp)	#taille
	addiu	$2,$2,-1	#taille-1
	lw	$4,40($sp)	#tab
	move	$5,$2		#taille-1
	jal	tri		#appel recursif
$L2:			# EPILOGUE
	lw	$31,32($sp)
	addiu	$sp,$sp,40	
	jr	$31	
$LC0:	
	.word	3
	.word	33
	.word	49
	.word	4
	.word	23
	.text
	.globl	main
main:# vars= 24, regs= 1/0, args= 16, gp= 0
	addiu	$sp,$sp,-48
	sw	$31,40($sp)
#les 5 valeurs de tab sont stockees dans la pile
	lw	$2,$LC0
	lw	$3,$LC0+4
	lw	$4,$LC0+8
	lw	$5,$LC0+12
	lw	$6,$LC0+16
	sw	$2,16($sp)
	sw	$3,20($sp)
	sw	$4,24($sp)
	sw	$5,28($sp)
	sw	$6,32($sp)
	addiu	$4,$sp,16#$a0=&tab POINTE VERS LA PILE
	li	$5,5			# 0x5
	jal	tri
	lw	$31,40($sp)
	ori     $2, $0, 10
 	syscall
	addiu	$sp,$sp,48
	jr	$31

