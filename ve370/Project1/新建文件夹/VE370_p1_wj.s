# VE370_WingJing_5143709228_p1.s
	.data
testArray:	.word 	1, -2, 3, -4, 0, 5, -6, 7, -8, 0, 9, -10, 11, -12
	.text
	.globl __start
__start:

main:
	addi	$sp, $sp, -12		# create stack for 3 items
	sw	$s2, 8($sp)		# save $s2
	sw	$s1, 4($sp)		# save $s1
	sw	$s0, 0($sp)		# save $s0

	lui		$a0, 0x1000		# $a0 = address of the array
	addi 	$a1, $zero, 14		# $a1 size = 14

	addi 	$a2, $zero, 1 		# cntType = 1
	jal COUNT			# $v0 = COUNT(array, size, 1)
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add 	$s0, $v0, $zero		# PosCnt($s0) = COUNT(array, size, 1)
	addi 	$a2, $zero, -1     	# cntType = -1
	jal COUNT			# $v0 = COUNT(array, size, -1)
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add  	$s1, $v0, $zero		# NegCnt($s1) = COUNT(array, size, -1)
	add  	$a2, $zero, $zero  	# cntType = 0
	jal COUNT			# $v0 = COUNT(array, size, 0)
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add  	$s2, $v0, $zero		# ZeroCnt($s2) = COUNT(array, size, 0)

	addi 	$v0, $zero, 1      	# Load $v0 with syscall 1 = print_int
	add  	$a0, $s0, $zero    	# Load $a0 with Poscnt($s0) to be printed
	syscall				# print the value on the screen

	add  	$a0, $s1, $zero    	# Load $a0 with Negcnt($s1) to be printed
	syscall				# print the value on the screen

	add  	$a0, $s2, $zero    	# Load $a0 with Zerocnt($s2) to be printed
	syscall				# print the value on the screen

	lw	$s0, 0($sp)		# reload $s0 from stack
	lw	$s1, 4($sp)		# reload $s1 from stack
	lw  $s2, 8($sp)		# reload $s2 from stack
	addi 	$sp, $sp, 12		# restore stack pointer

	addi  	$v0, $zero, 10  	# Prepare to exit (system call 10)
	syscall  		  	# Exit

COUNT:
	addi 	$sp, $sp, -20		# create stack for 5 items
	sw  $ra, 16($sp)	# save return address
	sw  $a3, 12($sp)	# save $a3
	sw  $a0, 8($sp)		# save $a0
	sw	$s1, 4($sp)		# save $s1
	sw	$s0, 0($sp)		# save $s0

	add  	$s1, $zero, $zero 	# cnt($s1)=0
	add  	$s0, $a1, $zero		# i($s0)=size
	add  	$t0, $a1, $zero    	
	sll  	$t0, $t0, 2
	add  	$a0, $a0, $t0		# $a0 = address of array[size]

LOOP:
	addi 	$s0, $s0, -1       	# i=i-1
	addi 	$a0, $a0, -4		# $a0 = address of array[i]
	slt  	$t0, $s0, $zero    	# $t0=1 if $s0<$zero
	bne  	$t0, $zero, EXIT   	# jump to EXIT if $s0<$zero (i<0)
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	lw   	$a3, 0($a0)		# $a3=array[i]
	slt  	$t0, $zero, $a2    	# jump to POS_helper if $zero<$a2 (cntType=1)
	bne  	$t0, $zero, POS_helper	
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	slt  	$t0, $a2, $zero    	# jump to NEG_helper if $a2<$zero (cntType=-1)
	bne  	$t0, $zero, NEG_helper	
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	j ZERO_helper			# jump to ZERO_helper
	add  	$t0, $t0, $zero    	# no meaning, used after jump

POS_helper:
	jal POS                 	# $v0 = POS(array[i])
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add  	$s1, $s1, $v0		# cnt = cnt + POS(array[i])
	j LOOP 				# jump to LOOP
	add  	$t0, $t0, $zero    	# no meaning, used after jump

NEG_helper:
	jal NEG                 	# $v0 = NEG(array[i])
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add  	$s1, $s1, $v0		# cnt = cnt + NEG(array[i])
	j LOOP 				# jump to LOOP
	add  	$t0, $t0, $zero    	# no meaning, used after jump

ZERO_helper:
	jal ZERO                	# $v0 = ZERO(array[i])
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add  	$s1, $s1, $v0		# cnt = cnt + ZERO(array[i])
	j LOOP 				# jump to LOOP
	add  	$t0, $t0, $zero    	# no meaning, used after jump

POS:
	slt  	$v0, $zero, $a3		# POS = (0<array[i]) ? 1 : 0
	jr 	$ra			# return
	add  	$t0, $t0, $zero    	# no meaning, used after jump

NEG:
	slt  	$v0, $a3, $zero    	# NEG = (array[i]<0) ? 1 : 0
	jr 	$ra			# return
	add  	$t0, $t0, $zero    	# no meaning, used after jump

ZERO:
	add  	$v0, $zero, $zero  	# ZERO = (array[i]=0) ? 1 : 0
	bne  	$a3, $zero, QUITZERO
	add  	$t0, $t0, $zero    	# no meaning, used after jump
	add  	$v0, $zero, 1

QUITZERO:
	jr 	$ra			# return
	add  	$t0, $t0, $zero    	# no meaning, used after jump

EXIT:
	add  	$v0, $s1, $zero    	# $v0 = $s1 (COUNT = cnt)
	lw   	$s0, 0($sp)		# restore $s0 from stack
	lw	$s1, 4($sp)		# restore $s1 from stack
	lw	$a0, 8($sp)		# restore $a0 from stack
	lw   	$a3, 12($sp)		# restore $a3 from stack
	lw   	$ra, 16($sp)		# restore $ra from stack
	addi 	$sp, $sp, 20		# restore stack pointer
	jr 	$ra 			# return 
	add  	$t0, $t0, $zero    	# no meaning, used after jump