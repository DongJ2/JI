##  ## print ��hello world��  
##  programed by��stevie zou 
##  ######################################### 
#  text segment       #  
#########################################    
.text         
.globl main  
main:       
la $a0,str    #$a0����Ҫ��ӡ�ַ��ĵ�ַ      
 li $v0, 4     #Ϊsyscall��ȡ����ֵ     
  syscall       #system call service 4  ��ӡ�ַ���    
 li $v0,10     
 syscall       #system call service 10 �˳�  
######################################### #   data segment      #  #########################################   
  .data  str: .asciiz "hello world\n"
 ##############end of file