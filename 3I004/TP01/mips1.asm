#var3=var1+var2
.data 
var1: .word 0x12
var2: .word 0x34
var3: .word 0

.text 
.globl main
main:
La $8, var1#adresse de var1 ds $8
lw $8, 0($8)#mem(0+$8) ds $8
La $9, var2
lw $9, 0($9)
addu $8,$8,$9
La $9, var3
sw $8, 0($9)

#return 0
ori $2, $0, 10
syscall
