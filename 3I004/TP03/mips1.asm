.data
	tab: .word 3, 33, 49, 4, 23, 12, 46, 21, 48, 2
	retour: .asciiz "\n"

.text

.globl main 

	main:
		#prologue 
		#na = 2, nr = 1, nv = 1
		addiu $29, $29, -16
		sw $31, 12($29)

		#corps
		addiu $8, $0, 10
		sw $8, 8($29) #taille
			
			#appel affiche
		la $4, tab
		lw $5, 8($29)
		jal affiche

			#appel tri
		la $4, tab
		lw $5, 8($29) 
		jal tri
		
		la $4, retour 
		ori $2, $0, 4 #affichage chaine
		syscall 

			 #appel affiche
		la $4, tab
		lw $5, 8($29)
		jal affiche

			#exit 
		ori $2, $0, 10
		syscall

		#epilogue 
		lw $31, 12($29)
		addiu $29, $29, 16
		jr $31

	affiche:
		#prologue
		#na = 0, nr = 1, nv = 1
		addiu $29, $29, -8
		sw $31, 4($29)
		sw $4, 8($29)
		sw $5, 12($29)

		#corps
		sw $0, 0($29) # i = 0

		affiche_boucle:
			lw $9, 0($29) #lecture
			sll $9, $9, 2 #i*4
			lw $8, 8($29) #lecture tab ($tab[0])
			addu $8, $9, $8 # &tab[i]
			lw $4, 0($8)
			ori $2, $0, 1 #affichage entier
			syscall

			la $4, retour 
			ori $2, $0, 4 #affichage chaine
			syscall 

			lw $8, 0($29) #lecture i
			addiu $8, $8, 1 #i++
			sw $8, 0($29) #ecriture i
			lw $9, 12($29) #lecture taille
		bne $9, $8, affiche_boucle #on boucle tant que i != taille		

		#epilogue
		lw $31, 4($29)
		addiu $29, $29, 8
		jr $31

	echange:
		#prologue
		#na = 0, nr = 1, nv = 1
		addiu $29, $29, -8
		sw $31, 4($29)

		#corps
		sll $8, $5, 2 # i*4
		addu $8, $8, $4 # &tab[i]
		sll $9, $6, 2 # j*4
		addu $9, $9, $4 # &tab[j]
		lw $10, 0($8) # tab[i]
		lw $11, 0($9) # tab[j]
		sw $10, 0($9) # ecriture tab[j]
		sw $11, 0($8) # ecriture tab[i]

		#epilogue
		lw $31, 4($29)
		addiu $29, $29, 8
		jr $31

	tri: 
	 	#prologue
	 	#na = 3, nr = 3, nv =3
	 	addiu $29, $29, -36
	 	sw $31, 32($29)
	 	sw $17, 28($29)
	 	sw $16, 24($29) 

	 	#corps
	 	or $16, $4, $0
	 	or $17, $5, $0

	 	#cas terminal
	 	slti $11, $17, 2
	 	bne $11, $0, epilogue

	 	#recursive
	 	ori $8, $0, 0 # valmax = 0
	 	ori $9, $0, 0 # i = 0

	 		#boucle principale
	 	j tri_loop_test

	 	tri_loop:
	 		sll $11, $9, 2 # i*4
	 		addu $11, $11, $16 # $tab[i]
	 		lw $12, 0($11) # tab[i]
	 		slt $12, $8, $12 #valmax < tab[i]
	 	beq $12, $0, tri_endif
	 	lw $8, 0($11)  # tab[i] -> valmax
	 	or $10, $0, $9 # imax <- i

	 	tri_endif:
	 		addiu $9, $9, 1

	 	tri_loop_test:
	 		bne $9, $17, tri_loop 

	 	#appel echange
	 	or $4, $0, $16
	 	or $5, $0, $10
	 	addiu $6, $17, -1 # taille-1
	 	jal echange

	 	#appel tri 
	 	or $4, $0, $16
	 	addiu $5, $17, -1
	 	jal tri

		epilogue:
	 	#epilogue
	 	lw $31, 32($29)
	 	lw $17, 28($29)
	 	lw $16, 24($29) 
	 	addiu $29, $29, 36
	 	jr $31
