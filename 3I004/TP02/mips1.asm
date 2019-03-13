#moyenne tab		

.data
#convention exercice : fin du tableau delimitee par valeur negative (excluse)
tab:.word 23,7,12,513,-1
	

.text	
.globl main
main:
	#PROLOGUE: on fait comme une fonction normale
	#pour pouvoir transformer main en ss fonction plus tard
	#correspond au code genere par le compilateur
	
	#na = 1, nr = 1 ($31) nv = 0(1)
	addiu $sp,$sp,-12
	sw $ra,8($sp)
	
	#CORPS	
	#adresse de tab dans a0
	la $a0, tab
	
	jal arimean#res ds v0
	
	#pour afficher int : $v0=1 $a0=entier
	
	or $a0,$0,$v0
	ori $v0, $0, 1
	syscall
	
	
	#or $a0, $0, $v0
	#ori $v0,$0,1 
	#syscall
	
	#EPILOGUE
	
	#exit()
	ori $2,$0,10
	syscall
	
	#code pour fonction normale qui ne sera pas execute
	lw $ra, 8($sp)
	addiu $sp, $sp, 12
	jr $ra
	
	
	
#fonction retournant ($v0 = $2) le nombre d'elements du tableau
#argument ($a0 = $4) l'adresse du tableau
sizetab:
	########
	#PROLOGUE#
	########
	
	#na = max(nb arg des fn appelees) = 0
	#nr = nRegistrePersistant utilises = 0
	#(la fonction etant terminale, on ne se sert pas de $31 = $ra = Return Adress)
	#nv = nVariableLocale = 0(1)
	
	#FAUXpas de memoire a reserver dans la pile
	addiu $sp,$sp,-4
	
	######
	#CORPS#
	######
	
	ori $t0, $0, -1#index=-1 au debut
	
	boucle_sizetab:
		addiu $t0, $t0, 1#incremente index
		sll $t1,$t0,2#i*4
		addu $t1, $t1, $a0# adresse du ieme element
		lw $t1, 0($t1)#ieme element
		
		bgtz $t1,boucle_sizetab #fin du tableau codee par valeur negative
			
	ori $v0,$t0,0
	
	########
	#EPILOGUE#
	########
	#on a pas touche a la stack dans le prologue, on n'y touche pas la non plus
	
	addiu $sp,$sp,4
	jr $ra
	


#fonction retournant ($v0 = $2) la somme des elements du tableau
#argument ($a0 = $4) l'adresse du tableau
sumtab:
	#fonction terminale avec na = nr = nv = 0 (nv=2)
	#FAUXdonc pas de prologue/epilogue	
	
	addiu $sp,$sp,-8
	
	
	ori $v0, $0, 0#v0 = somme
	
	lw $t0, 0($a0)#t0=ieme element
		
	#voir boucle_sizetab pour la maniere conventionelle
	boucle_sumtab:
		addu $v0, $v0, $t0
		
		addiu $a0, $a0, 4#incremente index
		lw $t0, 0($a0)#t0=ieme element
		
		bgtz $t0,boucle_sumtab #fin du tableau codee par valeur negative
		
		
	#epilogue
	addiu $sp,$sp,8
	jr $ra
	


#fonction retournant ($v0 = $2) la moyenne des elements du tableau
#argument ($a0 = $4) l'adresse du tableau
arimean:
	########
	#PROLOGUE#
	########
	
	#na = max(nb arg des fn appelees) = 1
	#nr = nRegistrePersistant utilises = 2 ($s0 et $31)
	#nv = nVariableLocale = 0(2)
	
	#$29=$sp (Stack Pointer) pointe vers la derniere case reservee (p0 sur le schema)
	#reserve 4*(na+nr+nv) = 20 octets en decrementant sp
	addiu $sp,$sp,-20
	# sp  pointe vers la derniere case reservee (p1 sur le schema)
		
	#stocke $31=$ra dans la stack
	sw $ra,16($sp)
	
	sw $s0,12($sp)
		
	#pas d'hypothese sur les fn appelees, elles peuvent modifier $a0
	#on stocke $a0 a la place qui lui a ete reservee dans la stack
	sw $a0,20($sp)
	
	#    |----|adresse haute
	#p0->| a0 |zone reservee par f appelante pour 1er arg de arimean (valeur dans $a0) 
	#    | ra | 		-		  arimean pour stocker $31 = $ra
	#    | s0 |		-		  arimean pour stocker $16 = $s0
	#p1->|  ? |		-		  arimean pour 1er arg des fonctions appelees (valeur dans $a0) 
	#    |----|adresse basse 	
	
	######
	#CORPS#
	######
	
	
	#Jump AND LINK modifie $31, on l'a deja sauvegarde dans la stack
	#les fonctions peuvent modifier $a0, deja sauvegarde dans la stack aussi
	#argument dans $a0 pour sizetab est le meme que celui recu
	jal sizetab
	#recupere le resultat
	or $s0, $0, $v0
	
	#on remet a0 de la stack dans $a0 au cas ou il aurait ete modifie
	lw $a0, 20($sp)
	jal sumtab
	
	#division entiere
	divu $v0, $v0, $s0
	

	########
	#EPILOGUE#
	########
	
	lw $ra, 16($sp)
	lw $s0, 12($sp)
	addiu $sp, $sp, 20
	
	jr $ra
	
	

