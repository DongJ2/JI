# Ve370 Project 1
# Dong Jing 515370910182
# p1.s
	.data 0x10000000
array:	.word 10,54,62,77,45,61,23,34,86,60,63,59,0,1,2,13,14,15,99,98,7,8,9,80,78
	.data 0x10000100
str1: 	.asciiz "The number of numbers greater or equal to 60 is "
	.data 0x10000200
str2: 	.asciiz "The number of numbers less than 60 is "
	.data 0x10000300
str3:	.asciiz ".\n"
	.text
	.globl __start
__start:
main:
	addi $sp, $sp, -8	# adjust stack for 2 items
	sw $s1, 4($sp)		# save $s1(Fail)
	sw $s0, 0($sp)		# save $s0(Pass)
	
	lui $a0, 0x1000		# $a0 is the base address of array
	addi $a1, $zero, 25	# $a1 is the size of array
	
	addi $a2, $zero, 1 	# $a2=1 (cntType=1)
	jal CountArray		# $v0=CountArray(Array, size, 1)
	add $t0, $t0, $zero	# no meaning
	add $s0, $v0, $zero	# $s0=$v0($s0=Pass(Array))

	addi $a2, $zero, -1	# $a2=-1 (cntType=-1)
	jal CountArray		# $vo=CountArray(Array, size, -1)
	add $t0, $t0, $zero	# no meaning
	add $s1, $v0, $zero	# $s1=$v0($s1=Fail(Array)

	addi $v0, $zero, 4  # print str1
	lui  $a0, 0x1000			
	addi $a0, $a0, 256
	syscall
	
	addi $v0, $zero, 1	# Load $v0 with syscall 1=print_int
	add $a0, $s0, $zero # $a0=$s0
	syscall				# print Pass(Array)

	addi $v0, $zero, 4	#print str3
	lui $a0, 0x1000
	addi $a0, $a0, 768
	syscall
	
	lui $a0, 0x1000		#print str2
	addi $a0, $a0, 512
	syscall
	
	addi $v0, $zero, 1
	add $a0, $s1, $zero # $a0=$s1
	syscall				# print Fail(Array)

	lw $s0, 0($sp)		# restore $s0
	lw $s1, 4($sp)		# restore $s1
	addi $sp, $sp, 8	# restore stack pointer
		
	addi $v0, $zero, 10	# Exit
	syscall				# Exit
	
CountArray:
	addi $sp, $sp, -20	# create stack for 5 items
	sw $ra, 16($sp)		# save return address
	sw $a3, 12($sp)		# save $a3
	sw $a0, 8($sp)		# save $a0
	sw $s1, 4($sp)		# save $s1
	sw $s0, 0($sp)		# save $s0

	add $s1, $zero, $zero	# cnt($s1)=0
	add $s0, $zero, $zero	# i($s0)=0
	add $t0, $a1, $zero	# $a0=address of Array[size]

Loop:
	slt $t0, $s0, $a1	# if ($s0<$a1) $t0=1 else $t0=0
	beq $t0, $zero, Exit	# if ($t0==0) exit 
	add $t0, $t0, $zero	# no meaning
	lw $a3, 0($a0)		# $a3=Array[i]
	addi $s0, $s0, 1	# $s0++(i++)
	addi $a0, $a0, 4	# reach the address of next number
	slt $t0, $zero, $a2	# if (0<$a2) $t0=1 else $t0=0
	bne $t0, $zero, Pass	# if ($t0!=0) Pass
	add $t0, $zero, $zero	# no meaning
	slt $t0, $zero, $a2	# if (0<$a2) $t0=1 else $t0=0
	beq $t0, $zero, Fail	# if ($t0==0) Fail
	add $t0, $t0, $zero	# no meaning

Pass:
	jal Passint			# $v0=Passint(Array[i])
	add $t0, $t0, $zero	# no meaning
	add $s1, $s1, $v0	# cnt=cnt+Passint(Array[i])
	j Loop				# jump to Loop
	add $t0, $t0, $zero	# no meaning

Fail:
	jal Failint			# $v0=Failint(Array[i])
	add $t0, $t0, $zero	# no meaning
	add $s1, $s1, $v0	# cnt=cnt+Failint(Array[i])
	j Loop				# jump to Loop
	add $t0, $t0, $zero	# no meaning
	
Passint:
	addi $t1, $zero, 59
	slt $v0, $t1, $a3	# if (60=<Array[i]) $v0=1 else $v0=0 
	jr $ra				# return 
	add $t0, $t0, $zero	# no meaning

Failint:
	slti $v0, $a3, 60	# if (Array[i]<60) $v0=1 else $v0=0
	jr $ra			# return
	add $t0, $t0, $zero	# no meaning

Exit:	
	add $v0, $s1, $zero	# $v0=$s1 (Let CountArray = cnt)
	lw $s0, 0($sp)		# restore $s0
	lw $s1, 4($sp)		# restore $s1
	lw $a0, 8($sp)		# restore $a0
	lw $a3, 12($sp)		# restore $a3
	lw $ra, 16($sp)		# restore $ra
	addi $sp, $sp, 20	# restore stack pointer
	jr $ra			# return
	add $t0, $t0, $zero	# no meaning