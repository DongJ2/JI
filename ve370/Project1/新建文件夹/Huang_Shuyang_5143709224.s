#	Ve370
#	Huang Shuyang
#	5143709224
#	Project 1

	.data	0x10000000
array:	.word	1, 13, 3, 9, -5, -10, 0, -11, 7, 0, -23, 19, 0, 8, 6  #	array
	.data	0x10000100
hint1:	.asciiz "The number of positive integers is "	#	hint1
	.data	0x10000200
hint2:  .asciiz "The number of negative integers is "	#	hint2
	.data	0x10000300
hint3:	.asciiz "The number of zeros is "	#	hint3
	.data	0x10000400
hint4:	.asciiz ".\n"	#	end of a line

	
	.text
	.globl __start
	
__start:

main:
	
	addi $sp, $sp, -24 		#	build stack. a0, a1, a2, s0, s1, s2 used. 
	sw	 $a0, 0($sp)		#	save word a0, a1, a2, s0, s1, s2 into stack.
	sw	 $a1, 4($sp)
	sw   $a2, 8($sp)
	sw	 $s0, 12($sp)
	sw	 $s1, 16($sp)
	sw	 $s2, 20($sp)

	lui  $a0, 0x1000		#	$a0 = the base address of array. $a0 = testArray.
	addi $a1, $zero, 15			#	$a1 = the size of array.   
	
	addi $a2, $zero, 1		#	$a2 = 1, tag for choosing positive numbers.
	jal  countArray			#	jump t0 the countArray. countArray(testArray, size, 1).
	add  $t0, $zero, $t0	#	meaningless, used after jump command.
	add  $s0, $zero, $v0	#	$s0 = PosCnt. 
	
	addi $a2, $zero, -1 	#	$a2 = -1, tag for choosing negative numbers.
	jal  countArray			#	jump t0 the countArray. countArray(testArray, size, -1).
	add  $t0, $zero, $t0	#	meaningless, used after jump command.
	add  $s1, $zero, $v0	#	$s1 = NegCnt.
	
	addi $a2, $zero, 0		#	$a2 = 0, tag for choosing zeros.
	jal  countArray			#	jump t0 the countArray. countArray(testArray, size, 0).
	add  $t0, $zero, $t0	#	meaningless, used after jump command.
	add  $s2, $zero, $v0	#	$s2 = ZeroCnt.
	
	addi $v0, $zero , 4		#	system call with $v0 = 4, print_string.
	lui  $a0, 0x1000			
	addi $a0, $a0, 256		#	address of string is 0x10000100.
	syscall					#	make the system call.
	addi $v0, $zero, 1		#	system call with $v0 = 1, print_int.
	add  $a0, $zero, $s0	#	load PosCnt t0 $a0.
	syscall					#	make the system call.
	addi $v0, $zero , 4		#	system call with $v0 = 4, print_string.
	lui  $a0, 0x1000
	addi $a0, $a0, 1024		#	address of string is 0x10000400.
	syscall					#	make the system call.
	
	addi $v0, $zero , 4		#	system call with $v0 = 4, print_string.
	lui  $a0, 0x1000			
	addi $a0, $a0, 512		#	address of string is 0x10000200.
	syscall					#	make the system call.
	addi $v0, $zero, 1		#	system call with $v0 = 1, print_int.
	add  $a0, $zero, $s1	#	load Negnt t0 $a0.
	syscall					#	make the system call.
	addi $v0, $zero , 4		#	system call with $v0 = 4, print_string.
	lui  $a0, 0x1000
	addi $a0, $a0, 1024		#	address of string is 0x10000400.
	syscall					#	make the system call.
	
	addi $v0, $zero , 4		#	system call with $v0 = 4, print_string.
	lui  $a0, 0x1000			
	addi $a0, $a0, 768		#	address of string is 0x10000300.
	syscall					#	make the system call.
	addi $v0, $zero, 1		#	system call with $v0 = 1, print_int.
	add  $a0, $zero, $s2	#	load ZeroCnt t0 $a0.
	syscall					#	make the system call.
	addi $v0, $zero , 4		#	system call with $v0 = 4, print_string.
	lui  $a0, 0x1000
	addi $a0, $a0, 1024		#	address of string is 0x10000400.
	syscall					#	make the system call.
	
	lw	 $a0, 0($sp)		#	load data in stack.	
	lw	 $a1, 4($sp)
	lw   $a2, 8($sp)
	lw	 $s0, 12($sp)
	lw	 $s1, 16($sp)
	lw	 $s2, 20($sp)
	addi $sp, $sp, 24		#	destory stack.
	
	addi $v0, $zero, 10		#	system call with $v0 = 10, terminate the execution.
	syscall					#	terminate the execution.
								
