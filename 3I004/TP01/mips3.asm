#stocke nb hexa en tant que chaine ASCII  
.data 

#réserve 8 B, il faut que la mémoire soit alignée
#res : .space 8 marche pas

res: .asciiz "0x00000000"

#crée un tableau dans la mémoire de 16 Bytes (16 * 255 possibilités)
table : .ascii "0123456789ABCDEF"

#nombre de 32bits = 4 Bytes = 8 charactères Hexadécimaux
#chaque caractère étant stocké sur 1 Byte, on stocke le res sur 8 Bytes
val: .word 0x5432ABCD


.text 
.globl main

main:

La $8, val#adresse de val ds $8
lw $8, 0($8)#mem(0+$8) ds $8
ori $9, $0, 32 #correspond a la variable i du code C

La $24, table#adresse de table

La $25, res#adresse de res
addiu $25, $25, 2#adresse de res + taille de "0x"
boucle_i:
#décrémente de i de 4 en 4 (4 bits codant un charactère)
addiu $9, $9, -4

#shift val à droite de i bits
srlv $10, $8, $9#10=8>>9
#garde les 4 bits de droite de val
andi $10,$10,0xF#10=10 & 0xF

#adresse du caractère correspondant dans la table
addu $10,$10,$24

#charge le caractère dans $11
lb $11, ($10)
#le met dans res
sb $11, 0($25)
#décale le pointeur sur res d'un caractère à droite
addi $25, $25,1
bnez $9, boucle_i

ori $2,$0,4
la $4, res
syscall

ori $2, $0, 10
syscall
