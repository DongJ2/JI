# 5133709187_p1.s
	.data
array:	 .word 	1, 13, -5, 6, 7, 0, 9, 15, 0, -6, 5, -3
	.text
	.globl __start
__start:
main:
	addi $sp, $sp, -12		# adjust stack for 3 items
	sw	 $s2, 8($sp)		# save $s2
	sw	 $s1, 4($sp)		# save $s1
	sw	 $s0, 0($sp)		# save $s0

	lui	 $a0, 0x1000		# $a0 = base address of array
	addi $a1, $zero, 12		# $a1(size) = 12

	addi $a2, $zero, 1 		# cntType=1
	jal COUNT				# $v0 = COUNT(array, size, 1)
	add  $t0, $t0, $zero    # meaningless
	add  $s0, $v0, $zero	# PosCnt($s0) = COUNT(array, size, 1)

	addi $a2, $zero, -1     # cntType=-1
	jal COUNT				# $v0 = COUNT(array, size, -1)
	add  $t0, $t0, $zero    # meaningless
	add  $s1, $v0, $zero	# NegCnt($s1) = COUNT(array, size, -1)

	add  $a2, $zero, $zero  # cntType=0
	jal COUNT				# $v0 = COUNT(array, size, 0)
	add  $t0, $t0, $zero    # meaningless
	add  $s2, $v0, $zero	# ZeroCnt($s2) = COUNT(array, size, 0)

	addi $v0, $zero, 1      # Load $v0 with syscall 1 = print_int
	add  $a0, $s0, $zero    # Load $a0 with Poscnt($s0) to be printed
	syscall					# print_int

	add  $a0, $s1, $zero    # Load $a0 with Negcnt($s1) to be printed
	syscall					# print_int

	add  $a0, $s2, $zero    # Load $a0 with Zerocnt($s2) to be printed
	syscall					# print_int

	lw	 $s0, 0($sp)		# restore $s0 from stack
	lw	 $s1, 4($sp)		# restore $s1 from stack
	lw   $s2, 8($sp)		# restore $s2 from stack
	addi $sp, $sp, 12		# restore stack pointer

	addi  $v0, $zero, 10  	# Prepare to exit (system call 10)
	syscall  		  		# Exit

COUNT:
	addi $sp, $sp, -20		# adjust stack for 5 items
	sw   $ra, 16($sp)		# save return address
	sw   $a3, 12($sp)		# save $a3
	sw   $a0, 8($sp)		# save $a0
	sw	 $s1, 4($sp)		# save $s1
	sw	 $s0, 0($sp)		# save $s0

	add  $s1, $zero, $zero 	# cnt($s1)=0
	add  $s0, $a1, $zero	# i($s0)=size
	add  $t0, $a1, $zero    # $a0 = address of array[size]
	sll  $t0, $t0, 2
	add  $a0, $a0, $t0		

LOOP:
	addi $s0, $s0, -1       # i=i-1
	addi $a0, $a0, -4		# $a0 = address of array[i]
	slt  $t0, $s0, $zero    # $t0=1 if $s0<$zero
	bne  $t0, $zero, EXIT   # go to EXIT if $s0<$zero (i<0)
	add  $t0, $t0, $zero    # meaningless
	lw   $a3, 0($a0)		# $a3=array[i]
	slt  $t0, $zero, $a2    # go to CALLPOS if $zero<$a2 (cntType=1)
	bne  $t0, $zero, CALLPOS	
	add  $t0, $t0, $zero    # meaningless
	slt  $t0, $a2, $zero    # go to CALLNEG if $a2<$zero (cntType=-1)
	bne  $t0, $zero, CALLNEG	
	add  $t0, $t0, $zero    # meaningless
	j CALLZERO				# go to CALLZERO
	add  $t0, $t0, $zero    # meaningless

CALLPOS:
	jal POS                 # $v0 = POS(array[i])
	add  $t0, $t0, $zero    # meaningless
	add  $s1, $s1, $v0		# cnt = cnt + POS(array[i])
	j LOOP 					# go to LOOP
	add  $t0, $t0, $zero    # meaningless

CALLNEG:
	jal NEG                 # $v0 = NEG(array[i])
	add  $t0, $t0, $zero    # meaningless
	add  $s1, $s1, $v0		# cnt = cnt + NEG(array[i])
	j LOOP 					# go to LOOP
	add  $t0, $t0, $zero    # meaningless

CALLZERO:
	jal ZERO                # $v0 = ZERO(array[i])
	add  $t0, $t0, $zero    # meaningless
	add  $s1, $s1, $v0		# cnt = cnt + ZERO(array[i])
	j LOOP 					# go to LOOP
	add  $t0, $t0, $zero    # meaningless

EXIT:
	add  $v0, $s1, $zero    # $v0 = $s1 (COUNT = cnt)
	lw   $s0, 0($sp)		# restore $s0 from stack
	lw	 $s1, 4($sp)		# restore $s1 from stack
	lw	 $a0, 8($sp)		# restore $a0 from stack
	lw   $a3, 12($sp)		# restore $a3 from stack
	lw   $ra, 16($sp)		# restore $ra from stack
	addi $sp, $sp, 20		# restore stack pointer
	jr $ra 					# return 
	add  $t0, $t0, $zero    # meaningless

POS:
	slt  $v0, $zero, $a3	# POS = (0<array[i]) ? 1 : 0
	jr $ra					# return
	add  $t0, $t0, $zero    # meaningless

NEG:
	slt  $v0, $a3, $zero    # NEG = (array[i]<0) ? 1 : 0
	jr $ra					# return
	add  $t0, $t0, $zero    # meaningless

ZERO:
	add  $v0, $zero, $zero  # ZERO = (array[i]=0) ? 1 : 0
	bne  $a3, $zero, QUITZERO
	add  $t0, $t0, $zero    # meaningless
	add  $v0, $zero, 1
QUITZERO:
	jr $ra					# return
	add  $t0, $t0, $zero    # meaningless
	