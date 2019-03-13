#somme (de 0 à 10) =0x37 = 3*16+7=48+7=55
.data 
.text 
.globl main
main:
addiu $8, $0, 0#somme
addiu $9, $0, 10#nb it

loop:
addu $8, $8, $9
addiu $9, $9, -1
bne $9,0, loop #branch not equal

ori $2, $0, 10
syscall