countArray:

	addi $sp, $sp, -20		#	build stack, s0, s1, s2, a0, ra.
	sw   $ra, 16($sp)		#	save.
	sw	 $s0, 12($sp)
	sw	 $s1, 8($sp)
	sw	 $s2, 4($sp)
	sw	 $a0, 0($sp)
							
	add  $s0, $zero, $a1	#	$s0 = 15, which is the length of array.
	sll  $s2, $s0, 	 2
	add  $s2, $s2,   $a0	#	$s2 is the address of current word.
	add  $s1, $zero, $zero	#	$s1 = cnt = 0.
	
loop:
	
	add  $s0, $s0, -1		#	$s0 = $s0 - 1. i = i - 1.
	slt	 $t0, $s0, $zero	#	$t0 = 1 if $s0 < 0, if i < 0.
	bne  $t0, $zero, EXIT	#	if ($t0 != $zero), $s0 < 0, goto EXIT 	
	add  $t0, $zero, $t0	#	meaningless, used after jump command.
	add  $s2, $s2, -4		#	$s2 = $s2 - 4. Adjust the address.
	
	lw   $a0, 0($s2)		#	load an integer.
	
	addi $t0, $zero, 1		#	set $t0 = 1.
	beq	 $a2, $t0, Pos		#	if ($a2 == 1) goto Pos.
	add  $t0, $zero, $t0	#	meaningless, used after jump command.

	addi $t0, $zero, -1		#	set $t0 = -1.
	beq	 $a2, $t0, Neg		#	if ($a2 == -1) got0 Neg.
	add  $t0, $zero, $t0	#	meaningless, used after jump command.
			
	addi $t0, $zero, 0		#	set $t0 = 0.
	beq	 $a2, $t0, Zero		#	if ($a2 == 0) got0 Zero.
	add  $t0, $zero, $t0	#	meaningless, used after jump command.
	
point1:						#	since beq command is not linked,
							#	point1 is used to recover the link. 
	add  $s1, $s1,   $v0	#	$s1 = $s1 + Pos. cnt += Zero(a[i]).
	add  $v0, $zero, $zero	#	$v0 = 0.
	
	j loop					#	go on the loop.
	add  $t0, $zero, $t0	#	meaningless, used after jump command.	
	
EXIT:						#	run when loop is finished.
	add  $v0, $zero, $s1	#	save result ($s1) into $v0.
	lw   $ra, 16($sp)		#	load.
	lw	 $s0, 12($sp)
	lw	 $s1, 8($sp)
	lw	 $s2, 4($sp)
	lw	 $a0, 0($sp)	
	addi $sp, $sp, 20		#	destory stack.
	jr   $ra				#	jump back to main.
	add  $t0, $zero, $t0	#	meaningless, used after jump command.	
	
Pos:
	slt $v0, $zero, $a0		#	if ($zero < $a0), $v0 = 1.
	j	point1				#	jump back.
	add $t0, $zero, $t0		#	meaningless, used after jump command.
Neg:
	slt $v0, $a0, $zero		#	if ($a0 < $zero), $v0 = 1.
	j	point1				#	jump back.
	add $t0, $zero, $t0		#	meaningless, used after jump command.
Zero:
	add $v0, $zero, $zero	#	$v0 = 0.
	beq	$a0, $zero, AddOne	#	if ($a0 == 0), AddOne.
	add $t0, $zero, $t0		#	meaningless, used after jump command.
point2:						#	used to save link.
	jr  point1				#	jump back.
	add $t0, $zero, $t0		#	meaningless, used after jump command.
AddOne:
	addi $v0, $zero, 1		#	$v0 = $v0 + 1.
	jr point2				#	jump back to point2.
	add $t0, $zero, $t0		#	meaningless, used after jump command.
	