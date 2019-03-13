#factorielle

.data
	n : .word 6
	

.text	
.globl main
main:
	#PROLOGUE: on fait comme une fonction normale
	#pour pouvoir transformer main en ss fonction plus tard
	#correspond au code genere par le compilateur
	
	#na = 1, nr = 1 ($31) nv = 0
	addiu $sp,$sp,-8
	sw $ra,4($sp)
	
	#CORPS	
	la $a0, n
	lw $a0, ($a0)
	
	#exception si n<0
	bgez $a0, fin_if_main
		#print_str("factorielle n<0 non definie")
		#exit()
		ori $2,$0,10
		syscall
	fin_if_main:
	
	jal fact#res ds v0
	
	#affiche res
	or $a0, $0, $v0
	ori $v0, $0, 1
	syscall
	
	
	#EPILOGUE
	#exit()
	ori $2,$0,10
	syscall
	
	#code pour fonction normale qui ne sera pas execute
	lw $ra, 4($sp)
	addiu $sp, $sp, 8
	jr $ra
	


#fonction retournant ($v0 = $2) n!
#argument ($a0 = $4) n
#(n<0)! n'est pas definie
#(n>13)! n'est pas representable sur 32 bits
#fact(32)=fact(33)=-2147483648 = 0x8000. fact(n>33)=0
fact:	
	#CAS DE BASE
	#devrait etre après prologue
	
	bgtz $a0, fin_if_fact
		ori $v0,$0,1
		jr $ra
	fin_if_fact:
	#PROLOGUE
	
	#na = max(nb arg des fn appelees) = 1
	#nr = nRegistrePersistant utilises = 1 ($31)
	#nv = nVariableLocale = 0
	
	#$29=$sp (Stack Pointer) pointe vers la derniere case occupee (p sur le schema)
	#reserve 4*(na+nr+nv) = 8 octets en decrementant sp
	addiu $sp,$sp,-8
	# sp  pointe vers la derniere case reservee (p2 sur le schema)
		
	#stocke $31=$ra dans la stack
	sw $ra,4($sp)
		
	#pas d'hypothese sur les fn appelees, elles peuvent modifier $a0
	#on stocke $a0 a la place qui lui a ete reservee dans la stack
	sw $a0,8($sp)
	
	#   	        |-------|adresse haute
	#p(n)->   | a0(n) |zone reservee par fn appelante pour 1er arg de fact (valeur dans $a0) 
	#             | ra(n) | 		-	ici			 pour stocker $31 = $ra
	#p(n-1)->|a0(n-1)|
	#             |ra(n-1)|
	#	        | ..... |
	#p2(1)-> |   ?   |
	#             |-------|adresse basse 	
	
	######
	#CORPS#
	######	
	
	
	#v0 = f(n-1)
	addiu $a0,$a0,-1
	jal fact
	
	#a0 = n
	lw $a0,8($sp)
	
	#v0 = a0*v0
	#mul $v0,$a0,$v0 pas dans la doc, macro ?
	mult $a0,$v0
	mflo $v0

	########
	#EPILOGUE#
	########
	
	lw $ra, 4($sp)
	addiu $sp, $sp, 8
	
	jr $ra
	
	
