##  ## print “hello world”  
##  programed by：stevie zou 
##  ######################################### 
#  text segment       #  
#########################################    
.text         
.globl main  
main:       
la $a0,str    #$a0储存要打印字符的地址      
 li $v0, 4     #为syscall读取整数值     
  syscall       #system call service 4  打印字符串    
 li $v0,10     
 syscall       #system call service 10 退出  
######################################### #   data segment      #  #########################################   
  .data  str: .asciiz "hello world\n"
 ##############end of file